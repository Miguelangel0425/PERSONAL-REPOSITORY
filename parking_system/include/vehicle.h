#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <chrono>
#include "../include/token_manager.h"

class Vehicle {
public:
    Vehicle() = default;
    Vehicle(const std::string& plate, const std::string& ownerName, 
            const std::string& ownerID, const std::string& ownerPhone, 
            const std::string& vehicleType);

    // Getters
    std::string getPlate() const;
    std::string getOwnerName() const;
    std::string getOwnerID() const;
    std::string getOwnerPhone() const;
    std::string getVehicleType() const;
    std::string getUniqueToken() const;
    std::chrono::system_clock::time_point getEntryTime() const;

    std::string serializeBasic() const;

    // Setters
    void setEntryTime();

    // Métodos de serialización
    std::string serialize() const;
    static Vehicle deserialize(const std::string& data);

private:
    std::string plate;
    std::string ownerName;
    std::string ownerID;
    std::string ownerPhone;
    std::string vehicleType;
    std::string uniqueToken;
    std::chrono::system_clock::time_point entryTime;
};

#endif // VEHICLE_H