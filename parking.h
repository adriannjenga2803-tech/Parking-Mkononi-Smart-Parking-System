#ifndef PARKING_H
#define PARKING_H

#include <string>
#include <vector>

using namespace std;


// PARKING SLOT STRUCTURE
struct ParkingSlot
{
    int id;

    string slotNumber;

    bool isOccupied;
};


// PARKING DISPLAY FUNCTIONS
void displayParkingSlots(
    const vector<ParkingSlot>& parkingSlots
);


// Check whether the entire parking lot is full.
bool isParkingLotFull(
    const vector<ParkingSlot>& parkingSlots
);


// Count the number of available parking slots.
int getAvailableSlotCount(
    const vector<ParkingSlot>& parkingSlots
);


// Count the number of occupied parking slots.
int getOccupiedSlotCount(
    const vector<ParkingSlot>& parkingSlots
);


// PARKING SLOT OPERATIONS
bool assignParkingSlot(
    vector<ParkingSlot>& parkingSlots,
    string& assignedSlot
);


// Release an occupied parking slot.
bool releaseParkingSlot(
    vector<ParkingSlot>& parkingSlots,
    const string& slotNumber
);


// Check whether a specific parking slot exists.
bool parkingSlotExists(
    const vector<ParkingSlot>& parkingSlots,
    const string& slotNumber
);


// Check whether a specific parking slot is available.
bool isParkingSlotAvailable(
    const vector<ParkingSlot>& parkingSlots,
    const string& slotNumber
);


// PARKING INITIALIZATION
vector<ParkingSlot> createParkingSlots();


// SYSTEM DISPLAY
void displaySystemTitle();


// Display the parking tariff.
void displayParkingTariff();


// WEB DASHBOARD SUPPORT
string generateParkingSlotsHTML(
    const vector<ParkingSlot>& parkingSlots
);


// Generate HTML for the parking summary.
string generateParkingSummaryHTML(
    const vector<ParkingSlot>& parkingSlots
);


#endif
