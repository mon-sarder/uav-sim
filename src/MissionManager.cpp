#include "MissionManager.h"

MissionManager::MissionManager(UAVController& controller, std::vector<Vec3> waypoints)
    : controller_(controller), waypoints_(std::move(waypoints)) {}

void MissionManager::update(double dt) {
    if (isMissionComplete()) {
        return;
    }

    // On the first tick, point the controller at waypoint 0
    if (!missionStarted_) {
        controller_.setTarget(waypoints_[currentIndex_]);
        missionStarted_ = true;
    }

    // Low battery triggers RTL back to the very first waypoint (treated as home)
    if (controller_.getState().battery <= kLowBatteryThreshold &&
        controller_.getState().mode != FlightMode::RTL) {
        controller_.setTarget(waypoints_.front());
        controller_.getState(); // state is const; mode change happens in controller
        }

    controller_.update(dt);

    // Advance to next waypoint once we've arrived
    if (controller_.hasReachedTarget() && currentIndex_ < waypoints_.size() - 1) {
        currentIndex_++;
        controller_.setTarget(waypoints_[currentIndex_]);
    }
}

bool MissionManager::isMissionComplete() const {
    if (waypoints_.empty()) {
        return true;
    }
    return currentIndex_ == waypoints_.size() - 1 && controller_.hasReachedTarget();
}

size_t MissionManager::currentWaypointIndex() const {
    return currentIndex_;
}