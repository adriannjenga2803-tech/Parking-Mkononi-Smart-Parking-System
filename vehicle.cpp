#include "vehicle.h"

#include <cctype>
#include <iostream>
#include <limits>

using namespace std;


// VALIDATE VEHICLE REGISTRATION
bool isValidRegistration(const string& registration)
{
    if (registration.empty())
    {
        return false;
    }

    bool hasLetter = false;
    bool hasNumber = false;

    for (char character : registration)
    {
        unsigned char currentCharacter =
            static_cast<unsigned char>(character);

        if (isalpha(currentCharacter))
        {
            hasLetter = true;
        }
        else if (isdigit(currentCharacter))
        {
            hasNumber = true;
        }
        else if (character != ' ' && character != '-')
        {
            return false;
        }
    }

    return hasLetter && hasNumber;
}


// CHECK FOR DUPLICATE VEHICLE REGISTRATION
bool isRegistrationAlreadyRegistered(
    const vector<Vehicle>& vehicles,
    const string& registration)
{
    for (const Vehicle& vehicle : vehicles)
    {
        if (vehicle.registration.length() != registration.length())
        {
            continue;
        }

        bool sameRegistration = true;

        for (size_t i = 0; i < registration.length(); i++)
        {
            unsigned char existingCharacter =
                static_cast<unsigned char>(
                    vehicle.registration[i]
                );

            unsigned char newCharacter =
                static_cast<unsigned char>(
                    registration[i]
                );

            if (toupper(existingCharacter) !=
                toupper(newCharacter))
            {
                sameRegistration = false;
                break;
            }
        }

        if (sameRegistration)
        {
            return true;
        }
    }

    return false;
}


// SELECT VEHICLE TYPE
string selectVehicleType(int choice)
{
    if (choice == 1)
    {
        return "Car";
    }
    else if (choice == 2)
    {
        return "SUV";
    }
    else if (choice == 3)
    {
        return "Van";
    }
    else if (choice == 4)
    {
        return "Motorcycle";
    }

    return "Unknown";
}


// VALIDATE OWNER NAME
bool isValidOwnerName(const string& ownerName)
{
    if (ownerName.empty())
    {
        return false;
    }

    bool hasLetter = false;

    for (char character : ownerName)
    {
        unsigned char currentCharacter =
            static_cast<unsigned char>(character);

        if (isalpha(currentCharacter))
        {
            hasLetter = true;
        }
        else if (character != ' ')
        {
            return false;
        }
    }

    return hasLetter;
}


// VALIDATE PHONE NUMBER
bool isValidPhoneNumber(const string& phoneNumber)
{
    if (phoneNumber.length() != 10)
    {
        return false;
    }

    if (phoneNumber[0] != '0')
    {
        return false;
    }

    if (phoneNumber[1] != '7' &&
        phoneNumber[1] != '1')
    {
        return false;
    }

    for (char digit : phoneNumber)
    {
        unsigned char currentDigit =
            static_cast<unsigned char>(digit);

        if (!isdigit(currentDigit))
        {
            return false;
        }
    }

    return true;
}


// DISPLAY VEHICLE INFORMATION
void displayVehicle(const Vehicle& vehicle)
{
    cout << "\nVehicle Information:" << endl;
    cout << "--------------------" << endl;

    cout << "Vehicle ID: "
         << vehicle.id << endl;

    cout << "Registration Number: "
         << vehicle.registration << endl;

    cout << "Vehicle Type: "
         << vehicle.vehicleType << endl;

    cout << "Owner Name: "
         << vehicle.ownerName << endl;

    cout << "Phone Number: "
         << vehicle.phoneNumber << endl;
}


// CREATE EMPTY VEHICLE
Vehicle createVehicle(int vehicleId)
{
    Vehicle vehicle;

    vehicle.id = vehicleId;
    vehicle.registration = "";
    vehicle.vehicleType = "";
    vehicle.ownerName = "";
    vehicle.phoneNumber = "";

    return vehicle;
}


// REGISTER VEHICLE
Vehicle registerVehicle(
    int vehicleId,
    const vector<Vehicle>& vehicles)
{
    Vehicle vehicle = createVehicle(vehicleId);


    // VEHICLE REGISTRATION NUMBER
    do
    {
        cout << "\nEnter vehicle registration number: ";

        getline(cin >> ws, vehicle.registration);

        if (!isValidRegistration(vehicle.registration))
        {
            cout << "Invalid registration number." << endl;
            cout << "Please enter a valid registration number."
                 << endl;
        }
        else if (isRegistrationAlreadyRegistered(
                     vehicles,
                     vehicle.registration))
        {
            cout << "This vehicle registration is already registered."
                 << endl;

            cout << "Please enter a different registration number."
                 << endl;
        }

    }
    while (
        !isValidRegistration(vehicle.registration) ||
        isRegistrationAlreadyRegistered(
            vehicles,
            vehicle.registration
        )
    );


    // CONVERT REGISTRATION TO UPPERCASE
    for (char& character : vehicle.registration)
    {
        unsigned char currentCharacter =
            static_cast<unsigned char>(character);

        character =
            static_cast<char>(
                toupper(currentCharacter)
            );
    }


    // VEHICLE TYPE
    int vehicleTypeChoice = 0;

    do
    {
        cout << "\nSelect Vehicle Type:" << endl;
        cout << "-------------------" << endl;
        cout << "1. Car" << endl;
        cout << "2. SUV" << endl;
        cout << "3. Van" << endl;
        cout << "4. Motorcycle" << endl;
        cout << "Enter your choice: ";

        cin >> vehicleTypeChoice;

        if (cin.fail())
        {
            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "Invalid input." << endl;
            cout << "Please enter a number from 1 to 4."
                 << endl;

            vehicleTypeChoice = 0;
        }
        else if (
            vehicleTypeChoice < 1 ||
            vehicleTypeChoice > 4
        )
        {
            cout << "Invalid vehicle type." << endl;

            cout << "Please select a number from 1 to 4."
                 << endl;
        }

    }
    while (
        vehicleTypeChoice < 1 ||
        vehicleTypeChoice > 4
    );

    vehicle.vehicleType =
        selectVehicleType(vehicleTypeChoice);


    // CLEAR INPUT BUFFER
    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );


    // OWNER NAME
    do
    {
        cout << "Enter owner's name: ";

        getline(cin, vehicle.ownerName);

        if (!isValidOwnerName(vehicle.ownerName))
        {
            cout << "Invalid owner name." << endl;

            cout << "Please enter letters and spaces only."
                 << endl;
        }

    }
    while (!isValidOwnerName(vehicle.ownerName));


    // OWNER PHONE NUMBER
    do
    {
        cout << "Enter owner's phone number: ";

        getline(cin, vehicle.phoneNumber);

        if (!isValidPhoneNumber(vehicle.phoneNumber))
        {
            cout << "Invalid phone number." << endl;

            cout << "Please enter a valid Kenyan phone number."
                 << endl;

            cout << "Example: 0712345678" << endl;
        }

    }
    while (!isValidPhoneNumber(vehicle.phoneNumber));


    // RETURN COMPLETED VEHICLE
    return vehicle;
}
