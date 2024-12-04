#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
private:
    std::string plate;
    std::string ownerName;
    std::string ownerID;
    std::string ownerPhone;
    std::string vehicleType;

public:
    Vehicle(const std::string& p, const std::string& name, 
            const std::string& id, const std::string& phone, 
            const std::string& type);


    std::string getPlate() const;
    std::string getOwnerName() const;
    std::string getOwnerID() const;
    std::string getOwnerPhone() const;
    std::string getVehicleType() const;
};

#endif 