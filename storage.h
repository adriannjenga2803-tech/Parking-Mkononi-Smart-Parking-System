#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

#include "vehicle.h"
#include "session.h"
#include "payment.h"

using namespace std;


// VEHICLE STORAGE
bool saveVehicles(
    const vector<Vehicle>& vehicles,
    const string& filename
);

bool loadVehicles(
    vector<Vehicle>& vehicles,
    const string& filename
);


// PARKING SESSION STORAGE
bool saveSessions(
    const vector<ParkingSession>& sessions,
    const string& filename
);

bool loadSessions(
    vector<ParkingSession>& sessions,
    const string& filename
);


// PAYMENT STORAGE
bool savePayments(
    const vector<Payment>& payments,
    const string& filename
);

bool loadPayments(
    vector<Payment>& payments,
    const string& filename
);

#endif
