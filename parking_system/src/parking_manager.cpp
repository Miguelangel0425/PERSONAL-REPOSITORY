#include "../include/parking_manager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
#include <random>   
#include <cmath>
#include "parking_manager.h"
#include "input_validator.h"
#include "history_manager.h"
#include "token_manager.h"
#include <filesystem>

ParkingManager::ParkingManager(const std::string& dataDir)
    : dataDir(dataDir), 
      vehiclesFile(dataDir + "vehicles.txt"),
      userRecordsFile(dataDir + "user_records.txt"),
      historyFile(dataDir + "parking_history.txt"), 
      historyManager(historyFile) { 
    loadVehiclesFromFile();
}

/**
 * @brief Maneja la entrada de un vehículo al sistema de estacionamiento.
 * 
 * Esta función solicita al usuario que ingrese la placa del vehículo y la valida.
 * Si la placa es inválida, notifica al usuario y sale. Si el vehículo ya está en el
 * estacionamiento, notifica al usuario y sale. Si el vehículo no está en el sistema,
 * solicita al usuario que ingrese los datos del propietario y el tipo de vehículo,
 * valida las entradas y agrega el vehículo al sistema. Finalmente, registra el evento
 * de entrada.
 * 
 * Pasos:
 * 1. Solicitar al usuario que ingrese la placa del vehículo.
 * 2. Validar la placa ingresada.
 * 3. Verificar si el vehículo ya está en el estacionamiento.
 * 4. Si el vehículo no está en el sistema, solicitar al usuario que ingrese los datos
 *    del propietario y el tipo de vehículo, validar las entradas y agregar el vehículo
 *    al sistema.
 * 5. Registrar el evento de entrada.
 * 6. Notificar al usuario y esperar a que presione una tecla para continuar.
 */
void ParkingManager::enterVehicle() {

    std::string plate;

    std::cout << "Ingrese placa (AAA000): ";
    plate = InputValidator::getValidatedPlate();


    if (!InputValidator::isValidPlate(plate)) {
        std::cout << "Placa invalida.\n";
        std::cout << "\nPresione cualquier tecla para continuar...";
        _getch();
        return;
    }


    auto eventos = historyManager.getAllEvents();
    auto ultimoEvento = std::find_if(eventos.rbegin(), eventos.rend(), 
        [&plate](const ParkingEvent& evento) { return evento.plate == plate; });

    
    if (ultimoEvento != eventos.rend() && ultimoEvento->eventType == "ENTRADA") {
        std::cout << "Este vehiculo ya esta en el parqueadero.\n";
        std::cout << "\nPresione cualquier tecla para continuar...";
        _getch();
        return;
    }

    auto vehicle = findVehicleByPlate(plate);

    if (vehicle) {

        historyManager.logEvent(plate, "ENTRADA");
        std::cout << "Vehiculo ingresado al parqueadero.\n";
        std::cout << "Datos del propietario:\n";
        std::cout << "Nombre: " << vehicle->getOwnerName() << std::endl;
        std::cout << "Cedula: " << vehicle->getOwnerID() << std::endl;
        std::cout << "Telefono: " << vehicle->getOwnerPhone() << std::endl;
    } else {

        std::string name, id, phone, type;

        while (true) {
            std::cout << "Nombre del propietario: ";
            name = InputValidator::getValidatedText();
            if (!InputValidator::validate(name, nameValidator)) {
                std::cout << "Nombre invalido. Solo letras.\n";
                continue;
            }
            break;
        }

        InputValidator validator;
        while (true) {
            std::cout << "Ingrese su Cedula: ";
            id = validator.getValidatedNumber();
            if (!InputValidator::isValidID(id)) {
                std::cout << "Cédula invalida. Debe tener 10 digitos.\n";
                continue;
            }
            break;
        }


        while (true) {
            std::cout << "Ingrese teléfono: ";
            phone = InputValidator::getValidatedNumber();
            if (!InputValidator::isValidPhone(phone)) {
                std::cout << "Telefono invalido. Debe tener 10 digitos.\n";
                continue;
            }
            break;
        }

        std::cout << "Ingrese tipo de vehiculo: ";
        type = InputValidator::getValidatedText();

        Vehicle newVehicle(plate, name, id, phone, type);
        vehicles.push_back(newVehicle);
        saveVehiclesToFile();
        saveUserRecord(newVehicle);
        historyManager.logEvent(plate, "ENTRADA");
    }

    std::cout << "\nPresione cualquier tecla para continuar...";
    _getch();
}


