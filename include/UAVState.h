#pragma once

#include <string>

// Flight modes the UAV can be in at any given time
enum class FlightMode {
    IDLE,
    NAVIGATING,
    HOVERING,
    RTL,       // Return to launch
    LANDED
};

// Converts a FlightMode to a readable string for logging/telemetry
std::string flightModeToString(FlightMode mode);

// The complete state of the UAV at a single point in time.
// Every system (navigation, telemetry, logging) reads from this struct.
struct UAVState {
    // Position in meters (x = east, y = north, z = altitude)
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    // Velocity in m/s
    double vx = 0.0;
    double vy = 0.0;
    double vz = 0.0;

    // Heading in radians (0 = north, increases clockwise)
    double heading = 0.0;

    // Battery percentage 0–100
    double battery = 100.0;

    // Current flight mode
    FlightMode mode = FlightMode::IDLE;

    // Simulation time in seconds
    double timestamp = 0.0;
};