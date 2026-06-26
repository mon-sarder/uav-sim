#include <gtest/gtest.h>
#include "MissionManager.h"
#include "UAVController.h"

TEST(MissionManagerTest, StartsAtFirstWaypoint) {
    UAVController controller;
    std::vector<Vec3> waypoints = { Vec3(5, 0, 0), Vec3(10, 0, 0) };
    MissionManager mission(controller, waypoints);

    EXPECT_EQ(mission.currentWaypointIndex(), 0);
    EXPECT_FALSE(mission.isMissionComplete());
}

TEST(MissionManagerTest, AdvancesThroughWaypoints) {
    UAVController controller;
    std::vector<Vec3> waypoints = { Vec3(1, 0, 0), Vec3(2, 0, 0) };
    MissionManager mission(controller, waypoints);

    // Run enough ticks to reach both waypoints
    for (int i = 0; i < 200; ++i) {
        mission.update(0.1);
    }

    EXPECT_TRUE(mission.isMissionComplete());
    EXPECT_EQ(mission.currentWaypointIndex(), 1);
}

TEST(MissionManagerTest, EmptyWaypointListIsImmediatelyComplete) {
    UAVController controller;
    std::vector<Vec3> waypoints;
    MissionManager mission(controller, waypoints);

    EXPECT_TRUE(mission.isMissionComplete());
}