bool ParkingManager::registerVehicle() { 
std::string plate, name, id, phone, type; 

    std::cout << "Ingrese placa (AAA000): "; 
    InputValidator validator;
    plate = validator.getValidatedPlate();
    if(!InputValidator::validate(plate, plateValidator)) { 
        std::cout << "Placa invalida.\n"; 
        std::cout << "\nPresione cualquier tecla para continuar...";
        _getch();
        return false; 
    }

    while (true) { 
        std::cout << "Nombre del propietario: "; 
        name = validator.getValidatedText();
        if (!InputValidator::validate(name, nameValidator)) { 
            std::cout << "Nombre invalido. Solo letras.\n"; 
            continue; 
        } 
        break; 
    } 

    while (true) {
        std::cout << "Ingrese su Cedula: ";
        id = validator.getValidatedNumber();
        if (!InputValidator::isValidID(id)) {
            std::cout << "Cédula invalida. Debe tener 10 digitos.\n";
            continue;
        }
        break;
    }

    while (true) {
        std::cout << "Ingrese telefono: ";
        phone = validator.InputValidator::getValidatedNumber(); 
        if (!InputValidator::isValidPhone(phone)) {
            std::cout << "Telefono invalido. Debe tener 10 digitos.\n";
            continue;
        }
        break;
    }

    while (true) {
        std::cout << "Ingrese tipo de vehiculo: ";
        type = validator.InputValidator::getValidatedText(); 
        if (type.empty()) {
            std::cout << "Tipo de vehiculo no puede estar vacío.\n";
            continue;
        }
        break;
    }

    Vehicle newVehicle(plate, name, id, phone, type); 
    vehicles.push_back(newVehicle); 

    saveVehiclesToFile(); 
    historyManager.logEvent(plate, "ENTRADA"); 
    std::cout << "Vehiculo registrado exitosamente.\n"; 
    std::cout << "\nPresione cualquier tecla para continuar..."; 
    _getch(); 
    return true; 
}

bool ParkingManager::findVehicle() {
    std::string plate;

    std::cout << "Ingrese placa del vehiculo a buscar: ";
    plate = InputValidator::getValidatedPlate();

    // Validar formato de placa
    if (!InputValidator::isValidPlate(plate)) {
        std::cout << "Placa invalida.\n";
        std::cout << "\nPresione cualquier tecla para continuar...";
        _getch();
        return false;
    }

    auto vehicle = findVehicleByPlate(plate);

    if (vehicle) {
        std::cout << "Vehiculo encontrado:\n";
        std::cout << "Placa: " << vehicle->getPlate() << std::endl;
        std::cout << "Propietario: " << vehicle->getOwnerName() << std::endl;
        std::cout << "Cedula: " << vehicle->getOwnerID() << std::endl;
        std::cout << "Telefono: " << vehicle->getOwnerPhone() << std::endl;
        std::cout << "Tipo: " << vehicle->getVehicleType() << std::endl;
        std::cout << "\nPresione cualquier tecla para continuar...";
        _getch();
        return true;
    } else {
        std::cout << "Vehiculo no encontrado.\n";
        std::cout << "\nPresione cualquier tecla para continuar...";
        _getch();
        return false;
    }
}

std::unique_ptr<Vehicle> ParkingManager::findVehicleByPlate(const std::string& plate) {
    // Buscar primero en memoria
    auto it = std::find_if(vehicles.begin(), vehicles.end(),
        [&plate](const Vehicle& v) { return v.getPlate() == plate; });

    if (it != vehicles.end()) {
        return std::make_unique<Vehicle>(*it);
    }

    // Si no está en memoria, buscar en user_records.txt
    std::ifstream file(userRecordsFile);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            auto tokens = TokenManager::split(line, ',');
            if (tokens.size() >= 4 && tokens[3] == plate) {
                return std::make_unique<Vehicle>(
                    tokens[3], // plate
                    tokens[0], // owner_name
                    tokens[1], // owner_id
                    tokens[2], // owner_phone
                    "Unknown"  // Tipo desconocido
                );
            }
        }
        file.close();
    }
    return nullptr;
}

void ParkingManager::saveVehiclesToFile() {
    std::ofstream file(vehiclesFile);
    if (file.is_open()) {
        for (const auto& vehicle : vehicles) {
            // Verificar si la placa ya existe en el archivo antes de agregarla
            bool exists = false;
            std::ifstream readFile(vehiclesFile);
            std::string line;
            while (std::getline(readFile, line)) {
                auto tokens = TokenManager::split(line);
                if (tokens[0] == vehicle.getPlate()) {
                    exists = true;
                    break;
                }
            }

            // Si no existe, se agrega el vehículo al archivo
            if (!exists) {
                file << vehicle.serializeBasic() << std::endl; // Guardar placa y tipo
            }
        }
        file.close();
    }
}

