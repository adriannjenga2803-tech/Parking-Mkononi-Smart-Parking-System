#include "storage.h"

#include <fstream>
#include <iostream>

using namespace std;


// SAVE VEHICLES
bool saveVehicles(
    const vector<Vehicle>& vehicles,
    const string& filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "Error: Unable to save vehicle records."
             << endl;

        return false;
    }

    for (const Vehicle& vehicle : vehicles)
    {
        file << vehicle.id << '|'
             << vehicle.registration << '|'
             << vehicle.vehicleType << '|'
             << vehicle.ownerName << '|'
             << vehicle.phoneNumber
             << '\n';
    }

    file.close();

    return true;
}


// LOAD VEHICLES
bool loadVehicles(
    vector<Vehicle>& vehicles,
    const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    vehicles.clear();

    string id;
    string registration;
    string vehicleType;
    string ownerName;
    string phoneNumber;

    while (getline(file, id, '|'))
    {
        if (!getline(file, registration, '|'))
        {
            break;
        }

        if (!getline(file, vehicleType, '|'))
        {
            break;
        }

        if (!getline(file, ownerName, '|'))
        {
            break;
        }

        if (!getline(file, phoneNumber))
        {
            break;
        }

        try
        {
            Vehicle vehicle;

            vehicle.id = stoi(id);
            vehicle.registration = registration;
            vehicle.vehicleType = vehicleType;
            vehicle.ownerName = ownerName;
            vehicle.phoneNumber = phoneNumber;

            vehicles.push_back(vehicle);
        }
        catch (...)
        {
            cout << "Warning: Invalid vehicle record found "
                 << "in storage file." << endl;
        }
    }

    file.close();

    return true;
}


// SAVE PARKING SESSIONS
bool saveSessions(
    const vector<ParkingSession>& sessions,
    const string& filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "Error: Unable to save parking sessions."
             << endl;

        return false;
    }

    for (const ParkingSession& session : sessions)
    {
        file << session.sessionId << '|'
             << session.vehicleId << '|'
             << session.slotNumber << '|'
             << session.entryTime << '|'
             << session.exitTime << '|'
             << session.isActive
             << '\n';
    }

    file.close();

    return true;
}


// LOAD PARKING SESSIONS
bool loadSessions(
    vector<ParkingSession>& sessions,
    const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    sessions.clear();

    string sessionId;
    string vehicleId;
    string slotNumber;
    string entryTime;
    string exitTime;
    string active;

    while (getline(file, sessionId, '|'))
    {
        if (!getline(file, vehicleId, '|'))
        {
            break;
        }

        if (!getline(file, slotNumber, '|'))
        {
            break;
        }

        if (!getline(file, entryTime, '|'))
        {
            break;
        }

        if (!getline(file, exitTime, '|'))
        {
            break;
        }

        if (!getline(file, active))
        {
            break;
        }

        try
        {
            ParkingSession session;

            session.sessionId = stoi(sessionId);
            session.vehicleId = stoi(vehicleId);
            session.slotNumber = slotNumber;
            session.entryTime = entryTime;
            session.exitTime = exitTime;
            session.isActive = (active == "1");

            sessions.push_back(session);
        }
        catch (...)
        {
            cout << "Warning: Invalid parking session record "
                 << "found in storage file." << endl;
        }
    }

    file.close();

    return true;
}


// SAVE PAYMENTS
bool savePayments(
    const vector<Payment>& payments,
    const string& filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "Error: Unable to save payment records."
             << endl;

        return false;
    }

    for (const Payment& payment : payments)
    {
        file << payment.paymentId << '|'
             << payment.sessionId << '|'
             << payment.amount << '|'
             << payment.paymentMethod << '|'
             << payment.isPaid
             << '\n';
    }

    file.close();

    return true;
}


// LOAD PAYMENTS
bool loadPayments(
    vector<Payment>& payments,
    const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    payments.clear();

    string paymentId;
    string sessionId;
    string amount;
    string paymentMethod;
    string paid;

    while (getline(file, paymentId, '|'))
    {
        if (!getline(file, sessionId, '|'))
        {
            break;
        }

        if (!getline(file, amount, '|'))
        {
            break;
        }

        if (!getline(file, paymentMethod, '|'))
        {
            break;
        }

        if (!getline(file, paid))
        {
            break;
        }

        try
        {
            Payment payment;

            payment.paymentId = stoi(paymentId);
            payment.sessionId = stoi(sessionId);
            payment.amount = stod(amount);
            payment.paymentMethod = paymentMethod;
            payment.isPaid = (paid == "1");

            payments.push_back(payment);
        }
        catch (...)
        {
            cout << "Warning: Invalid payment record "
                 << "found in storage file." << endl;
        }
    }

    file.close();

    return true;
}
