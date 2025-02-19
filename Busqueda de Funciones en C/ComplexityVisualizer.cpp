#include "ComplexityVisualizer.h"
#include <fstream>
#include <iostream>

ComplexityVisualizer::ComplexityVisualizer() {
    // Inicialización si es necesaria
}

bool ComplexityVisualizer::generatePythonScript(const std::string& csvPath, const std::string& outputPath) {
    try {
        std::ofstream scriptFile(outputPath);
        if (!scriptFile.is_open()) {
            std::cerr << "No se pudo crear el archivo de script Python: " << outputPath << std::endl;
            return false;
        }
        
        // Obtener plantilla y reemplazar la ruta del CSV
        std::string scriptContent = getPythonTemplate();
        size_t pos = scriptContent.find("CSV_FILE_PATH");
        if (pos != std::string::npos) {
            scriptContent.replace(pos, 13, "'" + csvPath + "'");
        }
        
        scriptFile << scriptContent;
        scriptFile.close();
        
        std::cout << "Script de Python generado: " << outputPath << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error al generar script Python: " << e.what() << std::endl;
        return false;
    }
}

bool ComplexityVisualizer::generateMatlabScript(const std::string& csvPath, const std::string& outputPath) {
    try {
        std::ofstream scriptFile(outputPath);
        if (!scriptFile.is_open()) {
            std::cerr << "No se pudo crear el archivo de script MATLAB: " << outputPath << std::endl;
            return false;
        }
        
        // Obtener plantilla y reemplazar la ruta del CSV
        std::string scriptContent = getMatlabTemplate();
        size_t pos = scriptContent.find("CSV_FILE_PATH");
        if (pos != std::string::npos) {
            scriptContent.replace(pos, 13, "'" + csvPath + "'");
        }
        
        scriptFile << scriptContent;
        scriptFile.close();
        
        std::cout << "Script de MATLAB generado: " << outputPath << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error al generar script MATLAB: " << e.what() << std::endl;
        return false;
    }
}

std::string ComplexityVisualizer::getPythonTemplate() const {
    return R"(import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys

def generate_complexity_points(complexity_type, n_values):
    """Genera puntos y valores para diferentes notaciones Big O"""
    y_values = []
    
    for n in n_values:
        if complexity_type == "O(1)":
            y_values.append(1)
        elif complexity_type == "O(log n)":
            y_values.append(np.log(n))
        elif complexity_type == "O(n)":
            y_values.append(n)
        elif complexity_type == "O(n log n)":
            y_values.append(n * np.log(n))
        elif complexity_type.startswith("O(n^"):
            power = int(complexity_type[4:-1])
            y_values.append(n**power)
        elif complexity_type == "O(2^n)":
            if n <= 30:  # Limitar para evitar overflow
                y_values.append(2**n)
            else:
                y_values.append(float('inf'))
        else:
            # Caso predeterminado
            y_values.append(n)
    
    return y_values

def plot_complexity(csv_file):
    """Genera gráficos de complejidad basados en el CSV generado por el programa C++"""
    try:
        # Cargar datos del CSV
        df = pd.read_csv(csv_file)
        
        if len(df) == 0:
            print("No se encontraron funciones para analizar.")
            return
        
        print(f"Analizando {len(df)} funciones...")
        
        # Generar valores para el eje X (tamaño de entrada)
        n_values = np.linspace(1, 100, 100)
        
        # Configurar el gráfico
        plt.figure(figsize=(14, 10))
        
        # Diferentes estilos de línea para distinguir mejor las funciones
        line_styles = ['-', '--', '-.', ':', '-', '--', '-.']
        markers = ['o', 's', '^', 'D', 'v', '<', '>']
        
        # Procesar cada función encontrada
        for i, (idx, row) in enumerate(df.iterrows()):
            func_name = row['Nombre']
            complexity = row['Complejidad']
            
            # Generar puntos para esta función
            y_values = generate_complexity_points(complexity, n_values)
            
            # Determinar el estilo de línea y marcador
            line_style = line_styles[i % len(line_styles)]
            marker = markers[i % len(markers)]
            
            # Agregar al gráfico con muestreo para no saturar la visualización
            plt.plot(
                n_values[::10],  # Muestreo cada 10 puntos
                [y for i, y in enumerate(y_values) if i % 10 == 0],
                label=f"{func_name}: {complexity}",
                linestyle=line_style,
                marker=marker,
                markersize=4
            )
        
        # Configurar etiquetas y leyendas
        plt.title('Análisis de Complejidad Big O por Función', fontsize=16)
        plt.xlabel('Tamaño de entrada (n)', fontsize=14)
        plt.ylabel('Número de operaciones', fontsize=14)
        plt.grid(True, alpha=0.3)
        plt.legend(loc='upper left', fontsize=10)
        
        # Usar escala logarítmica para el eje Y para mejor visualización
        plt.yscale('log')
        
        # Guardar el gráfico
        plt.tight_layout()
        plt.savefig('complejidad_funciones.png', dpi=300)
        plt.show()
        
        print(f"Gráfico guardado como 'complejidad_funciones.png'")
        
        return True
    
    except Exception as e:
        print(f"Error al generar el gráfico: {str(e)}")
        return False

if __name__ == "__main__":
    # Usar el archivo CSV proporcionado
    csv_file = CSV_FILE_PATH
    
    if len(sys.argv) > 1:
        csv_file = sys.argv[1]
    
    plot_complexity(csv_file)
)";
}

