#include "UAVController.h"

UAVController::UAVController() = default;

void UAVController::setTarget(const Vec3& target) {
    target_ = target;
    hasTarget_ = true;
    state_.mode = FlightMode::NAVIGATING;
}

bool UAVController::hasReachedTarget() const {
    if (!hasTarget_) {
        return false;
    }
    return state_.position.distanceTo(target_) <= kArrivalThreshold;
}

void UAVController::update(double dt) {
    state_.timestamp += dt;

    // Nothing to do if there's no target or battery is dead
    if (!hasTarget_ || state_.battery <= 0.0) {
        state_.velocity = Vec3(0.0, 0.0, 0.0);
        return;
    }

    if (hasReachedTarget()) {
        state_.velocity = Vec3(0.0, 0.0, 0.0);
        state_.mode = FlightMode::HOVERING;
        return;
    }

    // Direction from current position to target, scaled to max speed
    Vec3 direction = (target_ - state_.position).normalized();
    state_.velocity = direction * kMaxSpeed;

    // Integrate position: position += velocity * dt
    state_.position = state_.position + (state_.velocity * dt);

    // Drain battery proportional to speed and time
    double speed = state_.velocity.magnitude();
    state_.battery -= (speed / kMaxSpeed) * kBatteryDrainRate * dt;
    if (state_.battery < 0.0) {
        state_.battery = 0.0;
    }
}

const UAVState& UAVController::getState() const {
    return state_;
}