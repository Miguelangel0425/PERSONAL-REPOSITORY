#include "../include/vehicle.h"

Vehicle::Vehicle(const std::string& p, const std::string& name, 
                 const std::string& id, const std::string& phone, 
                 const std::string& type)
    : plate(p), ownerName(name), ownerID(id), 
      ownerPhone(phone), vehicleType(type) {}

std::string Vehicle::getPlate() const { return plate; }
std::string Vehicle::getOwnerName() const { return ownerName; }
std::string Vehicle::getOwnerID() const { return ownerID; }
std::string Vehicle::getOwnerPhone() const { return ownerPhone; }
std::string Vehicle::getVehicleType() const { return vehicleType; }