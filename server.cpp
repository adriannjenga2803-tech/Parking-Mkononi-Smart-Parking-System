#include "server.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include "parking.h"

using namespace std;

// WEB FILE LOCATIONS
const string INDEX_FILE =
    "web/index.html";

const string CSS_FILE =
    "web/styles.css";

// READ HTML/CSS FILE
string readWebFile(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "ERROR: Could not open web file: "
             << filename << endl;

        return "";
    }

    string content;
    string line;

    while (getline(file, line))
    {
        content += line;
        content += "\n";
    }

    file.close();

    return content;
}


// SEND HTTP RESPONSE
#ifdef _WIN32

void sendHTTPResponse(
    SOCKET clientSocket,
    const string& content,
    const string& contentType)
{
    string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: " + contentType + "\r\n"
        "Content-Length: " +
        to_string(content.length()) +
        "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        content;

    send(
        clientSocket,
        response.c_str(),
        static_cast<int>(response.length()),
        0
    );
}


// SEND 404 RESPONSE
void sendNotFoundResponse(
    SOCKET clientSocket)
{
    string notFound =
        "<html>"
        "<head>"
        "<title>404 - Not Found</title>"
        "</head>"
        "<body>"
        "<h1>404 - Page Not Found</h1>"
        "<p>The requested page could not be found.</p>"
        "</body>"
        "</html>";

    string response =
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " +
        to_string(notFound.length()) +
        "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        notFound;

    send(
        clientSocket,
        response.c_str(),
        static_cast<int>(response.length()),
        0
    );
}

#endif


// GENERATE PARKING SUMMARY
string generateParkingSummary(
    const vector<ParkingSlot>& parkingSlots)
{
    int availableSlots =
        getAvailableSlotCount(parkingSlots);

    int occupiedSlots =
        getOccupiedSlotCount(parkingSlots);

    int totalSlots =
        static_cast<int>(parkingSlots.size());

    string parkingStatus;

    if (availableSlots == 0)
    {
        parkingStatus = "FULL";
    }
    else
    {
        parkingStatus = "AVAILABLE";
    }

    string html;

    html += "<div class=\"parking-summary\">";

    html += "<p>";
    html += "<strong>Available Slots:</strong> ";
    html += to_string(availableSlots);
    html += "</p>";

    html += "<p>";
    html += "<strong>Occupied Slots:</strong> ";
    html += to_string(occupiedSlots);
    html += "</p>";

    html += "<p>";
    html += "<strong>Total Slots:</strong> ";
    html += to_string(totalSlots);
    html += "</p>";

    html += "<p>";
    html += "<strong>Parking Status:</strong> ";
    html += parkingStatus;
    html += "</p>";

    html += "</div>";

    return html;
}


// GENERATE COMPLETE PARKING PAGE
string generateParkingPage(
    const vector<ParkingSlot>& parkingSlots)
{
    string html =
        readWebFile(INDEX_FILE);

    if (html.empty())
    {
        return "";
    }


    // GENERATE PARKING SLOT DISPLAY
    string parkingSlotsHTML =
        generateParkingSlotsHTML(parkingSlots);


    // REPLACE PARKING SLOT PLACEHOLDER
    const string slotsPlaceholder =
        "<!-- PARKING_SLOTS -->";

    size_t slotsPosition =
        html.find(slotsPlaceholder);

    if (slotsPosition != string::npos)
    {
        html.replace(
            slotsPosition,
            slotsPlaceholder.length(),
            parkingSlotsHTML
        );
    }


    // GENERATE PARKING SUMMARY
    string parkingSummaryHTML =
        generateParkingSummary(parkingSlots);


    // REPLACE PARKING SUMMARY PLACEHOLDER
    const string summaryPlaceholder =
        "<!-- PARKING_SUMMARY -->";

    size_t summaryPosition =
        html.find(summaryPlaceholder);

    if (summaryPosition != string::npos)
    {
        html.replace(
            summaryPosition,
            summaryPlaceholder.length(),
            parkingSummaryHTML
        );
    }


    return html;
}


