#ifndef PARKING_MANAGER_H
#define PARKING_MANAGER_H

#include <vector>
#include <string>
#include "vehicle.h"

class ParkingManager {
private:
    std::vector<Vehicle> vehicles;
    std::string dataFile;
    std::string historyFile;
    std::vector<std::string> menuOptions;
    int currentOption;

    void clearScreen();
    void displayMenu();
    void handleMenuNavigation();
    void processSelectedOption();
    std::string getCurrentDateTime();
    void saveVehicleToFile(const Vehicle& vehicle);
    void logParkingEvent(const std::string& plate, const std::string& eventType);

public:
    ParkingManager();
    void mainMenu();
    void registerVehicle();
    void searchVehicleByPlate();
    void showParkingHistory();
    void vehicleExit();
};

#endif