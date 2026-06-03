#include <gtest/gtest.h>
#include "UAVState.h"

// UAVState initializes with safe default values
TEST(UAVStateTest, DefaultInitialization) {
    UAVState uav;
    EXPECT_DOUBLE_EQ(uav.x, 0.0);
    EXPECT_DOUBLE_EQ(uav.y, 0.0);
    EXPECT_DOUBLE_EQ(uav.z, 0.0);
    EXPECT_DOUBLE_EQ(uav.battery, 100.0);
    EXPECT_EQ(uav.mode, FlightMode::IDLE);
}

// Battery can be drained and clamped manually
TEST(UAVStateTest, BatteryDrain) {
    UAVState uav;
    uav.battery -= 40.0;
    EXPECT_DOUBLE_EQ(uav.battery, 60.0);
}

// FlightMode string conversion works for all modes
TEST(UAVStateTest, FlightModeToString) {
    EXPECT_EQ(flightModeToString(FlightMode::IDLE),       "IDLE");
    EXPECT_EQ(flightModeToString(FlightMode::NAVIGATING), "NAVIGATING");
    EXPECT_EQ(flightModeToString(FlightMode::HOVERING),   "HOVERING");
    EXPECT_EQ(flightModeToString(FlightMode::RTL),        "RTL");
    EXPECT_EQ(flightModeToString(FlightMode::LANDED),     "LANDED");
}