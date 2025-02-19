#include <iostream>
#include <string>
#include <iomanip>
#include "FunctionExtractor.h"
#include "ComplexityVisualizer.h"

void printUsage() {
    std::cout << "Analizador de Complejidad de Funciones C" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Uso: ./analizador_complejidad <archivo_c>" << std::endl;
    std::cout << "Ejemplo: ./analizador_complejidad ejemplo.c" << std::endl;
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
    // Verificar argumentos
    if (argc < 2) {
        printUsage();
        std::cout << "\nIntroduce la ruta del archivo C a analizar: ";
        std::string filePath;
        std::getline(std::cin, filePath);
        if (filePath.empty()) {
            std::cerr << "No se especificó ningún archivo. Saliendo..." << std::endl;
            return 1;
        }
    }
    
    // Obtener ruta del archivo
    std::string filePath = (argc >= 2) ? argv[1] : "";
    std::string csvPath = "funciones_extraidas.csv";
    std::string pythonScript = "visualizar_complejidad.py";
    std::string matlabScript = "visualizar_complejidad.m";
    
    try {
        // Crear instancia del extractor
        FunctionExtractor extractor;
        
        // Extraer funciones
        std::cout << "Analizando archivo: " << filePath << std::endl;
        std::vector<Function> functions = extractor.extractFromFile(filePath);
        
        if (functions.empty()) {
            std::cerr << "No se encontraron funciones en el archivo." << std::endl;
            return 1;
        }
        
        // Mostrar resumen de funciones encontradas
        printFunctionSummary(functions);
        
        // Guardar resultados en CSV
        if (extractor.saveToCSV(functions, csvPath)) {
            std::cout << "\nResultados guardados en: " << csvPath << std::endl;
        } else {
            std::cerr << "Error al guardar resultados en CSV." << std::endl;
            return 1;
        }
        
        // Generar scripts de visualización
        ComplexityVisualizer visualizer;
        visualizer.generatePythonScript(csvPath, pythonScript);
        visualizer.generateMatlabScript(csvPath, matlabScript);
        
        // Mostrar instrucciones para visualización
        std::cout << "\nPara visualizar los resultados:" << std::endl;
        std::cout << "1. Ejecutar script Python: python " << pythonScript << std::endl;
        std::cout << "2. Ejecutar script MATLAB: matlab -r \"run('" << matlabScript << "')\"" << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}