#pragma once 
#include <vector> 
#include <string>
#include <unordered_set>

struct Function {
    std::string name;
    std::string returnType;
    std::string parameters;
    std::string body;
    std::string complexity;
};

class FunctionExtractor {
public:
    FunctionExtractor();
    std::vector<Function> extractFromFile(const std::string& filePath);
    bool saveToCSV(const std::vector<Function>& functions, const std::string& outputPath);
    
private:
    std::string readFile(const std::string& filePath);
    std::vector<Function> extractFunctions(const std::string& sourceCode);
    std::string analyzeComplexity(const std::string& code);
    std::string extractFunctionBody(const std::string& sourceCode, size_t startPos);
    bool isValidSourceFile(const std::string& filePath);
    bool fileExists(const std::string &filePath);
    std::streamsize getFileSize(const std::string &filePath);
    bool isBinaryFile(const std::string &filePath);
    std::string analyzeBinaryFile(const std::string& filePath);
};