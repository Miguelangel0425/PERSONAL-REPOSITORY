#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <regex>

class Vehicle {
private:
    std::string plate;
    std::string ownerName;
    std::string ownerPhone;
    std::string vehicleType;

public:
    Vehicle(const std::string& p, const std::string& name, 
            const std::string& phone, const std::string& type)
        : plate(p), ownerName(name), ownerPhone(phone), vehicleType(type) {}

    std::string getPlate() const { return plate; }
    std::string getOwnerName() const { return ownerName; }
    std::string getOwnerPhone() const { return ownerPhone; }
    std::string getVehicleType() const { return vehicleType; }
};

class ParkingManager {
private:
    std::vector<Vehicle> vehicles;
    std::string dataFile = "parking_data.txt";
    std::string historyFile = "parking_history.txt";

    bool isValidPlate(const std::string& plate) {
        return std::regex_match(plate, std::regex("^[A-Z]{3}\\d{3}$"));
    }

    bool isValidName(const std::string& name) {
        return std::regex_match(name, std::regex("^[A-Za-z\\s]+$"));
    }

    bool isValidPhone(const std::string& phone) {
        return std::regex_match(phone, std::regex("^\\d{10}$"));
    }

    std::string getCurrentDateTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    void saveVehicleToFile(const Vehicle& vehicle) {
        std::ofstream file(dataFile, std::ios::app);
        file << vehicle.getPlate() << ","
             << vehicle.getOwnerName() << ","
             << vehicle.getOwnerPhone() << ","
             << vehicle.getVehicleType() << std::endl;
        file.close();
    }

    void logParkingEvent(const std::string& plate, const std::string& eventType) {
        std::ofstream file(historyFile, std::ios::app);
        file << getCurrentDateTime() << ","
             << plate << ","
             << eventType << std::endl;
        file.close();
    }

public:
    void registerVehicle() {
        std::string plate, name, phone, type;

        while (true) {
            std::cout << "Ingrese placa (formato AAA000): ";
            std::getline(std::cin, plate);
            if (isValidPlate(plate)) break;
            std::cout << "Placa inválida. Intente nuevamente.\n";
        }

        while (true) {
            std::cout << "Ingrese nombre del propietario: ";
            std::getline(std::cin, name);
            if (isValidName(name)) break;
            std::cout << "Nombre inválido. Intente nuevamente.\n";
        }

        while (true) {
            std::cout << "Ingrese teléfono (10 dígitos): ";
            std::getline(std::cin, phone);
            if (isValidPhone(phone)) break;
            std::cout << "Teléfono inválido. Intente nuevamente.\n";
        }

        std::cout << "Ingrese tipo de vehículo: ";
        std::getline(std::cin, type);

        Vehicle vehicle(plate, name, phone, type);
        vehicles.push_back(vehicle);
        saveVehicleToFile(vehicle);
        logParkingEvent(plate, "ENTRADA");
        std::cout << "Vehículo registrado exitosamente.\n";
    }

    void searchVehicleByPlate() {
        std::string plate;
        std::cout << "Ingrese placa a buscar: ";
        std::getline(std::cin, plate);

        auto it = std::find_if(vehicles.begin(), vehicles.end(),
            [&plate](const Vehicle& v) { return v.getPlate() == plate; });

        if (it != vehicles.end()) {
            std::cout << "Placa: " << it->getPlate() << std::endl;
            std::cout << "Propietario: " << it->getOwnerName() << std::endl;
            std::cout << "Teléfono: " << it->getOwnerPhone() << std::endl;
            std::cout << "Tipo de vehículo: " << it->getVehicleType() << std::endl;
        } else {
            std::cout << "Vehículo no encontrado.\n";
        }
    }

    void showParkingHistory() {
        std::string plate;
        std::cout << "Ingrese placa para consultar historial: ";
        std::getline(std::cin, plate);

        std::ifstream file(historyFile);
        std::string line;
        bool found = false;

        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string dateTime, recordPlate, event;

            std::getline(ss, dateTime, ',');
            std::getline(ss, recordPlate, ',');
            std::getline(ss, event);

            if (recordPlate == plate) {
                std::cout << dateTime << " - " << event << std::endl;
                found = true;
            }
        }

        if (!found) {
            std::cout << "No se encontró historial para esta placa.\n";
        }
    }

    void vehicleExit() {
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

    void mainMenu() {
        int choice;
        do {
            std::cout << "\n--- SISTEMA DE PARQUEADERO ---\n";
            std::cout << "1. Registrar Vehículo\n";
            std::cout << "2. Buscar Vehículo\n";
            std::cout << "3. Historial de Parqueo\n";
            std::cout << "4. Salida de Vehículo\n";
            std::cout << "5. Salir\n";
            std::cout << "Ingrese su opción: ";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch(choice) {
                case 1: registerVehicle(); break;
                case 2: searchVehicleByPlate(); break;
                case 3: showParkingHistory(); break;
                case 4: vehicleExit(); break;
                case 5: std::cout << "Saliendo...\n"; break;
                default: std::cout << "Opción inválida.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    ParkingManager parkingSystem;
    parkingSystem.mainMenu();
    return 0;
}