#include <gtest/gtest.h>
#include "UAVController.h"

TEST(UAVControllerTest, StartsIdleAtOrigin) {
    UAVController controller;
    EXPECT_EQ(controller.getState().mode, FlightMode::IDLE);
    EXPECT_DOUBLE_EQ(controller.getState().position.x, 0.0);
}

TEST(UAVControllerTest, MovesTowardTarget) {
    UAVController controller;
    controller.setTarget(Vec3(10.0, 0.0, 0.0));
    controller.update(0.1);

    // Should have moved in the +x direction
    EXPECT_GT(controller.getState().position.x, 0.0);
    EXPECT_EQ(controller.getState().mode, FlightMode::NAVIGATING);
}

TEST(UAVControllerTest, ReachesTargetEventually) {
    UAVController controller;
    controller.setTarget(Vec3(1.0, 0.0, 0.0)); // close target

    // Run enough ticks that it should arrive
    for (int i = 0; i < 100; ++i) {
        controller.update(0.1);
    }

    EXPECT_TRUE(controller.hasReachedTarget());
    EXPECT_EQ(controller.getState().mode, FlightMode::HOVERING);
}

TEST(UAVControllerTest, BatteryDrainsOverTime) {
    UAVController controller;
    controller.setTarget(Vec3(100.0, 0.0, 0.0)); // far target, keeps moving
    controller.update(1.0);

    EXPECT_LT(controller.getState().battery, 100.0);
}

TEST(UAVControllerTest, BatteryNeverGoesNegative) {
    UAVController controller;
    controller.setTarget(Vec3(1000.0, 0.0, 0.0));
    for (int i = 0; i < 10000; ++i) {
        controller.update(1.0);
    }
    EXPECT_GE(controller.getState().battery, 0.0);
}