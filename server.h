#ifndef SERVER_H
#define SERVER_H

#include <vector>

struct ParkingSlot;


// START WEB SERVER
void startWebServer(
    const std::vector<ParkingSlot>* parkingSlots
);

#endif
