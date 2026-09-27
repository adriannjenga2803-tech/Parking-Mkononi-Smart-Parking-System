#include "parking.h"

#include <iostream>

using namespace std;


// DISPLAY ALL PARKING SLOTS
void displayParkingSlots(
    const vector<ParkingSlot>& parkingSlots)
{
    int availableSlots = 0;
    int occupiedSlots = 0;


    cout << "\nParking Slot Availability:" << endl;
    cout << "---------------------------" << endl;


    // Display every parking slot
    for (size_t i = 0; i < parkingSlots.size(); i++)
    {
        const ParkingSlot& slot =
            parkingSlots[i];


        cout << "[" << slot.slotNumber << ": ";


        if (slot.isOccupied)
        {
            cout << "OCCUPIED";

            occupiedSlots++;
        }
        else
        {
            cout << "AVAILABLE";

            availableSlots++;
        }


        cout << "]";


        // Put three parking slots on each line.
        if ((i + 1) % 3 == 0)
        {
            cout << endl;
        }
        else
        {
            cout << "   ";
        }
    }


    cout << endl;


    // Display parking statistics
    cout << "Available Slots: "
         << availableSlots
         << endl;


    cout << "Occupied Slots: "
         << occupiedSlots
         << endl;


    // Display overall parking status
    if (availableSlots > 0)
    {
        cout << "Parking Status: AVAILABLE"
             << endl;
    }
    else
    {
        cout << "Parking Status: FULL"
             << endl;
    }
}


// CHECK WHETHER PARKING LOT IS FULL
bool isParkingLotFull(
    const vector<ParkingSlot>& parkingSlots)
{


    for (const ParkingSlot& slot : parkingSlots)
    {
        if (!slot.isOccupied)
        {
            return false;
        }
    }


    return true;
}


// COUNT AVAILABLE PARKING SLOTS
int getAvailableSlotCount(
    const vector<ParkingSlot>& parkingSlots)
{
    int availableSlots = 0;


    for (const ParkingSlot& slot : parkingSlots)
    {
        if (!slot.isOccupied)
        {
            availableSlots++;
        }
    }


    return availableSlots;
}


// COUNT OCCUPIED PARKING SLOTS
int getOccupiedSlotCount(
    const vector<ParkingSlot>& parkingSlots)
{
    int occupiedSlots = 0;


    for (const ParkingSlot& slot : parkingSlots)
    {
        if (slot.isOccupied)
        {
            occupiedSlots++;
        }
    }


    return occupiedSlots;
}


// ASSIGN AVAILABLE PARKING SLOT
bool assignParkingSlot(
    vector<ParkingSlot>& parkingSlots,
    string& assignedSlot)
{


    for (ParkingSlot& slot : parkingSlots)
    {
        if (!slot.isOccupied)
        {
            // Store the assigned slot number.
            assignedSlot =
                slot.slotNumber;


            // Mark the slot as occupied.
            slot.isOccupied = true;


            return true;
        }
    }


    // No available slot was found.
    return false;
}


// RELEASE PARKING SLOT
bool releaseParkingSlot(
    vector<ParkingSlot>& parkingSlots,
    const string& slotNumber)
{


    for (ParkingSlot& slot : parkingSlots)
    {
        if (slot.slotNumber == slotNumber)
        {


            if (!slot.isOccupied)
            {
                return false;
            }


            // Mark the slot as available.
            slot.isOccupied = false;


            return true;
        }
    }


    // The requested slot does not exist.
    return false;
}


// CHECK WHETHER A PARKING SLOT EXISTS
bool parkingSlotExists(
    const vector<ParkingSlot>& parkingSlots,
    const string& slotNumber)
{
    for (const ParkingSlot& slot : parkingSlots)
    {
        if (slot.slotNumber == slotNumber)
        {
            return true;
        }
    }


    return false;
}


