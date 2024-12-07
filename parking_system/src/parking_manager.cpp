#include "../include/parking_manager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
#include "parking_manager.h"
#include "input_validator.h"
#include "history_manager.h"
#include "token_manager.h"


ParkingManager::ParkingManager(const std::string& dataDir)
    : dataDir(dataDir), 
      vehiclesFile(dataDir + "vehicles.txt"),
      userRecordsFile(dataDir + "user_records.txt"), // Archivo para registros de usuarios
      historyFile(dataDir + "parking_history.txt"), // Archivo para el historial
      historyManager(historyFile) { // Pasar el archivo de historial al HistoryManager
    loadVehiclesFromFile();
}

void ParkingManager::enterVehicle() {
    std::string plate;

    std::cout << "Ingrese placa (AAA000): ";
    std::getline(std::cin, plate);

    // Validar la placa
    if (!InputValidator::isValidPlate(plate)) {
        std::cout << "Placa invalida. Intente nuevamente.\n";
        return;
    }

    // Verificar si la placa ya está registrada
    auto vehicle = findVehicleByPlate(plate);
    
    if (vehicle) {
        // Si el vehículo ya está registrado, solo registrar la entrada
        historyManager.logEvent(plate, "ENTRADA");
        std::cout << "Vehículo ingresado al parqueadero.\n";
    } else {
        // Si no está registrado, solicitar datos del propietario
        std::string name, id, phone, type;

        while (true) {
            std::cout << "Nombre del propietario: ";
            std::getline(std::cin, name);
            if (!InputValidator::validate(name, nameValidator)) {
                std::cout << "Nombre invalido. Solo letras.\n";
                continue;
            }
            break;
        }

        std::cout << "Ingrese su Cedula: ";
        std::getline(std::cin, id);

        std::cout << "Ingrese telefono: ";
        std::getline(std::cin, phone);

        std::cout << "Ingrese tipo de vehiculo: ";
        std::getline(std::cin, type);

        Vehicle newVehicle(plate, name, id, phone, type);
        vehicles.push_back(newVehicle);
        saveVehiclesToFile();
        saveUserRecord(newVehicle); // Guardar el registro del usuario en user_records.txt
        historyManager.logEvent(plate, "ENTRADA"); 
        
        std::cout << "Vehiculo registrado y ingresado al parqueadero.\n";
    }
}

bool ParkingManager::registerVehicle() {
    std::string plate, name, id, phone, type;

    // Validaciones con lambdas y templates
    while (true) {
        std::cout << "Ingrese placa (AAA000): ";
        std::getline(std::cin, plate);
        if (!InputValidator::validate(plate, plateValidator)) {
            std::cout << "Placa invalida. Intente nuevamente.\n";
            continue;
        }
        break;
    }

    while (true) {
        std::cout << "Nombre del propietario: ";
        std::getline(std::cin, name);
        if (!InputValidator::validate(name, nameValidator)) {
            std::cout << "Nombre invalido. Solo letras.\n";
            continue;
        }
        break;
    }

    // Agregar validaciones para ID, teléfono y tipo de vehículo
    std::cout << "Ingrese su Cedula: ";
    std::getline(std::cin, id);

    std::cout << "Ingrese telefono: ";
    std::getline(std::cin, phone);

    std::cout << "Ingrese tipo de vehiculo: ";
    std::getline(std::cin, type);

    Vehicle newVehicle(plate, name, id, phone, type);
    vehicles.push_back(newVehicle);
    
    saveVehiclesToFile();
    historyManager.logEvent(plate, "ENTRADA");
    std::cout << "Vehiculo registrado exitosamente.\n";
    
    return true;
}

bool ParkingManager::findVehicle() {
    std::string plate;
    std::cout << "Ingrese placa del vehículo a buscar: ";
    std::getline(std::cin, plate);

    // Validar formato de placa
    if (!InputValidator::isValidPlate(plate)) {
        std::cout << "Placa invalida.\n";
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
        return true;
    } else {
        std::cout << "Vehiculo no encontrado.\n";
        return false;
    }
}