std::string ComplexityVisualizer::getMatlabTemplate() const {
    return R"(function plotComplexityFromCSV(csvFile)
% PLOTCOMPLEXITYFROMCSV Genera un gráfico de complejidad Big O basado en datos CSV
%   Esta función lee un archivo CSV generado por el extractor de funciones C++
%   y crea un gráfico que muestra la complejidad computacional de cada función.

    % Verificar si existe el archivo
    if ~exist(csvFile, 'file')
        error('El archivo CSV no existe: %s', csvFile);
    end
    
    % Leer los datos del CSV
    data = readtable(csvFile);
    
    if height(data) == 0
        error('No se encontraron funciones para analizar.');
    end
    
    fprintf('Analizando %d funciones...\n', height(data));
    
    % Generar valores para el eje X (tamaño de entrada)
    n_values = linspace(1, 100, 100);
    
    % Crear una nueva figura
    figure('Position', [100, 100, 1000, 700]);
    
    % Diferentes estilos de línea y marcadores
    lineStyles = {'-', '--', ':', '-.', '-', '--', ':'};
    markers = {'o', 's', 'd', '^', 'v', '>', '<'};
    
    % Procesar cada función
    hold on;
    for i = 1:height(data)
        funcName = data.Nombre{i};
        complexity = data.Complejidad{i};
        
        % Generar puntos para esta complejidad
        y_values = generateComplexityPoints(complexity, n_values);
        
        % Determinar estilo de línea y marcador
        lineIdx = mod(i-1, length(lineStyles)) + 1;
        markerIdx = mod(i-1, length(markers)) + 1;
        
        % Muestrear puntos para no saturar el gráfico
        sampleIdx = 1:5:length(n_values);
        
        % Graficar con estilo único
        plot(n_values(sampleIdx), y_values(sampleIdx), ...
             [lineStyles{lineIdx}, markers{markerIdx}], ...
             'LineWidth', 1.5, ...
             'MarkerSize', 6, ...
             'DisplayName', sprintf('%s: %s', funcName, complexity));
    end
    hold off;
    
    % Configurar etiquetas y leyenda
    title('Análisis de Complejidad Big O por Función', 'FontSize', 16);
    xlabel('Tamaño de entrada (n)', 'FontSize', 14);
    ylabel('Número de operaciones', 'FontSize', 14);
    grid on;
    legend('Location', 'northwest', 'FontSize', 10);
    
    % Usar escala logarítmica para el eje Y
    set(gca, 'YScale', 'log');
    
    % Guardar el gráfico
    saveas(gcf, 'complejidad_funciones_matlab.png');
    fprintf('Gráfico guardado como ''complejidad_funciones_matlab.png''\n');
end

function y_values = generateComplexityPoints(complexity_type, n_values)
% Genera puntos Y basados en diferentes notaciones Big O
    y_values = zeros(size(n_values));
    
    for i = 1:length(n_values)
        n = n_values(i);
        
        if strcmp(complexity_type, 'O(1)')
            y_values(i) = 1;
        elseif strcmp(complexity_type, 'O(log n)')
            y_values(i) = log(n);
        elseif strcmp(complexity_type, 'O(n)')
            y_values(i) = n;
        elseif strcmp(complexity_type, 'O(n log n)')
            y_values(i) = n * log(n);
        elseif startsWith(complexity_type, 'O(n^')
            % Extraer el exponente del string
            power_str = regexp(complexity_type, 'O\(n\^(\d+)\)', 'tokens');
            if ~isempty(power_str)
                power = str2double(power_str{1}{1});
                y_values(i) = n^power;
            else
                y_values(i) = n; % Default
            end
        elseif strcmp(complexity_type, 'O(2^n)')
            if n <= 30
                y_values(i) = 2^n;
            else
                y_values(i) = Inf; % Evitar overflow
            end
        else
            % Caso predeterminado
            y_values(i) = n;
        end
    end
end

% Llamada principal
csvFile = CSV_FILE_PATH;
plotComplexityFromCSV(csvFile);
)";
}
