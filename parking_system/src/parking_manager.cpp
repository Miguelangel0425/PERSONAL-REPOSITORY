#include "../include/parking_manager.h"
#include "../include/input_validator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <conio.h>
#include <algorithm>
#include <limits>

ParkingManager::ParkingManager() 
    : dataFile("parking_data.txt"), 
      historyFile("parking_history.txt"),
      menuOptions({"Registrar Vehículo", "Buscar Vehículo", 
                   "Historial de Parqueo", "Salida de Vehículo", "Salir"}),
      currentOption(0) {}

void ParkingManager::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void ParkingManager::displayMenu() {
    clearScreen();
    std::cout << "--- SISTEMA DE PARQUEADERO ---\n\n";
    
    for (size_t i = 0; i < menuOptions.size(); ++i) {
        if (i == currentOption) {
            std::cout << "-> " << menuOptions[i] << " <-\n";
        } else {
            std::cout << "   " << menuOptions[i] << "\n";
        }
    }
    std::cout << "\nUse W/S para moverse, Enter para seleccionar\n";
}

void ParkingManager::handleMenuNavigation() {
    char key;
    while (true) {
        displayMenu();
        key = _getch();

        switch (key) {
            case 'w':  // Arriba
                if (currentOption > 0) currentOption--;
                break;
            case 's':  // Abajo
                if (currentOption < menuOptions.size() - 1) currentOption++;
                break;
            case 13:  // Enter
                processSelectedOption();
                return;
        }
    }
}

void ParkingManager::processSelectedOption() {
    clearScreen();
    switch (currentOption) {
        case 0: registerVehicle(); break;
        case 1: searchVehicleByPlate(); break;
        case 2: showParkingHistory(); break;
        case 3: vehicleExit(); break;
        case 4: 
            std::cout << "Saliendo del sistema...\n";
            exit(0);
    }
    
    std::cout << "\nPresione cualquier tecla para continuar...";
    _getch();
}

std::string ParkingManager::getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void ParkingManager::registerVehicle() {
    std::string plate, name, id, phone, type;

    while (true) {
        std::cout << "Ingrese placa (formato AAA000): ";
        std::getline(std::cin, plate);
        if (InputValidator::isValidPlate(plate)) break;
        std::cout << "Placa inválida. Intente nuevamente.\n";
    }

    while (true) {
        std::cout << "Ingrese nombre del propietario: ";
        std::getline(std::cin, name);
        if (InputValidator::isValidName(name)) break;
        std::cout << "Nombre inválido. Solo letras son permitidas.\n";
    }

    while (true) {
        std::cout << "Ingrese cédula (10 dígitos): ";
        std::getline(std::cin, id);
        if (InputValidator::isValidID(id)) break;
        std::cout << "Cédula inválida. Debe contener 10 dígitos.\n";
    }

    while (true) {
        std::cout << "Ingrese teléfono (10 dígitos): ";
        std::getline(std::cin, phone);
        if (InputValidator::isValidPhone(phone)) break;
        std::cout << "Teléfono inválido. Debe contener 10 dígitos.\n";
    }

    std::cout << "Ingrese tipo de vehículo: ";
    std::getline(std::cin, type);

    Vehicle vehicle(plate, name, id, phone, type);
    vehicles.push_back(vehicle);
    saveVehicleToFile(vehicle);
    logParkingEvent(plate, "ENTRADA");
    std::cout << "Vehículo registrado exitosamente.\n";
}

void ParkingManager::saveVehicleToFile(const Vehicle& vehicle) {
    std::ofstream file(dataFile, std::ios::app);
    file << vehicle.getPlate() << ","
         << vehicle.getOwnerName() << ","
         << vehicle.getOwnerID() << ","
         << vehicle.getOwnerPhone() << ","
         << vehicle.getVehicleType() << std::endl;
    file.close();
}

void ParkingManager::logParkingEvent(const std::string& plate, const std::string& eventType) {
    std::ofstream file(historyFile, std::ios::app);
    file << getCurrentDateTime() << ","
         << plate << ","
         << eventType << std::endl;
    file.close();
}

void ParkingManager::searchVehicleByPlate() {
    std::string plate;
    std::cout << "Ingrese placa a buscar: ";
    std::getline(std::cin, plate);

    auto it = std::find_if(vehicles.begin(), vehicles.end(),
        [&plate](const Vehicle& v) { return v.getPlate() == plate; });

    if (it != vehicles.end()) {
        std::cout << "Placa: " << it->getPlate() << std::endl;
        std::cout << "Propietario: " << it->getOwnerName() << std::endl;
        std::cout << "Cédula: " << it->getOwnerID() << std::endl;
        std::cout << "Teléfono: " << it->getOwnerPhone() << std::endl;
        std::cout << "Tipo de vehículo: " << it->getVehicleType() << std::endl;
    } else {
        std::cout << "Vehículo no encontrado.\n";
    }
}

void ParkingManager::showParkingHistory() {
    std::string plate, startDate, endDate;
    std::cout << "Ingrese placa para consultar historial: ";
    std::getline(std::cin, plate);

    std::cout << "Ingrese fecha de inicio (YYYY-MM-DD): ";
    std::getline(std::cin, startDate);

    std::cout << "Ingrese fecha de fin (YYYY-MM-DD): ";
    std::getline(std::cin, endDate);

    std::ifstream file(historyFile);
    std::string line;
    bool found = false;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string dateTime, recordPlate, event;

        std::getline(ss, dateTime, ',');
        std::getline(ss, recordPlate, ',');
        std::getline(ss, event);

        if (recordPlate == plate && 
            dateTime.substr(0, 10) >= startDate && 
            dateTime.substr(0, 10) <= endDate) {
            std::cout << dateTime << " - " << event << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No se encontró historial para esta placa en el rango de fechas.\n";
    }
}

void ParkingManager::vehicleExit() {
    std::string plate;
    std::cout << "Ingrese placa de salida: ";
    std::getline(std::cin, plate);

    auto it = std::find_if(vehicles.begin(), vehicles.end(),
        [&plate](const Vehicle& v) { return v.getPlate() == plate; });

    if (it != vehicles.end()) {
        logParkingEvent(plate, "SALIDA");
        vehicles.erase(it);
        std::cout << "Vehículo registrado como salida.\n";
    } else {
        std::cout << "Vehículo no encontrado en el sistema.\n";
    }
}

void ParkingManager::mainMenu() {
    while (true) {
        handleMenuNavigation();
    }
}