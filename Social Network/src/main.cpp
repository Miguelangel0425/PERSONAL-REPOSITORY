#include "SocialGraph.h"
#include "GUI.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <locale>
#include <conio.h> // Para _getch() en Windows
#include <vector>

// Definiciones de longitud mínima y máxima para el nombre de usuario y la contraseña
const int MIN_USERNAME_LENGTH = 3;
const int MAX_USERNAME_LENGTH = 20;
const int MIN_PASSWORD_LENGTH = 6;
const int MAX_PASSWORD_LENGTH = 30;

// Definiciones para teclas especiales
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_W 119
#define KEY_w 87
#define KEY_S 115
#define KEY_s 83
#define KEY_ENTER 13
#define KEY_ESC 27

namespace fs = std::filesystem;

// Función para leer una tecla sin esperar Enter
int leerTecla() {
    #ifdef _WIN32
        return _getch();
    #else
        // Implementación para sistemas Unix/Linux
        system("stty raw -echo");
        int ch = getchar();
        system("stty cooked echo");
        return ch;
    #endif
}

// Función para mostrar el menú con la opción seleccionada
void mostrarMenu(int opcionSeleccionada) {
    // Limpiar pantalla
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    std::cout << "\n=============================================" << std::endl;
    std::cout << "          RED SOCIAL - MENU PRINCIPAL        " << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "  Navegue con las teclas W/S o flechas arriba/abajo   " << std::endl;
    std::cout << "       Presione ENTER para seleccionar       " << std::endl;
    std::cout << "=============================================" << std::endl;
    
    // Opciones del menú con resaltado para la opción seleccionada
    std::vector<std::string> opciones = {
        "Iniciar aplicacion grafica",
        "Ver manual de usuario",
        "Crear backup de datos",
        "Restaurar backup",
        "Salir"
    };
    
    for (int i = 0; i < opciones.size(); i++) {
        if (i + 1 == opcionSeleccionada) {
            std::cout << "-> " << i + 1 << ". " << opciones[i] << " <-" << std::endl;
        } else {
            std::cout << "  " << i + 1 << ". " << opciones[i] << "  " << std::endl;
        }
    }
    
    std::cout << "\nUse W/S o las flechas para moverse. ENTER para seleccionar." << std::endl;
}

// Función para mostrar el manual de usuario
void mostrarManualUsuario() {
    // Limpiar pantalla
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    std::cout << "\n=============================================" << std::endl;
    std::cout << "          MANUAL DE USUARIO                 " << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "\nBienvenido a la aplicacion de Red Social" << std::endl;
    std::cout << "\n1. INICIO DE SESIÓN:" << std::endl;
    std::cout << "   - Ingrese su nombre de usuario y contraseña en los campos correspondientes." << std::endl;
    std::cout << "   - Haga clic en 'Login' para acceder a su cuenta." << std::endl;
    std::cout << "   - Si no tiene una cuenta, haga clic en 'Register'." << std::endl;
    
    std::cout << "\n2. REGISTRO DE USUARIO:" << std::endl;
    std::cout << "   - Complete los campos de nombre de usuario y contrasenia." << std::endl;
    std::cout << "   - Confirme su contrasenia en el campo correspondiente." << std::endl;
    std::cout << "   - El nombre de usuario debe tener entre " << MIN_USERNAME_LENGTH << " y " << MAX_USERNAME_LENGTH << " caracteres." << std::endl;
    std::cout << "   - La contrasenia debe tener entre " << MIN_PASSWORD_LENGTH << " y " << MAX_PASSWORD_LENGTH << " caracteres." << std::endl;
    std::cout << "   - Haga clic en 'Create Account' para registrarse." << std::endl;
    
    std::cout << "\n3. PANTALLA PRINCIPAL:" << std::endl;
    std::cout << "   - En el panel izquierdo vera la lista de sus amigos." << std::endl;
    std::cout << "   - En el panel central puede crear y ver publicaciones." << std::endl;
    std::cout << "   - Para crear una publicación, escriba en el cuadro de texto y haga clic en 'Post'." << std::endl;
    std::cout << "   - Sus publicaciones apareceran en orden cronologico debajo del area de creacion." << std::endl;
    std::cout << "   - Para cerrar sesion, haga clic en 'Logout' en la esquina superior derecha." << std::endl;
    
    std::cout << "\n4. GESTION DE BACKUPS:" << std::endl;
    std::cout << "   - Los datos se guardan automaticamente al salir de la aplicacion." << std::endl;
    std::cout << "   - Puede crear copias de seguridad adicionales desde el menú principal." << std::endl;
    std::cout << "   - Para restaurar un backup, seleccione la opción correspondiente en el menú." << std::endl;
    
    std::cout << "\nPresione cualquier tecla para volver al menú principal...";
    leerTecla(); // Espera una tecla sin necesidad de Enter
}