std::unique_ptr<Vehicle> ParkingManager::findVehicleByPlate(const std::string& plate) {
    auto it = std::find_if(vehicles.begin(), vehicles.end(), 
        [&plate](const Vehicle& v) { return v.getPlate() == plate; });
    
    return it != vehicles.end() ? 
        std::make_unique<Vehicle>(*it) : nullptr;
}

void ParkingManager::saveVehiclesToFile() {
    std::ofstream file(vehiclesFile);
    for (const auto& vehicle : vehicles) {
        file << vehicle.serializeBasic() << std::endl; // Guardar solo placa y tipo
    }
}


void ParkingManager::loadVehiclesFromFile() {
    std::ifstream file(vehiclesFile);
    std::string line;
    vehicles.clear(); // Limpiar la lista de vehículos antes de cargar

    if (file.is_open()) {
        while (std::getline(file, line)) {
            auto tokens = TokenManager::split(line);
            if (tokens.size() >= 2) {
                // Crear un vehículo con la placa y el tipo
                Vehicle vehicle(tokens[0], "", "", "", tokens[1]); // Placa y tipo de vehículo
                vehicles.push_back(vehicle);
            }
        }
        file.close();
    } else {
        std::cerr << "Error al abrir el archivo para cargar vehículos." << std::endl;
    }
}

void ParkingManager::saveUserRecord(const Vehicle& vehicle) {
    std::ofstream file(userRecordsFile, std::ios::app);
    if (file.is_open()) {
        file << vehicle.getOwnerName() << "," 
             << vehicle.getOwnerID() << "," 
             << vehicle.getOwnerPhone() << "," 
             << vehicle.getPlate() << std::endl; // Guardar los datos del usuario
        file.close();
    }
}

void ParkingManager::showParkingHistory() {
    std::string plate;
    std::string date;

    std::cout << "Ingrese placa para ver historial: ";
    std::getline(std::cin, plate);

    std::cout << "Ingrese fecha (YYYY-MM-DD): ";
    std::getline(std::cin, date);

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
}

void ParkingManager::vehicleExit() {
    std::string plate;
    std::cout << "Ingrese placa de salida: ";
    std::getline(std::cin, plate);

    // Validar formato de placa
    if (!InputValidator::isValidPlate(plate)) {
        std::cout << "Placa invalida.\n";
        return;
    }

    auto vehicle = findVehicleByPlate(plate);
    if (vehicle) {
        historyManager.logEvent(plate, "SALIDA");
        
        vehicles.erase(
            std::remove_if(vehicles.begin(), vehicles.end(), 
                [&plate](const Vehicle& v) { return v.getPlate() == plate; }), 
            vehicles.end()
        );

        saveVehiclesToFile();
        std::cout << "Vehiculo registrado como salida.\n";
    } else {
        std::cout << "Vehiculo no encontrado o ya ha salido.\n";
    }
}

void ParkingManager::displayMainMenu() {
    int choice = 0;
    const int totalOptions = 5;

    while (true) {
        system("pause");
        system("cls"); // Limpiar la pantalla
        std::cout << "\n--- SISTEMA DE ESTACIONAMIENTO ---\n";
        
        // Mostrar opciones del menú
        for (int i = 0; i < totalOptions; ++i) {
            if (i == choice) {
                std::cout << "> "; // Indicar la opción seleccionada
            } else {
                std::cout << "  ";
            }
            switch (i) {
                case 0: std::cout << "Ingresar Vehiculo\n"; break;
                case 1: std::cout << "Buscar Vehiculo\n"; break;
                case 2: std::cout << "Historial de Parqueo\n"; break;
                case 3: std::cout << "Salida de Vehiculo\n"; break;
                case 4: std::cout << "Salir\n"; break;
            }
        }

        // Capturar la tecla presionada
        char key = _getch();
        if (key == 's') { // Mover hacia abajo
            choice = (choice + 1) % totalOptions;
        } else if (key == 'w') { // Mover hacia arriba
            choice = (choice - 1 + totalOptions) % totalOptions;
        } else if (key == '\r') { // Enter
            system("cls"); 
            switch (choice) {
                case 0: enterVehicle(); break;
                case 1: findVehicle(); break;
                case 2: showParkingHistory(); break;
                case 3: vehicleExit(); break;
                case 4: std::cout << "Saliendo...\n"; return;
            }
        }
    }
}
