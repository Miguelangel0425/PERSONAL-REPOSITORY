#include "SocialGraph.h"
#include <iostream>
#include <stdexcept>
#include "GUI.h"
#include <filesystem>
#include <locale>

namespace fs = std::filesystem;

// Función para mostrar el hash de una contraseña (para depuración)
extern std::string hashPassword(const std::string &password);

int main() {
    try {
        // Configurar locale para manejar caracteres especiales - con manejo de errores
        try {
            std::locale::global(std::locale(""));
            std::cout.imbue(std::locale());
            std::cout << "Locale configurado exitosamente." << std::endl;
        } catch(const std::exception& e) {
            std::cerr << "Advertencia: No se pudo configurar el locale: " << e.what() << std::endl;
            std::cerr << "Utilizando locale C por defecto" << std::endl;
            std::locale::global(std::locale("C"));
            std::cout.imbue(std::locale());
        }
        
        // Inicializar la red social
        SocialGraph socialNetwork;
        
        // Intentar cargar datos guardados
        try {
            std::string jsonPath = "social_network.json";
            std::cout << "Intentando cargar datos desde: " << fs::absolute(jsonPath).string() << std::endl;
            socialNetwork.loadFromFile(jsonPath);
            std::cout << "Datos cargados exitosamente." << std::endl;
        } catch (const std::exception& e) {
            std::cout << "No se encontraron datos guardados o error al cargar: " << e.what() << std::endl;
            std::cout << "Creando nueva red social." << std::endl;
            
        }
        
        // Inicializar y ejecutar la GUI
        GUI gui(socialNetwork);
        
        // Ejecutar la aplicación
        gui.run();
        
        // Guardar datos antes de salir
        try {
            std::string jsonPath = "social_network.json";
            std::cout << "Guardando datos en: " << fs::absolute(jsonPath).string() << std::endl;
            socialNetwork.saveToFile(jsonPath);
            std::cout << "Datos guardados exitosamente." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error al guardar los datos: " << e.what() << std::endl;
        }
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error fatal: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Error desconocido" << std::endl;
        return 1;
    }
}