#include "FunctionExtractor.h"
#include <fstream>
#include <regex>
#include <stdexcept>
#include <unordered_map>
#include <iostream>

FunctionExtractor::FunctionExtractor() {
    // Inicialización si es necesaria
}

std::vector<Function> FunctionExtractor::extractFromFile(const std::string& filePath) {
    try {
        std::string sourceCode = readFile(filePath);
        return extractFunctions(sourceCode);
    } catch (const std::exception& e) {
        std::cerr << "Error al extraer funciones: " << e.what() << std::endl;
        return std::vector<Function>();
    }
}

std::string FunctionExtractor::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + filePath);
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    return content;
}

std::vector<Function> FunctionExtractor::extractFunctions(const std::string& sourceCode) {
    std::vector<Function> functions;
    
    // Regex para capturar definiciones de funciones en C
    // Captura: tipo_retorno nombre_funcion(parámetros) {
    std::regex functionPattern("(\\w+(?:\\s+\\w+)*?)\\s+(\\w+)\\s*\\(([^)]*)\\)\\s*\\{");
    
    std::string::const_iterator searchStart(sourceCode.cbegin());
    std::smatch functionMatch;
    
    // Palabras clave que no deben considerarse como nombres de función
    std::unordered_map<std::string, bool> keywords = {
        {"if", true}, {"else", true}, {"while", true}, 
        {"for", true}, {"switch", true}, {"case", true}
    };
    
    while (std::regex_search(searchStart, sourceCode.cend(), functionMatch, functionPattern)) {
        Function func;
        func.returnType = functionMatch[1];
        func.name = functionMatch[2];
        func.parameters = functionMatch[3];
        
        // Posición del inicio de la función (apertura de llave)
        size_t functionStartPos = functionMatch.position() + functionMatch.length() - 1;
        
        // Extraer el cuerpo completo con balance de llaves
        func.body = extractFunctionBody(sourceCode, functionStartPos);
        
        // Solo analizar y agregar si no es una palabra clave
        if (keywords.find(func.name) == keywords.end()) {
            func.complexity = analyzeComplexity(func.body);
            functions.push_back(func);
        }
        
        // Continuar la búsqueda después del cuerpo de la función
        searchStart = sourceCode.cbegin() + functionStartPos + func.body.length();
    }
    
    return functions;
}

std::string FunctionExtractor::extractFunctionBody(const std::string& sourceCode, size_t startPos) {
    size_t endPos = startPos + 1;
    int braceCount = 1;
    
    while (braceCount > 0 && endPos < sourceCode.length()) {
        if (sourceCode[endPos] == '{') {
            braceCount++;
        } else if (sourceCode[endPos] == '}') {
            braceCount--;
        }
        endPos++;
    }
    
    if (braceCount != 0) {
        // Las llaves no están balanceadas
        return "{}";
    }
    
    return sourceCode.substr(startPos, endPos - startPos);
}

std::string FunctionExtractor::analyzeComplexity(const std::string& code) {
    // Patrones para detectar estructuras de control
    std::regex forRegex("\\bfor\\b");
    std::regex whileRegex("\\bwhile\\b");
    
    // Contar bucles
    auto forBegin = std::sregex_iterator(code.begin(), code.end(), forRegex);
    auto forEnd = std::sregex_iterator();
    int forCount = std::distance(forBegin, forEnd);
    
    auto whileBegin = std::sregex_iterator(code.begin(), code.end(), whileRegex);
    auto whileEnd = std::sregex_iterator();
    int whileCount = std::distance(whileBegin, whileEnd);
    
    int loops = forCount + whileCount;
    
    // Detectar bucles anidados
    std::regex nestedLoopPattern("for[^{]*\\{[^}]*for|while[^{]*\\{[^}]*for|for[^{]*\\{[^}]*while|while[^{]*\\{[^}]*while");
    auto nestedLoopBegin = std::sregex_iterator(code.begin(), code.end(), nestedLoopPattern);
    auto nestedLoopEnd = std::sregex_iterator();
    int nestedLoops = std::distance(nestedLoopBegin, nestedLoopEnd);
    
    // Detectar recursión
    std::regex functionNamePattern("(\\w+)\\s*\\([^)]*\\)\\s*\\{");
    std::smatch nameMatch;
    bool hasRecursion = false;
    
    if (std::regex_search(code, nameMatch, functionNamePattern)) {
        std::string funcName = nameMatch[1];
        std::string funcBody = code.substr(nameMatch.position() + nameMatch.length());
        
        std::regex recursiveCallPattern("\\b" + funcName + "\\s*\\(");
        auto recursiveCallBegin = std::sregex_iterator(funcBody.begin(), funcBody.end(), recursiveCallPattern);
        auto recursiveCallEnd = std::sregex_iterator();
        hasRecursion = std::distance(recursiveCallBegin, recursiveCallEnd) > 0;
    }
    
    // Analizar la complejidad
    if (hasRecursion) {
        return "O(2^n)";  // Recursión simple (aproximación)
    } else if (nestedLoops > 0) {
        int depth = nestedLoops + 1; // Aproximación de la profundidad de anidación
        return "O(n^" + std::to_string(depth) + ")";
    } else if (loops > 0) {
        return "O(n)";
    } else {
        return "O(1)";
    }
}

bool FunctionExtractor::saveToCSV(const std::vector<Function>& functions, const std::string& outputPath) {
    try {
        std::ofstream outputFile(outputPath);
        if (!outputFile.is_open()) {
            std::cerr << "No se pudo crear el archivo CSV: " << outputPath << std::endl;
            return false;
        }
        
        // Escribir encabezado
        outputFile << "Nombre,Tipo de retorno,Parámetros,Complejidad\n";
        
        // Escribir datos de cada función
        for (const Function& func : functions) {
            // Escapar comillas en parámetros
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
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error al guardar el CSV: " << e.what() << std::endl;
        return false;
    }
}