#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <vector>

using namespace std;


// PARKING SESSION STRUCTURE
struct ParkingSession
{
    int sessionId;
    int vehicleId;
    string slotNumber;
    string entryTime;
    string exitTime;
    bool isActive;
};


// GET CURRENT SYSTEM TIME
string getCurrentTime();


// VALIDATE TIME
bool isValidTime(
    const string& time
);


// VALIDATE EXIT TIME
bool isExitTimeValid(
    const string& entryTime,
    const string& exitTime
);


// CALCULATE PARKING DURATION
int calculateDuration(
    const string& entryTime,
    const string& exitTime
);


// CREATE PARKING SESSION
ParkingSession createParkingSession(
    int sessionId,
    int vehicleId
);


// DISPLAY PARKING SESSION
void displayParkingSession(
    const ParkingSession& session
);


// CHECK FOR ACTIVE VEHICLE SESSION
bool hasActiveSession(
    const vector<ParkingSession>& sessions,
    int vehicleId
);


// FIND ACTIVE SESSION
int findActiveSessionIndex(
    const vector<ParkingSession>& sessions,
    int vehicleId
);

#endif
