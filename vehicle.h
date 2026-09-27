#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <vector>

using namespace std;


// VEHICLE STRUCTURE
struct Vehicle
{
    int id;

    string registration;

    string vehicleType;

    string ownerName;

    string phoneNumber;
};


// VEHICLE VALIDATION FUNCTIONS
bool isValidRegistration(
    const string& registration
);


// Check whether a registration number is already registered.
bool isRegistrationAlreadyRegistered(
    const vector<Vehicle>& vehicles,
    const string& registration
);


// Convert a numeric vehicle-type choice into a vehicle type.
string selectVehicleType(
    int choice
);


// Validate the vehicle owner's name.
bool isValidOwnerName(
    const string& ownerName
);


// Validate the owner's Kenyan phone number.
bool isValidPhoneNumber(
    const string& phoneNumber
);


// VEHICLE DISPLAY
void displayVehicle(
    const Vehicle& vehicle
);


// VEHICLE CREATION
Vehicle createVehicle(
    int vehicleId
);


// VEHICLE REGISTRATION
Vehicle registerVehicle(
    int vehicleId,
    const vector<Vehicle>& vehicles
);


#endif
