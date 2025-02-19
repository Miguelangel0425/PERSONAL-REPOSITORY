#include "FunctionExtractor.h"
#include <fstream>
#include <regex>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <sys/stat.h>

FunctionExtractor::FunctionExtractor() {}

bool FunctionExtractor::isValidSourceFile(const std::string& filePath) {
    size_t pos = filePath.find_last_of(".");
    if (pos == std::string::npos) return false;
    
    std::string extension = filePath.substr(pos);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    std::unordered_set<std::string> validExtensions = {
        ".cpp", ".cc", ".cxx", ".c", ".h", ".hpp", ".txt", ".exe"
    };
    
    return validExtensions.find(extension) != validExtensions.end();
}

bool FunctionExtractor::fileExists(const std::string& filePath) {
    struct stat buffer;
    return (stat(filePath.c_str(), &buffer) == 0);
}

std::streamsize FunctionExtractor::getFileSize(const std::string& filePath) {
    struct stat buffer;
    if (stat(filePath.c_str(), &buffer) == 0) {
        return buffer.st_size;
    }
    return -1;
}

bool FunctionExtractor::isBinaryFile(const std::string& filePath) {
    std::ifstream file(filePath.c_str(), std::ios::binary);
    if (!file.is_open()) {
        if (!fileExists(filePath)) {
            throw std::runtime_error("El archivo no existe: " + filePath);
        }
        throw std::runtime_error("No se puede abrir el archivo: " + filePath);
    }
    
    // Verificar solo los primeros 4KB
    const size_t SAMPLE_SIZE = 4096;
    char buffer[SAMPLE_SIZE];
    file.read(buffer, SAMPLE_SIZE);
    size_t bytesRead = file.gcount();
    
    size_t binaryCount = 0;
    for (size_t i = 0; i < bytesRead; i++) {
        if (buffer[i] == 0 || (unsigned char)buffer[i] > 127) {
            binaryCount++;
            // Si más del 10% son caracteres binarios, considerarlo binario
            if (binaryCount > bytesRead / 10) {
                return true;
            }
        }
    }
    
    return false;
}

