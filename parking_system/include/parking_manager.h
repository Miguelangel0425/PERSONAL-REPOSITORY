#ifndef PARKING_MANAGER_H
#define PARKING_MANAGER_H

#include <vector>
#include <memory>
#include <functional>
#include "vehicle.h"
#include "input_validator.h"
#include "history_manager.h"
#include "token_manager.h"

class ParkingManager {
public:
    ParkingManager(const std::string& dataDir = "data/");

    void enterVehicle();

    // Operaciones principales
    bool registerVehicle();
    bool findVehicle();
    void showParkingHistory();
    void vehicleExit();
    void showHelpManual();
    void createBackup();
    void restoreBackup();
    void displayMainMenu();

private:
    std::string dataDir;
    std::string vehiclesFile;
    std::string userRecordsFile;
    std::string historyFile;
    HistoryManager historyManager;
    std::vector<Vehicle> vehicles;

    // Métodos auxiliares
     void saveUserRecord(const Vehicle& vehicle);
    void saveVehiclesToFile();
    void loadVehiclesFromFile();
    void showParkingLotCircular();
    std::unique_ptr<Vehicle> findVehicleByPlate(const std::string &plate);

    // Validadores de entrada con lambdas
    std::function<bool(const std::string&)> plateValidator = 
        [](const std::string& plate) { 
            return InputValidator::isValidPlate(plate); 
        };

    std::function<bool(const std::string&)> nameValidator = 
        [](const std::string& name) { 
            return InputValidator::isValidName(name); 
        };
};

#endif // PARKING_MANAGER_H