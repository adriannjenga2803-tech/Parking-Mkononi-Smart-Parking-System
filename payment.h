#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

using namespace std;


// PAYMENT STRUCTURE
struct Payment
{
    int paymentId;
    int sessionId;
    double amount;
    string paymentMethod;
    bool isPaid;
};


// CALCULATE PARKING FEE
double calculateParkingFee(
    int durationMinutes
);


// SELECT PAYMENT METHOD
string selectPaymentMethod(
    int choice
);


// VALIDATE PAYMENT CONFIRMATION
bool isValidPaymentConfirmation(
    char confirmation
);


// PROCESS PAYMENT CONFIRMATION
bool processPaymentConfirmation(
    char confirmation
);


// CREATE PAYMENT
Payment createPayment(
    int paymentId,
    int sessionId,
    double amount
);


// DISPLAY PAYMENT
void displayPayment(
    const Payment& payment
);

#endif
