#include "payment.h"

#include <iostream>
#include <iomanip>

using namespace std;


// CALCULATE PARKING FEE
double calculateParkingFee(int durationMinutes)
{
    // Prevent negative durations from producing an invalid fee.
    if (durationMinutes < 0)
    {
        return 0;
    }

    if (durationMinutes <= 30)
    {
        return 0;
    }
    else if (durationMinutes <= 120)
    {
        return 50;
    }
    else if (durationMinutes <= 240)
    {
        return 100;
    }
    else if (durationMinutes <= 360)
    {
        return 300;
    }
    else
    {
        return 500;
    }
}


// SELECT PAYMENT METHOD
string selectPaymentMethod(int choice)
{
    if (choice == 1)
    {
        return "M-Pesa";
    }
    else if (choice == 2)
    {
        return "Cash";
    }
    else if (choice == 3)
    {
        return "Card";
    }

    return "Unknown";
}


// VALIDATE PAYMENT CONFIRMATION
bool isValidPaymentConfirmation(char confirmation)
{
    return confirmation == 'Y' ||
           confirmation == 'y' ||
           confirmation == 'N' ||
           confirmation == 'n';
}


// PROCESS PAYMENT CONFIRMATION
bool processPaymentConfirmation(char confirmation)
{
    if (confirmation == 'Y' ||
        confirmation == 'y')
    {
        return true;
    }

    return false;
}


// CREATE PAYMENT
Payment createPayment(
    int paymentId,
    int sessionId,
    double amount)
{
    Payment payment;

    payment.paymentId = paymentId;
    payment.sessionId = sessionId;
    payment.amount = amount;
    payment.paymentMethod = "Not selected";
    payment.isPaid = false;

    return payment;
}


// DISPLAY PAYMENT INFORMATION
void displayPayment(const Payment& payment)
{
    cout << "\nPayment Information:" << endl;
    cout << "--------------------" << endl;

    cout << "Payment ID: "
         << payment.paymentId << endl;

    cout << "Session ID: "
         << payment.sessionId << endl;

    cout << "Amount: KSh "
         << fixed
         << setprecision(2)
         << payment.amount
         << endl;

    cout << "Payment Method: "
         << payment.paymentMethod
         << endl;

    cout << "Payment Status: ";

    if (payment.isPaid)
    {
        cout << "PAID" << endl;
    }
    else
    {
        cout << "PENDING" << endl;
    }
}