// CHECK WHETHER A PARKING SLOT IS AVAILABLE
bool isParkingSlotAvailable(
    const vector<ParkingSlot>& parkingSlots,
    const string& slotNumber)
{
    for (const ParkingSlot& slot : parkingSlots)
    {
        if (slot.slotNumber == slotNumber)
        {
            return !slot.isOccupied;
        }
    }


    return false;
}


// CREATE INITIAL PARKING SLOTS
vector<ParkingSlot> createParkingSlots()
{

    vector<ParkingSlot> parkingSlots =
    {
        {1, "A1", false},
        {2, "A2", false},
        {3, "A3", true},
        {4, "A4", false},
        {5, "A5", true},
        {6, "A6", false}
    };


    return parkingSlots;
}


// DISPLAY SYSTEM TITLE
void displaySystemTitle()
{
    cout << "===================================="
         << endl;

    cout << "     Parking Mkononi Smart Parking System"
         << endl;

    cout << "===================================="
         << endl;
}


// DISPLAY PARKING TARIFF
void displayParkingTariff()
{
    cout << "\nParking Tariff:"
         << endl;

    cout << "---------------"
         << endl;

    cout << "Up to 30 minutes : FREE"
         << endl;

    cout << "Up to 2 hours    : KSh 50"
         << endl;

    cout << "Up to 4 hours    : KSh 100"
         << endl;

    cout << "Up to 6 hours    : KSh 300"
         << endl;

    cout << "Over 6 hours     : KSh 500"
         << endl;
}


// GENERATE LIVE PARKING SLOT HTML
string generateParkingSlotsHTML(
    const vector<ParkingSlot>& parkingSlots)
{
    string html;


    html +=
        "<div class=\"parking-slots\">";


    // Generate one HTML card for every parking slot
    for (const ParkingSlot& slot : parkingSlots)
    {
        html +=
            "<div class=\"slot ";


        // Apply the correct CSS class.
        if (slot.isOccupied)
        {
            html += "occupied\">";
        }
        else
        {
            html += "available\">";
        }


        // Parking slot name.
        html +=
            "<h3>";

        html +=
            slot.slotNumber;

        html +=
            "</h3>";


        // Parking slot status.
        if (slot.isOccupied)
        {
            html +=
                "<p>OCCUPIED</p>";
        }
        else
        {
            html +=
                "<p>AVAILABLE</p>";
        }


        html +=
            "</div>";
    }


    html +=
        "</div>";


    return html;
}


// GENERATE LIVE PARKING SUMMARY HTML
string generateParkingSummaryHTML(
    const vector<ParkingSlot>& parkingSlots)
{
    // Calculate the current parking statistics.
    int availableSlots =
        getAvailableSlotCount(
            parkingSlots
        );


    int occupiedSlots =
        getOccupiedSlotCount(
            parkingSlots
        );


    int totalSlots =
        static_cast<int>(
            parkingSlots.size()
        );


    string parkingStatus;


    // Determine whether spaces are still available.
    if (availableSlots > 0)
    {
        parkingStatus =
            "AVAILABLE";
    }
    else
    {
        parkingStatus =
            "FULL";
    }


    string html;


    // Parking summary container
    html +=
        "<div class=\"parking-summary\">";


    // Available slots
    html +=
        "<p>"
        "<strong>Available Slots:</strong> ";

    html +=
        to_string(availableSlots);

    html +=
        "</p>";


    // Occupied slots
    html +=
        "<p>"
        "<strong>Occupied Slots:</strong> ";

    html +=
        to_string(occupiedSlots);

    html +=
        "</p>";


    // Total slots
    html +=
        "<p>"
        "<strong>Total Slots:</strong> ";

    html +=
        to_string(totalSlots);

    html +=
        "</p>";


    // Overall parking status
    html +=
        "<p>"
        "<strong>Parking Status:</strong> ";

    html +=
        parkingStatus;

    html +=
        "</p>";


    html +=
        "</div>";


    return html;
}
