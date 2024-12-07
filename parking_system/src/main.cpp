#include "../include/parking_manager.h"
#include <iostream>

int main() {
    try {
        ParkingManager parkingSystem;
        parkingSystem.displayMainMenu();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}