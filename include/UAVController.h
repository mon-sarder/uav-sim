#pragma once

#include "UAVState.h"
#include "Vec3.h"

// Owns a UAVState and knows how to advance it one simulation tick at a time.
// This is the "physics" layer — it doesn't know about waypoints or missions,
// only how to move toward a single target point and drain battery doing so.
class UAVController {
public:
    UAVController();

    // Advances the UAV state by dt seconds, moving toward currentTarget.
    void update(double dt);

    // Sets the point the UAV should fly toward.
    void setTarget(const Vec3& target);

    // Read-only access to current state (for telemetry, tests, GCS, etc.)
    const UAVState& getState() const;

    // True once the UAV is within arrivalThreshold meters of currentTarget.
    bool hasReachedTarget() const;

private:
    UAVState state_;
    Vec3 target_;
    bool hasTarget_ = false;

    static constexpr double kMaxSpeed = 8.0;           // m/s
    static constexpr double kBatteryDrainRate = 0.05;  // % per second at max speed
    static constexpr double kArrivalThreshold = 0.5;   // meters
};