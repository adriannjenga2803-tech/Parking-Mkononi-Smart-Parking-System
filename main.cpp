#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <thread>

#include "parking.h"
#include "vehicle.h"
#include "session.h"
#include "payment.h"
#include "storage.h"
#include "server.h"

using namespace std;


// FIND VEHICLE
int findVehicleIndex(
    const vector<Vehicle>& vehicles,
    int vehicleId)
{
    for (size_t i = 0; i < vehicles.size(); i++)
    {
        if (vehicles[i].id == vehicleId)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}


// CHECK WHETHER VEHICLE IS ALREADY PARKED
bool isVehicleAlreadyParked(
    const vector<ParkingSession>& sessions,
    int vehicleId)
{
    return hasActiveSession(
        sessions,
        vehicleId
    );
}


// GET NEXT VEHICLE ID
int getNextVehicleId(
    const vector<Vehicle>& vehicles)
{
    int highestId = 0;

    for (const Vehicle& vehicle : vehicles)
    {
        if (vehicle.id > highestId)
        {
            highestId = vehicle.id;
        }
    }

    return highestId + 1;
}


// GET NEXT SESSION ID
int getNextSessionId(
    const vector<ParkingSession>& sessions)
{
    int highestId = 0;

    for (const ParkingSession& session : sessions)
    {
        if (session.sessionId > highestId)
        {
            highestId = session.sessionId;
        }
    }

    return highestId + 1;
}


// GET NEXT PAYMENT ID
int getNextPaymentId(
    const vector<Payment>& payments)
{
    int highestId = 0;

    for (const Payment& payment : payments)
    {
        if (payment.paymentId > highestId)
        {
            highestId = payment.paymentId;
        }
    }

    return highestId + 1;
}


// RESTORE OCCUPIED PARKING SLOTS
void restoreOccupiedSlots(
    vector<ParkingSlot>& parkingSlots,
    const vector<ParkingSession>& sessions)
{
    for (const ParkingSession& session : sessions)
    {
        if (!session.isActive)
        {
            continue;
        }

        for (ParkingSlot& slot : parkingSlots)
        {
            if (slot.slotNumber == session.slotNumber)
            {
                slot.isOccupied = true;
                break;
            }
        }
    }
}


// MAIN PROGRAM
int main()
{

    // DISPLAY SYSTEM TITLE
    displaySystemTitle();


    // CREATE PARKING SLOTS
    vector<ParkingSlot> parkingSlots =
        createParkingSlots();


    // CREATE DATA COLLECTIONS
    vector<Vehicle> vehicles;

    vector<ParkingSession> sessions;

    vector<Payment> payments;


    // LOAD PREVIOUSLY SAVED DATA
    loadVehicles(
        vehicles,
        "vehicles.dat"
    );

    loadSessions(
        sessions,
        "sessions.dat"
    );

    loadPayments(
        payments,
        "payments.dat"
    );


    // RESTORE ACTIVE PARKING SLOTS
    restoreOccupiedSlots(
        parkingSlots,
        sessions
    );


    // START WEB SERVER
    thread webServerThread(
        startWebServer,
        &parkingSlots
    );

    webServerThread.detach();


    // INITIALIZE NEXT IDs
    int nextVehicleId =
        getNextVehicleId(vehicles);

    int nextSessionId =
        getNextSessionId(sessions);

    int nextPaymentId =
        getNextPaymentId(payments);


    // MAIN MENU
    int menuChoice = -1;


    while (menuChoice != 0)
    {
        cout << "\n";
        cout << "========================================" << endl;
        cout << "     PARKING MKONONI SMART PARKING" << endl;
        cout << "========================================" << endl;

        cout << "1. Display Parking Slots" << endl;
        cout << "2. Display Parking Tariff" << endl;
        cout << "3. Register Vehicle" << endl;
        cout << "4. Park Vehicle" << endl;
        cout << "5. Process Vehicle Exit" << endl;
        cout << "6. View Registered Vehicles" << endl;
        cout << "7. View Active Parking Sessions" << endl;
        cout << "0. Exit System" << endl;

        cout << "----------------------------------------" << endl;
        cout << "Enter your choice: ";


        cin >> menuChoice;


        // INVALID MENU INPUT
        if (cin.fail())
        {
            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "\nInvalid input." << endl;
            cout << "Please enter a number from 0 to 7."
                 << endl;

            continue;
        }


        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );


        // OPTION 1 - DISPLAY PARKING SLOTS
        if (menuChoice == 1)
        {
            cout << "\n";
            displayParkingSlots(parkingSlots);
        }


        // OPTION 2 - DISPLAY PARKING TARIFF
        else if (menuChoice == 2)
        {
            displayParkingTariff();
        }


        // OPTION 3 - REGISTER VEHICLE
        else if (menuChoice == 3)
        {
            cout << "\n";
            cout << "========================================"
                 << endl;

            cout << "         VEHICLE REGISTRATION"
                 << endl;

            cout << "========================================"
                 << endl;


            Vehicle vehicle =
                registerVehicle(
                    nextVehicleId,
                    vehicles
                );


            vehicles.push_back(vehicle);


            cout << "\nVehicle registered successfully."
                 << endl;


            displayVehicle(vehicle);


            nextVehicleId++;


            // Save updated vehicle records.
            saveVehicles(
                vehicles,
                "vehicles.dat"
            );
        }


        // OPTION 4 - PARK VEHICLE
        else if (menuChoice == 4)
        {
            cout << "\n";
            cout << "========================================"
                 << endl;

            cout << "             PARK VEHICLE"
                 << endl;

            cout << "========================================"
                 << endl;


            // CHECK WHETHER PARKING LOT IS FULL
            if (isParkingLotFull(parkingSlots))
            {
                cout << "\nThe parking lot is currently FULL."
                     << endl;

                cout << "No parking slots are available."
                     << endl;

                continue;
            }


            // DISPLAY AVAILABLE SLOTS
            displayParkingSlots(parkingSlots);


            // ENTER VEHICLE ID
            int vehicleId;

            cout << "\nEnter Vehicle ID: ";

            cin >> vehicleId;


            if (cin.fail())
            {
                cin.clear();

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                cout << "Invalid vehicle ID." << endl;

                continue;
            }


            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );


            // FIND VEHICLE
            int vehicleIndex =
                findVehicleIndex(
                    vehicles,
                    vehicleId
                );


            if (vehicleIndex == -1)
            {
                cout << "\nVehicle not found."
                     << endl;

                cout << "Please register the vehicle first."
                     << endl;

                continue;
            }


            // CHECK WHETHER VEHICLE IS ALREADY PARKED
            if (isVehicleAlreadyParked(
                    sessions,
                    vehicleId))
            {
                cout << "\nThis vehicle is already parked."
                     << endl;

                cout << "A vehicle cannot have two active "
                     << "parking sessions."
                     << endl;

                continue;
            }


            // ASSIGN AVAILABLE PARKING SLOT
            string assignedSlot;


            bool slotAssigned =
                assignParkingSlot(
                    parkingSlots,
                    assignedSlot
                );


            if (!slotAssigned)
            {
                cout << "\nUnable to assign a parking slot."
                     << endl;

                continue;
            }


            // CREATE PARKING SESSION
            ParkingSession session =
                createParkingSession(
                    nextSessionId,
                    vehicleId
                );


            session.slotNumber =
                assignedSlot;


            session.entryTime =
                getCurrentTime();


            session.exitTime = "";

            session.isActive = true;


            sessions.push_back(session);


            // SAVE SESSION
            saveSessions(
                sessions,
                "sessions.dat"
            );


            // DISPLAY PARKING CONFIRMATION
            cout << "\n========================================"
                 << endl;

            cout << "       VEHICLE PARKED SUCCESSFULLY"
                 << endl;

            cout << "========================================"
                 << endl;

            cout << "Vehicle Registration: "
                 << vehicles[vehicleIndex].registration
                 << endl;

            cout << "Parking Slot: "
                 << assignedSlot
                 << endl;

            cout << "Entry Time: "
                 << session.entryTime
                 << endl;

            cout << "Session ID: "
                 << session.sessionId
                 << endl;


            nextSessionId++;
        }


        // OPTION 5 - PROCESS VEHICLE EXIT
        else if (menuChoice == 5)
        {
            cout << "\n";
            cout << "========================================"
                 << endl;

            cout << "        PROCESS VEHICLE EXIT"
                 << endl;

            cout << "========================================"
                 << endl;


            // ENTER VEHICLE ID
            int vehicleId;

            cout << "Enter Vehicle ID: ";

            cin >> vehicleId;


            if (cin.fail())
            {
                cin.clear();

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                cout << "Invalid vehicle ID." << endl;

                continue;
            }


            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );


            // FIND VEHICLE
            int vehicleIndex =
                findVehicleIndex(
                    vehicles,
                    vehicleId
                );


            if (vehicleIndex == -1)
            {
                cout << "\nVehicle not found."
                     << endl;

                continue;
            }


            // FIND ACTIVE SESSION
            int sessionIndex =
                findActiveSessionIndex(
                    sessions,
                    vehicleId
                );


            if (sessionIndex == -1)
            {
                cout << "\nThis vehicle does not have "
                     << "an active parking session."
                     << endl;

                continue;
            }


            ParkingSession& session =
                sessions[sessionIndex];


            // DISPLAY CURRENT SESSION
            cout << "\nVehicle Registration: "
                 << vehicles[vehicleIndex].registration
                 << endl;

            cout << "Parking Slot: "
                 << session.slotNumber
                 << endl;

            cout << "Entry Time: "
                 << session.entryTime
                 << endl;


            // ENTER EXIT TIME
            string exitTime;


            do
            {
                cout << "\nEnter Exit Time (HH:MM): ";

                getline(
                    cin,
                    exitTime
                );


                if (!isValidTime(exitTime))
                {
                    cout << "Invalid time format."
                         << endl;

                    cout << "Please use HH:MM."
                         << endl;

                    cout << "Example: 14:30"
                         << endl;
                }

            }
            while (!isValidTime(exitTime));


            // VALIDATE EXIT TIME
            if (!isExitTimeValid(
                    session.entryTime,
                    exitTime))
            {
                cout << "\nInvalid exit time."
                     << endl;

                continue;
            }


            // CALCULATE DURATION
            int durationMinutes =
                calculateDuration(
                    session.entryTime,
                    exitTime
                );


            // CALCULATE PARKING FEE
            double parkingFee =
                calculateParkingFee(
                    durationMinutes
                );


            // DISPLAY EXIT INFORMATION
            cout << "\n========================================"
                 << endl;

            cout << "             PARKING SUMMARY"
                 << endl;

            cout << "========================================"
                 << endl;

            cout << "Vehicle Registration: "
                 << vehicles[vehicleIndex].registration
                 << endl;

            cout << "Parking Slot: "
                 << session.slotNumber
                 << endl;

            cout << "Entry Time: "
                 << session.entryTime
                 << endl;

            cout << "Exit Time: "
                 << exitTime
                 << endl;

            cout << "Duration: "
                 << durationMinutes
                 << " minutes"
                 << endl;

            cout << "Amount to Pay: KSh "
                 << parkingFee
                 << endl;


            // CREATE PAYMENT RECORD
            Payment payment =
                createPayment(
                    nextPaymentId,
                    session.sessionId,
                    parkingFee
                );


            // SELECT PAYMENT METHOD
            int paymentChoice = 0;


            do
            {
                cout << "\nSelect Payment Method:"
                     << endl;

                cout << "----------------------"
                     << endl;

                cout << "1. M-Pesa" << endl;
                cout << "2. Cash" << endl;
                cout << "3. Card" << endl;

                cout << "Enter your choice: ";


                cin >> paymentChoice;


                if (cin.fail())
                {
                    cin.clear();

                    cin.ignore(
                        numeric_limits<streamsize>::max(),
                        '\n'
                    );

                    cout << "Invalid input."
                         << endl;

                    paymentChoice = 0;
                }
                else if (
                    paymentChoice < 1 ||
                    paymentChoice > 3
                )
                {
                    cout << "Please select a number "
                         << "from 1 to 3."
                         << endl;
                }

            }
            while (
                paymentChoice < 1 ||
                paymentChoice > 3
            );


            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );


            payment.paymentMethod =
                selectPaymentMethod(
                    paymentChoice
                );


            // PAYMENT CONFIRMATION
            char confirmation;


            do
            {
                cout << "\nConfirm payment of KSh "
                     << parkingFee
                     << " using "
                     << payment.paymentMethod
                     << "? (Y/N): ";


                cin >> confirmation;


                if (!isValidPaymentConfirmation(
                        confirmation))
                {
                    cout << "Invalid choice."
                         << endl;

                    cout << "Please enter Y or N."
                         << endl;
                }

            }
            while (
                !isValidPaymentConfirmation(
                    confirmation
                )
            );


            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );


            // PROCESS PAYMENT
            bool paymentSuccessful =
                processPaymentConfirmation(
                    confirmation
                );


            if (!paymentSuccessful)
            {
                cout << "\nPayment was not completed."
                     << endl;

                cout << "The vehicle remains parked."
                     << endl;

                cout << "The parking slot remains occupied."
                     << endl;

                continue;
            }


            // PAYMENT SUCCESSFUL
            payment.isPaid = true;


            payments.push_back(payment);


            savePayments(
                payments,
                "payments.dat"
            );


            // COMPLETE PARKING SESSION
            session.exitTime =
                exitTime;

            session.isActive =
                false;


            // RELEASE PARKING SLOT
            releaseParkingSlot(
                parkingSlots,
                session.slotNumber
            );


            // SAVE UPDATED SESSION DATA
            saveSessions(
                sessions,
                "sessions.dat"
            );


            // DISPLAY PAYMENT INFORMATION
            displayPayment(payment);


            // DISPLAY EXIT AUTHORIZATION
            cout << "\n========================================"
                 << endl;

            cout << "          EXIT AUTHORIZED"
                 << endl;

            cout << "========================================"
                 << endl;

            cout << "Payment completed successfully."
                 << endl;

            cout << "Parking slot "
                 << session.slotNumber
                 << " is now available."
                 << endl;

            cout << "Barrier: OPEN"
                 << endl;

            cout << "Vehicle may exit the parking area."
                 << endl;


            nextPaymentId++;
        }


        // OPTION 6 - VIEW REGISTERED VEHICLES
        else if (menuChoice == 6)
        {
            cout << "\n";
            cout << "========================================"
                 << endl;

            cout << "        REGISTERED VEHICLES"
                 << endl;

            cout << "========================================"
                 << endl;


            if (vehicles.empty())
            {
                cout << "No vehicles are currently registered."
                     << endl;
            }
            else
            {
                for (const Vehicle& vehicle : vehicles)
                {
                    displayVehicle(vehicle);
                }
            }
        }


        // OPTION 7 - VIEW ACTIVE PARKING SESSIONS
        else if (menuChoice == 7)
        {
            cout << "\n";
            cout << "========================================"
                 << endl;

            cout << "        ACTIVE PARKING SESSIONS"
                 << endl;

            cout << "========================================"
                 << endl;


            bool activeSessionFound = false;


            for (const ParkingSession& session : sessions)
            {
                if (session.isActive)
                {
                    displayParkingSession(session);

                    activeSessionFound = true;
                }
            }


            if (!activeSessionFound)
            {
                cout << "There are currently no active "
                     << "parking sessions."
                     << endl;
            }
        }


        // OPTION 0 - EXIT SYSTEM
        else if (menuChoice == 0)
        {
            cout << "\n";
            cout << "========================================"
                 << endl;

            cout << "       SAVING SYSTEM DATA"
                 << endl;

            cout << "========================================"
                 << endl;


            // Save all current information before exiting.
            saveVehicles(
                vehicles,
                "vehicles.dat"
            );

            saveSessions(
                sessions,
                "sessions.dat"
            );

            savePayments(
                payments,
                "payments.dat"
            );


            cout << "\nAll system data has been saved."
                 << endl;

            cout << "Thank you for using "
                 << "Parking Mkononi."
                 << endl;

            cout << "Goodbye." << endl;
        }


        // INVALID MENU OPTION
        else
        {
            cout << "\nInvalid menu choice."
                 << endl;

            cout << "Please select an option from 0 to 7."
                 << endl;
        }
    }


    return 0;
}
