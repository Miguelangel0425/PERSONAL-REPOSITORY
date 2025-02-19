#include <iostream>
#include <string>
#include <iomanip>
#include "FunctionExtractor.h"
#include <chrono>

void printUsage() {
    std::cout << "Analizador de Complejidad de Funciones C++" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Uso: ./analizador_complejidad <archivo>" << std::endl;
    std::cout << "Ejemplo: ./analizador_complejidad ejemplo.cpp" << std::endl;
}

void printFunctionSummary(const std::vector<Function>& functions) {
    std::cout << "\nSe encontraron " << functions.size() << " funciones:\n";
    std::cout << "----------------------------------------------\n";
    std::cout << std::left << std::setw(20) << "NOMBRE" << std::setw(20) << "TIPO RETORNO" 
              << std::setw(15) << "COMPLEJIDAD" << std::endl;
    std::cout << "----------------------------------------------\n";
    
    for (const Function& func : functions) {
        std::cout << std::left << std::setw(20) << func.name 
                  << std::setw(20) << func.returnType 
                  << std::setw(15) << func.complexity << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::string filePath;
    
    if (argc < 2) {
        printUsage();
        std::cout << "\nIntroduce la ruta del archivo a analizar: ";
        std::getline(std::cin, filePath);
        if (filePath.empty()) {
            std::cerr << "No se especificó ningún archivo. Saliendo..." << std::endl;
            return 1;
        }
    } else {
        filePath = argv[1];
    }
    
    std::string csvPath = "funciones_extraidas.csv";
    
    try {
        std::cout << "=== Iniciando análisis ===" << std::endl;
        auto startTime = std::chrono::high_resolution_clock::now();
        
        FunctionExtractor extractor;
        std::cout << "Analizando archivo: " << filePath << std::endl;
        std::vector<Function> functions = extractor.extractFromFile(filePath);
        
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout << "Tiempo de analisis: " << duration << " ms" << std::endl;
        
        if (functions.empty()) {
            std::cerr << "No se encontraron funciones en el archivo." << std::endl;
            return 1;
        }
        
        printFunctionSummary(functions);
        
        if (extractor.saveToCSV(functions, csvPath)) {
            std::cout << "\nResultados guardados en: " << csvPath << std::endl;
            std::cout << "\nPara visualizar los resultados, ejecute:" << std::endl;
            std::cout << "python visualizar_complejidad.py " << csvPath << std::endl;
        } else {
            std::cerr << "Error al guardar resultados en CSV." << std::endl;
            return 1;
        }
        
        std::cout << "=== Análisis completado ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error fatal: " << e.what() << std::endl;
        return 1;
    }
}