// Función para crear un backup
bool crearBackup(const SocialGraph& socialNetwork) {
    try {
        // Limpiar pantalla
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        std::cout << "\n=============================================" << std::endl;
        std::cout << "          CREACION DE BACKUP                " << std::endl;
        std::cout << "=============================================" << std::endl;
        
        // Crear directorio de backups si no existe
        if (!fs::exists("backups")) {
            fs::create_directory("backups");
        }
        
        // Obtener fecha y hora actual para el nombre del archivo
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y%m%d_%H%M%S");
        
        // Crear nombre del archivo de backup
        std::string backupPath = "backups/social_network_" + ss.str() + ".json";
        
        // Guardar datos en el archivo de backup
        socialNetwork.saveToFile(backupPath);
        
        std::cout << "\nBackup creado exitosamente en: " << std::endl;
        std::cout << fs::absolute(backupPath).string() << std::endl;
        std::cout << "\nPresione cualquier tecla para continuar...";
        leerTecla();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "\nError al crear backup: " << e.what() << std::endl;
        std::cout << "\nPresione cualquier tecla para continuar...";
        leerTecla();
        return false;
    }
}

// Función para listar backups disponibles y devolver el vector de rutas
std::vector<std::string> listarBackups() {
    std::vector<std::string> backups;
    
    // Limpiar pantalla
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    std::cout << "\n=============================================" << std::endl;
    std::cout << "          RESTAURACION DE BACKUP            " << std::endl;
    std::cout << "=============================================" << std::endl;
    
    try {
        if (!fs::exists("backups")) {
            std::cout << "\nNo se encontro el directorio de backups." << std::endl;
            return backups;
        }
        
        // Listar todos los archivos .json en el directorio de backups
        std::cout << "\nBackups disponibles:" << std::endl;
        std::cout << "-----------------------" << std::endl;
        int index = 1;
        
        for (const auto& entry : fs::directory_iterator("backups")) {
            if (entry.path().extension() == ".json") {
                std::string filename = entry.path().filename().string();
                backups.push_back(entry.path().string());
                
                // Formatear la fecha del nombre del archivo para mostrarla
                std::string dateStr = filename.substr(14, 8); // Extraer YYYYMMDD
                std::string timeStr = filename.substr(23, 6); // Extraer HHMMSS
                
                if (dateStr.length() == 8 && timeStr.length() == 6) {
                    std::cout << index << ". " << "Fecha: " 
                              << dateStr.substr(0, 4) << "-" << dateStr.substr(4, 2) << "-" << dateStr.substr(6, 2)
                              << " Hora: " << timeStr.substr(0, 2) << ":" << timeStr.substr(2, 2) << ":" << timeStr.substr(4, 2)
                              << std::endl;
                } else {
                    std::cout << index << ". " << filename << std::endl;
                }
                
                index++;
            }
        }
        
        if (backups.empty()) {
            std::cout << "\nNo se encontraron backups disponibles." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "\nError al listar backups: " << e.what() << std::endl;
    }
    
    return backups;
}

// Función para seleccionar un backup usando teclas de navegación
int seleccionarBackup(const std::vector<std::string>& backups) {
    if (backups.empty()) {
        std::cout << "\nPresione cualquier tecla para continuar...";
        leerTecla();
        return -1;
    }
    
    int seleccion = 1;
    int tecla;
    bool seleccionado = false;
    
    while (!seleccionado) {
        // Limpiar pantalla
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        std::cout << "\n=============================================" << std::endl;
        std::cout << "          SELECCION DE BACKUP               " << std::endl;
        std::cout << "=============================================" << std::endl;
        std::cout << "  Navegue con las teclas W/S o flechas ↑/↓   " << std::endl;
        std::cout << "       Presione ENTER para seleccionar       " << std::endl;
        std::cout << "          ESC para cancelar                  " << std::endl;
        std::cout << "=============================================" << std::endl;
        
        std::cout << "\nBackups disponibles:" << std::endl;
        std::cout << "-----------------------" << std::endl;
        
        for (int i = 0; i < backups.size(); i++) {
            std::string filename = fs::path(backups[i]).filename().string();
            std::string dateStr = filename.substr(14, 8); // Extraer YYYYMMDD
            std::string timeStr = filename.substr(23, 6); // Extraer HHMMSS
            
            if (i + 1 == seleccion) {
                std::cout << "-> " << i + 1 << ". ";
            } else {
                std::cout << "  " << i + 1 << ". ";
            }
            
            if (dateStr.length() == 8 && timeStr.length() == 6) {
                std::cout << "Fecha: " 
                          << dateStr.substr(0, 4) << "-" << dateStr.substr(4, 2) << "-" << dateStr.substr(6, 2)
                          << " Hora: " << timeStr.substr(0, 2) << ":" << timeStr.substr(2, 2) << ":" << timeStr.substr(4, 2);
            } else {
                std::cout << filename;
            }
            
            if (i + 1 == seleccion) {
                std::cout << " <-" << std::endl;
            } else {
                std::cout << std::endl;
            }
        }
        
        std::cout << "\nUse W/S o las flechas para moverse. ENTER para seleccionar. ESC para cancelar." << std::endl;
        
        // Leer tecla sin esperar Enter
        tecla = leerTecla();
        
        // Si es una tecla de flecha en Windows, _getch() devuelve primero 224 y luego el código de la flecha
        if (tecla == 224 || tecla == 0) {
            tecla = leerTecla();
        }
        
        // Procesar la tecla
        switch (tecla) {
            case KEY_UP:
            case KEY_W:
            case KEY_w:
                seleccion = (seleccion > 1) ? seleccion - 1 : backups.size();
                break;
            case KEY_DOWN:
            case KEY_S:
            case KEY_s:
                seleccion = (seleccion < backups.size()) ? seleccion + 1 : 1;
                break;
            case KEY_ENTER:
                seleccionado = true;
                break;
            case KEY_ESC:
                return -1; // Cancelar
        }
    }
    
    return seleccion;
}

// Función para restaurar un backup
bool restaurarBackup(SocialGraph& socialNetwork, const std::string& backupPath) {
    try {
        // Limpiar pantalla
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        std::cout << "\n=============================================" << std::endl;
        std::cout << "          RESTAURACION DE BACKUP            " << std::endl;
        std::cout << "=============================================" << std::endl;
        
        // Verificar si el archivo existe
        if (!fs::exists(backupPath)) {
            std::cerr << "\nEl archivo de backup no existe: " << backupPath << std::endl;
            std::cout << "\nPresione cualquier tecla para continuar...";
            leerTecla();
            return false;
        }
        
        // Pedir confirmación
        std::string filename = fs::path(backupPath).filename().string();
        std::string displayName = filename;
        
        // Formatear el nombre para mostrarlo sin guiones bajos
        if (filename.substr(0, 14) == "social_network_" && filename.length() >= 30) {
            std::string dateStr = filename.substr(14, 8); // Extraer YYYYMMDD
            std::string timeStr = filename.substr(23, 6); // Extraer HHMMSS
            
            if (dateStr.length() == 8 && timeStr.length() == 6) {
                displayName = "social_network " 
                          + dateStr.substr(0, 4) + "-" + dateStr.substr(4, 2) + "-" + dateStr.substr(6, 2)
                          + " " + timeStr.substr(0, 2) + ":" + timeStr.substr(2, 2) + ":" + timeStr.substr(4, 2)
                          + ".json";
            }
        }
        
        std::cout << "\n¡ADVERTENCIA! Esta accion reemplazara todos los datos actuales." << std::endl;
        std::cout << "Backup a restaurar: " << displayName << std::endl;
        std::cout << "\n¿Está seguro de que desea continuar? (s/n): ";
        
        char confirmacion = leerTecla();
        if (confirmacion != 's' && confirmacion != 'S') {
            std::cout << "\nRestauracion cancelada." << std::endl;
            std::cout << "\nPresione cualquier tecla para continuar...";
            leerTecla();
            return false;
        }
        
        // Hacer una copia del archivo actual antes de restaurar (por seguridad)
        std::string currentDataPath = "social_network.json";
        if (fs::exists(currentDataPath)) {
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            std::stringstream ss;
            ss << std::put_time(std::localtime(&time), "%Y%m%d_%H%M%S");
            
            std::string backupCurrentPath = "backups/pre_restore_" + ss.str() + ".json";
            fs::copy_file(currentDataPath, backupCurrentPath);
            std::cout << "\nSe ha creado una copia de seguridad de los datos actuales en: " 
                      << fs::absolute(backupCurrentPath).string() << std::endl;
        }
        
        // Cargar datos desde el backup
        socialNetwork.loadFromFile(backupPath);
        
        // Guardar los datos restaurados como datos actuales
        socialNetwork.saveToFile(currentDataPath);
        
        std::cout << "\nBackup restaurado exitosamente desde: " << displayName << std::endl;
        std::cout << "\nPresione cualquier tecla para continuar...";
        leerTecla();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "\nError al restaurar backup: " << e.what() << std::endl;
        std::cout << "\nPresione cualquier tecla para continuar...";
        leerTecla();
        return false;
    }
}

// Función principal modificada con menú de opciones navegable con teclas
int main() {
    try {
        // Configurar locale para manejar caracteres especiales
        try {
            std::locale::global(std::locale("en_US.UTF-8"));
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
        
        std::cout << "Presione cualquier tecla para continuar...";
        leerTecla();
        
        bool salir = false;
        int opcionSeleccionada = 1;
        int tecla;
        
        while (!salir) {
            // Mostrar menú con la opción seleccionada
            mostrarMenu(opcionSeleccionada);
            
            // Leer tecla sin esperar Enter
            tecla = leerTecla();
            
            // Si es una tecla de flecha en Windows, _getch() devuelve primero 224 y luego el código de la flecha
            if (tecla == 224 || tecla == 0) {
                tecla = leerTecla();
            }
            
            // Procesar la tecla
            switch (tecla) {
                case KEY_UP:
                case KEY_W:
                case KEY_w:
                    opcionSeleccionada = (opcionSeleccionada > 1) ? opcionSeleccionada - 1 : 5;
                    break;
                case KEY_DOWN:
                case KEY_S:
                case KEY_s:
                    opcionSeleccionada = (opcionSeleccionada < 5) ? opcionSeleccionada + 1 : 1;
                    break;
                case KEY_ENTER:
                    // Ejecutar la opción seleccionada
                    switch (opcionSeleccionada) {
                        case 1: {
                            // Limpiar pantalla
                            #ifdef _WIN32
                                system("cls");
                            #else
                                system("clear");
                            #endif
                            
                            std::cout << "Iniciando aplicación gráfica..." << std::endl;
                            
                            // Inicializar y ejecutar la GUI
                            GUI gui(socialNetwork);
                            gui.run();
                            
                            // Guardar datos después de cerrar la GUI
                            try {
                                std::string jsonPath = "social_network.json";
                                std::cout << "Guardando datos en: " << fs::absolute(jsonPath).string() << std::endl;
                                socialNetwork.saveToFile(jsonPath);
                                std::cout << "Datos guardados exitosamente." << std::endl;
                                std::cout << "\nPresione cualquier tecla para continuar...";
                                leerTecla();
                            } catch (const std::exception& e) {
                                std::cerr << "Error al guardar los datos: " << e.what() << std::endl;
                                std::cout << "\nPresione cualquier tecla para continuar...";
                                leerTecla();
                            }
                            break;
                        }
                        
                        case 2:
                            mostrarManualUsuario();
                            break;
                        
                        case 3:
                            crearBackup(socialNetwork);
                            break;
                        
                        case 4: {
                            std::vector<std::string> backups = listarBackups();
                            int seleccion = seleccionarBackup(backups);
                            
                            if (seleccion > 0 && seleccion <= backups.size()) {
                                restaurarBackup(socialNetwork, backups[seleccion - 1]);
                            }
                            break;
                        }
                        
                        case 5:
                            salir = true;
                            // Limpiar pantalla
                            #ifdef _WIN32
                                system("cls");
                            #else
                                system("clear");
                            #endif
                            
                            std::cout << "\nGuardando datos antes de salir..." << std::endl;
                            try {
                                std::string jsonPath = "social_network.json";
                                socialNetwork.saveToFile(jsonPath);
                                std::cout << "Datos guardados exitosamente." << std::endl;
                            } catch (const std::exception& e) {
                                std::cerr << "Error al guardar los datos: " << e.what() << std::endl;
                            }
                            std::cout << "\n¡Gracias por usar la aplicacion!" << std::endl;
                            break;
                    }
                    break;
            }
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