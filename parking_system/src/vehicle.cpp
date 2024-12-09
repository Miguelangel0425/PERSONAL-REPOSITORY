#include "../include/vehicle.h"
#include "../include/token_manager.h"
#include "vehicle.h"

Vehicle::Vehicle(const std::string& plate, const std::string& ownerName, 
                 const std::string& ownerID, const std::string& ownerPhone, 
                 const std::string& vehicleType)
    : plate(plate), ownerName(ownerName), ownerID(ownerID), 
      ownerPhone(ownerPhone), vehicleType(vehicleType) {
    uniqueToken = TokenManager::generateToken();
    setEntryTime();
}

void Vehicle::setOwnerName(const std::string& ownerName) {

    this->ownerName = ownerName;

}
void Vehicle::setOwnerId(const std::string& ownerID) {
    this->ownerID = ownerID;
}
void Vehicle::setOwnerPhone(const std::string& ownerPhone) {
    this->ownerPhone = ownerPhone;
}
void Vehicle::setVehicleType(const std::string& vehicleType) {
    this->vehicleType = vehicleType;
}
void Vehicle::setUniqueToken(const std::string& uniqueToken) {
    this->uniqueToken = uniqueToken;
}
void Vehicle::setEntryTime(const std::chrono::system_clock::time_point& entryTime) {
    this->entryTime = entryTime;
}

std::string Vehicle::getPlate() const { return plate; }
std::string Vehicle::getOwnerName() const { return ownerName; }
std::string Vehicle::getOwnerID() const { return ownerID; }
std::string Vehicle::getOwnerPhone() const { return ownerPhone; }
std::string Vehicle::getVehicleType() const { return vehicleType; }
std::string Vehicle::getUniqueToken() const { return uniqueToken; }

std::chrono::system_clock::time_point Vehicle::getEntryTime() const { 
    return entryTime; 
}

std::string Vehicle::serializeBasic() const {
    return plate + "," + vehicleType;
}

void Vehicle::setEntryTime() {
    entryTime = std::chrono::system_clock::now();
}

std::string Vehicle::serialize() const {
    return TokenManager::join({
        plate, ownerName, ownerID, 
        ownerPhone, vehicleType, uniqueToken
    });
}

Vehicle Vehicle::deserialize(const std::string& data) {
    auto tokens = TokenManager::split(data);
    if (tokens.size() >= 5) {
        Vehicle vehicle(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
        return vehicle;
    }
    throw std::runtime_error("Invalid vehicle data");
}