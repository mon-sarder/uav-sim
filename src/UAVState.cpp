#include "UAVState.h"

std::string flightModeToString(FlightMode mode) {
    switch (mode) {
        case FlightMode::IDLE:       return "IDLE";
        case FlightMode::NAVIGATING: return "NAVIGATING";
        case FlightMode::HOVERING:   return "HOVERING";
        case FlightMode::RTL:        return "RTL";
        case FlightMode::LANDED:     return "LANDED";
        default:                     return "UNKNOWN";
    }
}