// START WEB SERVER
void startWebServer(
    const vector<ParkingSlot>* parkingSlots)
{
#ifdef _WIN32


    // CHECK PARKING DATA
    if (parkingSlots == nullptr)
    {
        cout << "Error: Parking slot data is unavailable."
             << endl;

        return;
    }


    // START WINDOWS SOCKET SYSTEM
    WSADATA wsaData;

    if (WSAStartup(
            MAKEWORD(2, 2),
            &wsaData) != 0)
    {
        cout << "Error: Unable to start Windows networking."
             << endl;

        return;
    }


    // CREATE SERVER SOCKET
    SOCKET serverSocket =
        socket(
            AF_INET,
            SOCK_STREAM,
            IPPROTO_TCP
        );

    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Error: Unable to create server socket."
             << endl;

        WSACleanup();

        return;
    }


    // CONFIGURE SERVER ADDRESS
    sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;

    serverAddress.sin_addr.s_addr =
        inet_addr("127.0.0.1");

    serverAddress.sin_port =
        htons(8080);


    // BIND SERVER TO PORT 8080
    if (bind(
            serverSocket,
            reinterpret_cast<sockaddr*>(
                &serverAddress
            ),
            sizeof(serverAddress)
        ) == SOCKET_ERROR)
    {
        cout << "Error: Unable to bind web server."
             << endl;

        closesocket(serverSocket);

        WSACleanup();

        return;
    }


    // START LISTENING
    if (listen(serverSocket, 5) == SOCKET_ERROR)
    {
        cout << "Error: Unable to start listening."
             << endl;

        closesocket(serverSocket);

        WSACleanup();

        return;
    }


    // SERVER STARTUP MESSAGE
    cout << endl;
    cout << "====================================" << endl;
    cout << "   Parking Mkononi Web Server" << endl;
    cout << "====================================" << endl;
    cout << "Web server started successfully." << endl;
    cout << "Open your browser and visit:" << endl;
    cout << "http://localhost:8080" << endl;
    cout << "====================================" << endl;


    // ACCEPT BROWSER CONNECTIONS
    while (true)
    {
        sockaddr_in clientAddress;

        int clientAddressSize =
            sizeof(clientAddress);

        SOCKET clientSocket =
            accept(
                serverSocket,
                reinterpret_cast<sockaddr*>(
                    &clientAddress
                ),
                &clientAddressSize
            );

        if (clientSocket == INVALID_SOCKET)
        {
            cout << "Error accepting browser connection."
                 << endl;

            continue;
        }


        // RECEIVE HTTP REQUEST
        char buffer[4096];

        int bytesReceived =
            recv(
                clientSocket,
                buffer,
                sizeof(buffer) - 1,
                0
            );

        if (bytesReceived <= 0)
        {
            closesocket(clientSocket);

            continue;
        }

        buffer[bytesReceived] = '\0';

        string request(buffer);


        // SERVE MAIN WEBSITE
        if (
            request.find("GET / ") != string::npos ||
            request.find("GET /HTTP") != string::npos
        )
        {
            string html =
                generateParkingPage(*parkingSlots);

            if (html.empty())
            {
                html =
                    "<html>"
                    "<body>"
                    "<h1>Parking Mkononi</h1>"
                    "<p>Unable to load the web page.</p>"
                    "</body>"
                    "</html>";
            }

            sendHTTPResponse(
                clientSocket,
                html,
                "text/html"
            );
        }


        // SERVE CSS FILES
        else if (
            request.find("GET /styles.css")
            != string::npos
        )
        {
            string css =
                readWebFile(CSS_FILE);

            if (css.empty())
            {
                css =
                    "body { "
                    "font-family: Arial; "
                    "}";
            }

            sendHTTPResponse(
                clientSocket,
                css,
                "text/css"
            );
        }


        // UNKNOWN REQUEST
        else
        {
            sendNotFoundResponse(clientSocket);
        }


        // CLOSE CLIENT CONNECTION
        closesocket(clientSocket);
    }


    closesocket(serverSocket);

    WSACleanup();

#else

    cout << "The current web server implementation "
         << "requires Windows." << endl;

#endif
}