void ParkingManager::loadVehiclesFromFile() {
    std::ifstream vehiclesData(vehiclesFile);
    std::string line;

    if (vehiclesData.is_open()) {
        while (std::getline(vehiclesData, line)) {
            auto tokens = TokenManager::split(line);
            if (tokens.size() >= 2) {
                Vehicle vehicle(tokens[0], "", "", "", tokens[1]);
                vehicles.push_back(vehicle);
            }
        }
        vehiclesData.close();
    }

    std::ifstream userRecordsData(userRecordsFile);
    if (userRecordsData.is_open()) {
        while (std::getline(userRecordsData, line)) {
            auto tokens = TokenManager::split(line, ',');
            if (tokens.size() >= 4) {
                auto it = std::find_if(vehicles.begin(), vehicles.end(),
                    [&tokens](const Vehicle& v) { return v.getPlate() == tokens[3]; });

                if (it != vehicles.end()) {
                    *it = Vehicle(tokens[3], tokens[0], tokens[1], tokens[2], it->getVehicleType());
                } else {
                    Vehicle vehicle(tokens[3], tokens[0], tokens[1], tokens[2], "Unknown");
                    vehicles.push_back(vehicle);
                }
            }
        }
        userRecordsData.close();
    }
}

void ParkingManager::showParkingLotCircular() {
    const int spacesPerLayer = 8; // Número de espacios por capa
    int totalVehicles = vehicles.size();
    int totalSpaces = std::max(totalVehicles + 4, spacesPerLayer); // Agregar espacios vacíos
    int layers = std::ceil((double)totalSpaces / spacesPerLayer); // Calcular capas necesarias

    // Crear espacios vacíos y ocupados
    std::vector<std::string> parkingSpaces(totalSpaces, "   "); // Espacios vacíos
    for (size_t i = 0; i < vehicles.size(); ++i) {
        parkingSpaces[i] = vehicles[i].getPlate();
    }

    // Mezclar los espacios vacíos y ocupados
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(parkingSpaces.begin(), parkingSpaces.end(), rng);

    // Mostrar diseño circular dinámico
    std::cout << "\n╭──────────────────────── PARQUEADERO CIRCULAR ────────────────────────╮\n";

    int index = 0;
    for (int layer = 0; layer < layers; ++layer) {
        int spacesInLayer = std::min(spacesPerLayer, totalSpaces - index);

        // Indentar para centrar las capas
        int padding = (spacesPerLayer - spacesInLayer) * 6; // Ajuste dinámico
        std::cout << std::string(padding, ' ');

        // Dibujar capa
        std::cout << "╭";
        for (int i = 0; i < spacesInLayer; ++i) {
            std::cout << "───╮";
        }
        std::cout << "\b \n";

        std::cout << std::string(padding, ' ') << "│";
        for (int i = 0; i < spacesInLayer; ++i) {
            std::cout << std::setw(3) << parkingSpaces[index++] << "│";
        }
        std::cout << "\n";

        std::cout << std::string(padding, ' ') << "╰";
        for (int i = 0; i < spacesInLayer; ++i) {
            std::cout << "───╯";
        }
        std::cout << "\b \n";
    }

    std::cout << "╰────────────────────────────────────────────────────────────────────╯\n";
}

void ParkingManager::saveUserRecord(const Vehicle& vehicle) {
    std::ofstream file(userRecordsFile, std::ios::app);
    if (file.is_open()) {
        file << vehicle.getOwnerName() << ","
             << vehicle.getOwnerID() << ","
             << vehicle.getOwnerPhone() << ","
             << vehicle.getPlate() << std::endl;
        file.close();
    } else {
        std::cerr << "Error al guardar en user_records.txt\n";
    }
}

