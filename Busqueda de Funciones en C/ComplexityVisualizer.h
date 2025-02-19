#pragma once 
#include <vector>   
#include <string>
#include "FunctionExtractor.h"

// Clase para generar comandos de visualización para Python y MATLAB
class ComplexityVisualizer {
public:
    // Constructor
    ComplexityVisualizer();
    
    bool generatePythonScript(const std::string& csvPath, const std::string& scriptPath);
    bool generateMatlabScript(const std::string& csvPath, const std::string& scriptPath);
    
private:
    // Plantilla para el script de Python
    std::string getPythonTemplate() const;
    
    // Plantilla para el script de MATLAB
    std::string getMatlabTemplate() const;
};