std::string FunctionExtractor::readFile(const std::string& filePath) {
    if (!fileExists(filePath)) {
        throw std::runtime_error("El archivo no existe: " + filePath);
    }

    // Verificar si es binario antes de leer completamente
    if (isBinaryFile(filePath)) {
        std::cout << "Archivo binario detectado: " << filePath << std::endl;
        return analyzeBinaryFile(filePath);
    }

    std::ifstream file(filePath.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("No se puede abrir el archivo: " + filePath);
    }
    
    std::cout << "Leyendo contenido del archivo de texto..." << std::endl;
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string FunctionExtractor::analyzeBinaryFile(const std::string& filePath) {
    std::stringstream result;
    std::streamsize fileSize = getFileSize(filePath);
    
    result << "// Análisis de archivo binario: " << filePath << "\n\n";
    result << "void main() {\n";
    result << "    // Este es un archivo binario/ejecutable\n";
    if (fileSize >= 0) {
        result << "    // Tamaño: " << fileSize << " bytes\n";
    }
    result << "    // No es posible extraer las funciones originales\n";
    result << "    // Se recomienda analizar el código fuente (.cpp, .c)\n";
    result << "}\n";
    
    return result.str();
}

std::vector<Function> FunctionExtractor::extractFromFile(const std::string& filePath) {
    try {
        std::cout << "Procesando archivo: " << filePath << std::endl;
        
        if (!isValidSourceFile(filePath)) {
            throw std::runtime_error("Extensión de archivo no soportada.\n"
                               "Extensiones válidas: .cpp, .cc, .cxx, .c, .h, .hpp, .exe");
        }
        
        std::cout << "Leyendo archivo..." << std::endl;
        std::string sourceCode = readFile(filePath);
        std::cout << "Extrayendo funciones..." << std::endl;
        auto result = extractFunctions(sourceCode);
        std::cout << "Extracción completada. Encontradas " << result.size() << " funciones." << std::endl;
        return result;
    } catch (const std::exception& e) {
        std::cerr << "Error al extraer funciones: " << e.what() << std::endl;
        return std::vector<Function>();
    }
}

std::vector<Function> FunctionExtractor::extractFunctions(const std::string& sourceCode) {
    std::vector<Function> functions;
    std::regex functionPattern("(\\w+(?:\\s+\\w+)*?)\\s+(\\w+)\\s*\\(([^)]*)\\)\\s*\\{");
    std::string::const_iterator searchStart(sourceCode.cbegin());
    std::smatch functionMatch;
    
    std::unordered_map<std::string, bool> keywords = {
        {"if", true}, {"else", true}, {"while", true}, 
        {"for", true}, {"switch", true}, {"case", true}
    };
    
    std::cout << "Buscando patrones de funcion..." << std::endl;
    int functionCount = 0;
    
    while (std::regex_search(searchStart, sourceCode.cend(), functionMatch, functionPattern)) {
        functionCount++;
        std::string funcName = functionMatch[2];
        
        // Verificar primero si es una palabra clave antes de procesar
        if (keywords.find(funcName) != keywords.end()) {
            // Es una palabra clave, avanzar y continuar
            size_t matchPos = functionMatch.position() + functionMatch.prefix().length();
            searchStart = sourceCode.cbegin() + matchPos + 1;
            continue;
        }
        
        std::cout << "Funcion #" << functionCount << " encontrada: " << funcName << "..." << std::endl;
        
        Function func;
        func.returnType = functionMatch[1];
        func.name = funcName;
        func.parameters = functionMatch[3];
        
        size_t functionStartPos = functionMatch.position() + functionMatch.length() - 1;
        std::cout << "Extrayendo cuerpo de la funcion " << func.name << "..." << std::endl;
        func.body = extractFunctionBody(sourceCode, functionStartPos);
        
        std::cout << "Analizando complejidad para " << func.name << "..." << std::endl;
        func.complexity = analyzeComplexity(func.body);
        functions.push_back(func);
        
        searchStart = sourceCode.cbegin() + functionStartPos + func.body.length();
    }
     
    // Si no se encontraron funciones, crear una función especial
    if (functions.empty()) {
        std::cout << "No se encontraron funciones, creando función de marcador..." << std::endl;
        Function emptyFunc;
        emptyFunc.name = "EmptyFile";
        emptyFunc.returnType = "void";
        emptyFunc.parameters = "void";
        emptyFunc.body = "{ /* No se encontraron funciones */ }";
        emptyFunc.complexity = "N/A";
        functions.push_back(emptyFunc);
    }
    
    return functions;
}

std::string FunctionExtractor::extractFunctionBody(const std::string& sourceCode, size_t startPos) {
    size_t endPos = startPos + 1;
    int braceCount = 1;
    const size_t MAX_ITERATIONS = 100000; // Límite de seguridad
    size_t iterations = 0;
    
    while (braceCount > 0 && endPos < sourceCode.length() && iterations < MAX_ITERATIONS) {
        if (sourceCode[endPos] == '{') {
            braceCount++;
        } else if (sourceCode[endPos] == '}') {
            braceCount--;
        }
        endPos++;
        iterations++;
    }
    
    if (braceCount != 0 || iterations >= MAX_ITERATIONS) {
        std::cerr << "Advertencia: Posible estructura irregular de llaves o función demasiado larga" << std::endl;
        return "{}";
    }
    
    return sourceCode.substr(startPos, endPos - startPos);
}

std::string FunctionExtractor::analyzeComplexity(const std::string& code) {
    // Limitar el análisis a los primeros 10000 caracteres para archivos muy grandes
    std::string analyzedCode = code.length() > 10000 ? code.substr(0, 10000) : code;
    
    std::regex forRegex("\\bfor\\b");
    std::regex whileRegex("\\bwhile\\b");
    
    auto forBegin = std::sregex_iterator(analyzedCode.begin(), analyzedCode.end(), forRegex);
    auto forEnd = std::sregex_iterator();
    int forCount = std::distance(forBegin, forEnd);
    
    auto whileBegin = std::sregex_iterator(analyzedCode.begin(), analyzedCode.end(), whileRegex);
    auto whileEnd = std::sregex_iterator();
    int whileCount = std::distance(whileBegin, whileEnd);
    
    int loops = forCount + whileCount;
    
    // Simplificar expresión regular para bucles anidados para evitar backtracking excesivo
    std::regex nestedLoopPattern("for[^{]{0,50}\\{[^}]{0,200}(for|while)|while[^{]{0,50}\\{[^}]{0,200}(for|while)");
    auto nestedLoopBegin = std::sregex_iterator(analyzedCode.begin(), analyzedCode.end(), nestedLoopPattern);
    auto nestedLoopEnd = std::sregex_iterator();
    int nestedLoops = std::distance(nestedLoopBegin, nestedLoopEnd);
    
    std::regex functionNamePattern("(\\w+)\\s*\\([^)]*\\)\\s*\\{");
    std::smatch nameMatch;
    bool hasRecursion = false;
    
    if (std::regex_search(analyzedCode, nameMatch, functionNamePattern)) {
        std::string funcName = nameMatch[1];
        std::string funcBody = analyzedCode.substr(nameMatch.position() + nameMatch.length());
        
        std::regex recursiveCallPattern("\\b" + funcName + "\\s*\\(");
        auto recursiveCallBegin = std::sregex_iterator(funcBody.begin(), funcBody.end(), recursiveCallPattern);
        auto recursiveCallEnd = std::sregex_iterator();
        hasRecursion = std::distance(recursiveCallBegin, recursiveCallEnd) > 0;
    }
    
    if (hasRecursion) {
        return "O(2^n)";
    } else if (nestedLoops > 0) {
        int depth = nestedLoops + 1;
        return "O(n^" + std::to_string(depth) + ")";
    } else if (loops > 0) {
        return "O(n)";
    } else {
        return "O(1)";
    }
}

bool FunctionExtractor::saveToCSV(const std::vector<Function>& functions, const std::string& outputPath) {
    try {
        std::cout << "Guardando resultados en CSV: " << outputPath << std::endl;
        std::ofstream outputFile(outputPath);
        if (!outputFile.is_open()) {
            std::cerr << "No se pudo crear el archivo CSV: " << outputPath << std::endl;
            return false;
        }
        
        outputFile << "Nombre,Tipo de retorno,Parámetros,Complejidad\n";
        
        for (const Function& func : functions) {
            std::string params = func.parameters;
            std::string::size_type pos = 0;
            while ((pos = params.find("\"", pos)) != std::string::npos) {
                params.replace(pos, 1, "\"\"");
                pos += 2;
            }
            
            outputFile << func.name << "," 
                      << func.returnType << "," 
                      << "\"" << params << "\"," 
                      << func.complexity << "\n";
        }
        
        outputFile.close();
        std::cout << "CSV guardado exitosamente" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error al guardar el CSV: " << e.what() << std::endl;
        return false;
    }
}