void ParkingManager::showParkingHistory() {
    std::string plate;
    std::string date;

    std::cout << "Ingrese placa para ver historial: ";
    plate = InputValidator::getValidatedPlate();    

    // Validar formato de placa
    if (!InputValidator::isValidPlate(plate)) {
        std::cout << "Placa invalida.\n";
        std::cout << "\nPresione cualquier tecla para continuar...";
        _getch();
        return;
    }

    std::cout << "Ingrese fecha (YYYY-MM-DD): ";
    date = InputValidator::getValidatedDate(); // Validar fecha

    // Obtener todos los eventos
    auto events = historyManager.getAllEvents();
    std::vector<ParkingEvent> filteredEvents;

    // Filtrar eventos por placa y fecha
    for (const auto& event : events) {
        if (event.plate == plate && event.timestamp.substr(0, 10) == date) {
            filteredEvents.push_back(event);
        }
    }

    if (filteredEvents.empty()) {
        std::cout << "No se encontraron eventos para la placa: " << plate 
                  << " en la fecha especificada." << std::endl;
    } else {
        for (const auto& event : filteredEvents) {
            std::cout << event.timestamp << " - " << event.eventType << std::endl;
        }
    }

    std::cout << "\nPresione cualquier tecla para continuar...";
    _getch();
}

void ParkingManager::vehicleExit() {
    std::string plate;

    std::cout << "Ingrese placa de salida: ";
    plate = InputValidator::getValidatedPlate();


    if (!InputValidator::isValidPlate(plate)) {
        std::cout << "Placa invalida.\n";
        std::cout << "\nPresione cualquier tecla para continuar...";
        _getch();
        return;
    }


    auto vehicle = findVehicleByPlate(plate);
    

    if (!vehicle) {
        std::cout << "Vehiculo no encontrado.\n";
        std::cout << "\nPresione cualquier tecla para continuar...";
        _getch();
        return;
    }


    auto eventos = historyManager.getAllEvents();
    auto ultimoEvento = std::find_if(eventos.rbegin(), eventos.rend(), 
        [&plate](const ParkingEvent& evento) { return evento.plate == plate; });


    if (ultimoEvento != eventos.rend() && ultimoEvento->eventType == "SALIDA") {
        std::cout << "Este vehiculo ya ha salido del parqueadero.\n";
        std::cout << "\nPresione cualquier tecla para continuar...";
        _getch();
        return;
    }

    if (ultimoEvento == eventos.rend() || ultimoEvento->eventType != "ENTRADA") {
        std::cout << "El vehiculo no esta en el parqueadero.\n";
        std::cout << "\nPresione cualquier tecla para continuar...";
        _getch();
        return;
    }

    // Registrar la salida
    historyManager.logEvent(plate, "SALIDA");
    std::cout << "Salida registrada.\n";

    std::cout << "\nPresione cualquier tecla para continuar...";
    _getch();
}

void ParkingManager::showHelpManual() {
    system("cls");
    std::cout << "\n╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                     MANUAL DE AYUDA                        ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n";
    std::cout << "\nBienvenido al sistema de gestión del parqueadero.\n\n";
    std::cout << "Opciones disponibles:\n";
    std::cout << "  1. **Ingresar Vehículo**: Permite registrar un vehículo en el sistema.\n";
    std::cout << "  2. **Buscar Vehículo**: Busca un vehículo registrado por su placa.\n";
    std::cout << "  3. **Historial de Parqueo**: Muestra el historial de entradas y salidas.\n";
    std::cout << "  4. **Salida de Vehículo**: Registra la salida de un vehículo del parqueadero.\n";
    std::cout << "  5. **Mostrar Parqueadero Circular**: Visualiza los vehículos estacionados.\n";
    std::cout << "  6. **Salir**: Cierra el programa.\n\n";
    std::cout << "Tecla rápida:\n";
    std::cout << "  - Presiona **F12** en cualquier momento para abrir este manual.\n\n";
    std::cout << "Presiona cualquier tecla para volver al menú principal...\n";

    _getch();
}

void ParkingManager::createBackup() {
    // Obtener la fecha y hora actual
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;
    localtime_s(&now_tm, &now_time_t); // Convertir a tiempo local

    // Formatear fecha y hora como YYYY-MM-DD_HH-MM-SS
    std::ostringstream timestamp;
    timestamp << std::put_time(&now_tm, "%Y-%m-%d_%H-%M-%S");

    // Directorio de respaldo
    std::string backupDir = dataDir + "backup/";
    std::filesystem::create_directories(backupDir); // Crear directorio si no existe

    try {
        // Copiar archivos con timestamp en el nombre
        std::string vehiclesBackupFile = backupDir + "vehicles_backup_" + timestamp.str() + ".txt";
        std::string userRecordsBackupFile = backupDir + "user_records_backup_" + timestamp.str() + ".txt";
        std::string historyBackupFile = backupDir + "parking_history_backup_" + timestamp.str() + ".txt";

        std::filesystem::copy_file(vehiclesFile, vehiclesBackupFile,
                                   std::filesystem::copy_options::overwrite_existing);
        std::filesystem::copy_file(userRecordsFile, userRecordsBackupFile,
                                   std::filesystem::copy_options::overwrite_existing);
        std::filesystem::copy_file(historyFile, historyBackupFile,
                                   std::filesystem::copy_options::overwrite_existing);

        std::cout << "Respaldo creado exitosamente:\n";
        std::cout << "  - " << vehiclesBackupFile << "\n";
        std::cout << "  - " << userRecordsBackupFile << "\n";
        std::cout << "  - " << historyBackupFile << "\n";
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error al crear el respaldo: " << e.what() << "\n";
    }

    std::cout << "Presione cualquier tecla para volver al menú...\n";
    _getch();
}

