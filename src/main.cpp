#include <iostream>
#include "UAVState.h"

int main() {
    // Initialize UAV in idle state at origin
    UAVState uav;
    uav.mode = FlightMode::IDLE;

    std::cout << "UAV SIM v0.1 -- ONLINE" << std::endl;
    std::cout << "Position : ("
              << uav.x << ", "
              << uav.y << ", "
              << uav.z << ")" << std::endl;
    std::cout << "Battery  : " << uav.battery << "%" << std::endl;
    std::cout << "Mode     : " << flightModeToString(uav.mode) << std::endl;

    return 0;
}