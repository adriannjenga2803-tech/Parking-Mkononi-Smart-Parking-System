#include "session.h"

#include <cctype>
#include <ctime>
#include <iostream>

using namespace std;


// GET CURRENT SYSTEM TIME
string getCurrentTime()
{
    time_t currentTime = time(0);

    tm* localTime = localtime(&currentTime);

    if (localTime == nullptr)
    {
        return "00:00";
    }

    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;

    string timeString;

    // Add leading zero to the hour when necessary.
    if (hour < 10)
    {
        timeString += "0";
    }

    timeString += to_string(hour);

    timeString += ":";

    // Add leading zero to the minute when necessary.
    if (minute < 10)
    {
        timeString += "0";
    }

    timeString += to_string(minute);

    return timeString;
}


// VALIDATE TIME
bool isValidTime(const string& time)
{
    // Time must contain exactly five characters.
    if (time.length() != 5)
    {
        return false;
    }

    // The third character must be ':'.
    if (time[2] != ':')
    {
        return false;
    }

    // Check that all other characters are numbers.
    for (int i = 0; i < 5; i++)
    {
        if (i == 2)
        {
            continue;
        }

        unsigned char currentCharacter =
            static_cast<unsigned char>(time[i]);

        if (!isdigit(currentCharacter))
        {
            return false;
        }
    }

    // Convert the hour and minute portions to integers.
    int hour =
        stoi(time.substr(0, 2));

    int minute =
        stoi(time.substr(3, 2));

    // Validate hour.
    if (hour < 0 || hour > 23)
    {
        return false;
    }

    // Validate minute.
    if (minute < 0 || minute > 59)
    {
        return false;
    }

    return true;
}


// VALIDATE EXIT TIME
bool isExitTimeValid(
    const string& entryTime,
    const string& exitTime)
{
    if (!isValidTime(entryTime))
    {
        return false;
    }

    if (!isValidTime(exitTime))
    {
        return false;
    }

    return true;
}


// CALCULATE PARKING DURATION
int calculateDuration(
    const string& entryTime,
    const string& exitTime)
{
    // Make sure both times are valid before processing them.
    if (!isValidTime(entryTime) ||
        !isValidTime(exitTime))
    {
        return 0;
    }

    // Extract entry hour and minute.
    int entryHour =
        stoi(entryTime.substr(0, 2));

    int entryMinute =
        stoi(entryTime.substr(3, 2));

    // Extract exit hour and minute.
    int exitHour =
        stoi(exitTime.substr(0, 2));

    int exitMinute =
        stoi(exitTime.substr(3, 2));

    // Convert both times into total minutes from midnight.
    int entryTotalMinutes =
        (entryHour * 60) + entryMinute;

    int exitTotalMinutes =
        (exitHour * 60) + exitMinute;

    // If exit time is earlier than entry time, the session
    // passed midnight.
    if (exitTotalMinutes < entryTotalMinutes)
    {
        exitTotalMinutes += 24 * 60;
    }

    int duration =
        exitTotalMinutes - entryTotalMinutes;

    return duration;
}


// CREATE PARKING SESSION
ParkingSession createParkingSession(
    int sessionId,
    int vehicleId)
{
    ParkingSession session;

    session.sessionId = sessionId;
    session.vehicleId = vehicleId;
    session.slotNumber = "";
    session.entryTime = "";
    session.exitTime = "";
    session.isActive = false;

    return session;
}


// DISPLAY PARKING SESSION
void displayParkingSession(
    const ParkingSession& session)
{
    cout << "\nParking Session Information:" << endl;
    cout << "----------------------------" << endl;

    cout << "Session ID: "
         << session.sessionId << endl;

    cout << "Vehicle ID: "
         << session.vehicleId << endl;

    cout << "Parking Slot: "
         << session.slotNumber << endl;

    cout << "Entry Time: "
         << session.entryTime << endl;

    // Display exit time when the session is completed.
    if (!session.exitTime.empty())
    {
        cout << "Exit Time: "
             << session.exitTime << endl;
    }
    else
    {
        cout << "Exit Time: Still parked" << endl;
    }

    cout << "Session Status: ";

    if (session.isActive)
    {
        cout << "ACTIVE" << endl;
    }
    else
    {
        cout << "COMPLETED" << endl;
    }
}


// CHECK WHETHER VEHICLE HAS AN ACTIVE SESSION
bool hasActiveSession(
    const vector<ParkingSession>& sessions,
    int vehicleId)
{
    for (const ParkingSession& session : sessions)
    {
        if (session.vehicleId == vehicleId &&
            session.isActive)
        {
            return true;
        }
    }

    return false;
}


// FIND ACTIVE SESSION INDEX
int findActiveSessionIndex(
    const vector<ParkingSession>& sessions,
    int vehicleId)
{
    for (size_t i = 0; i < sessions.size(); i++)
    {
        if (sessions[i].vehicleId == vehicleId &&
            sessions[i].isActive)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}