void ParkingManager::restoreBackup() {
    std::string backupDir = dataDir + "backup/";
    try {
        // Buscar el respaldo más reciente
        std::string latestVehiclesBackup, latestUserRecordsBackup, latestHistoryBackup;

        for (const auto& entry : std::filesystem::directory_iterator(backupDir)) {
            if (entry.path().string().find("vehicles_backup_") != std::string::npos) {
                latestVehiclesBackup = entry.path().string();
            } else if (entry.path().string().find("user_records_backup_") != std::string::npos) {
                latestUserRecordsBackup = entry.path().string();
            } else if (entry.path().string().find("parking_history_backup_") != std::string::npos) {
                latestHistoryBackup = entry.path().string();
            }
        }

        // Verificar que los respaldos estén disponibles
        if (latestVehiclesBackup.empty() || latestUserRecordsBackup.empty() || latestHistoryBackup.empty()) {
            std::cerr << "No se encontró un respaldo válido.\n";
            std::cout << "Presione cualquier tecla para volver al menú...\n";
            _getch();
            return;
        }

        // Restaurar los archivos desde el respaldo más reciente
        std::filesystem::copy_file(latestVehiclesBackup, vehiclesFile,
                                   std::filesystem::copy_options::overwrite_existing);
        std::filesystem::copy_file(latestUserRecordsBackup, userRecordsFile,
                                   std::filesystem::copy_options::overwrite_existing);
        std::filesystem::copy_file(latestHistoryBackup, historyFile,
                                   std::filesystem::copy_options::overwrite_existing);

        loadVehiclesFromFile();

        std::cout << "Respaldo restaurado exitosamente desde:\n";
        std::cout << "  - " << latestVehiclesBackup << "\n";
        std::cout << "  - " << latestUserRecordsBackup << "\n";
        std::cout << "  - " << latestHistoryBackup << "\n";
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error al restaurar el respaldo: " << e.what() << "\n";
    }

    std::cout << "Presione cualquier tecla para volver al menú...\n";
    _getch();
}

void ParkingManager::displayMainMenu() {
    int choice = 0;
    const int totalOptions = 8; 
    bool exitProgram = false;

    while (!exitProgram) {
        system("cls"); 
        std::cout << "\n--- SISTEMA DE ESTACIONAMIENTO ---\n";

        for (int i = 0; i < totalOptions; ++i) {
            if (i == choice) {
                std::cout << "> ";
            } else {
                std::cout << "  ";
            }
            switch (i) {
                case 0: std::cout << "Ingresar Vehículo\n"; break;
                case 1: std::cout << "Buscar Vehículo\n"; break;
                case 2: std::cout << "Historial de Parqueo\n"; break;
                case 3: std::cout << "Salida de Vehículo\n"; break;
                case 4: std::cout << "Mostrar Parqueadero Circular\n"; break;
                case 5: std::cout << "Crear Respaldo\n"; break;
                case 6: std::cout << "Restaurar Respaldo\n"; break;
                case 7: std::cout << "Salir\n"; break;
            }
        }

        int ch = _getch();

        if (ch == 0 || ch == 224) { 
            ch = _getch();
            if (ch == 123) { 
                showHelpManual();
                continue; 
            }
        }

        // Manejar selección de opciones del menú
        switch (ch) {
            case 72: // Flecha arriba
                choice = (choice - 1 + totalOptions) % totalOptions;
                break;
            case 80: // Flecha abajo
                choice = (choice + 1) % totalOptions;
                break;
            case 13: // Enter
                system("cls");
                switch (choice) {
                    case 0: enterVehicle(); break;
                    case 1: findVehicle(); break;
                    case 2: showParkingHistory(); break;
                    case 3: vehicleExit(); break;
                    case 4: showParkingLotCircular(); break;
                    case 5: createBackup(); break;
                    case 6: restoreBackup(); break;
                    case 7: exitProgram = true; break;
                }
                break;
        }
    }
}
