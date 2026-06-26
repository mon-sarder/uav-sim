#pragma once

#include <vector>
#include "UAVController.h"
#include "Vec3.h"

// Holds an ordered list of waypoints and drives a UAVController through them.
// Decides when to advance to the next waypoint and what to do when the
// mission is complete or battery runs low.
class MissionManager {
public:
    MissionManager(UAVController& controller, std::vector<Vec3> waypoints);

    // Advances the mission by dt seconds: ticks the controller and
    // checks whether it's time to advance to the next waypoint.
    void update(double dt);

    // True once every waypoint has been visited.
    bool isMissionComplete() const;

    // Index of the waypoint currently being flown to (for logging/telemetry).
    size_t currentWaypointIndex() const;

private:
    UAVController& controller_;
    std::vector<Vec3> waypoints_;
    size_t currentIndex_ = 0;
    bool missionStarted_ = false;

    static constexpr double kLowBatteryThreshold = 15.0; // percent
};