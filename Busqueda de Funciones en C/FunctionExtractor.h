#pragma once 
#include <vector> 
#include <string>

using namespace std;

struct Function {
    string name;
    string returnType;
    string parameters;
    string body;
    string complexity;
};

class FunctionExtractor {
    public:
    // Constructor
    FunctionExtractor();
    
    // Extraer funciones de un archivo
    std::vector<Function> extractFromFile(const std::string& filePath);
    
    // Guardar resultados en CSV
    bool saveToCSV(const std::vector<Function>& functions, const std::string& outputPath);
    
private:
    // Leer contenido completo de un archivo
    std::string readFile(const std::string& filePath);
    
    // Extraer funciones del código fuente
    std::vector<Function> extractFunctions(const std::string& sourceCode);
    
    // Analizar complejidad Big O de una función
    std::string analyzeComplexity(const std::string& code);
    
    // Extraer el cuerpo completo de una función con anidación de llaves balanceada
    std::string extractFunctionBody(const std::string& sourceCode, size_t startPos);
};


