#include <gtest/gtest.h>
#include "Vec3.h"

TEST(Vec3Test, DefaultConstructor) {
    Vec3 v;
    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

TEST(Vec3Test, Addition) {
    Vec3 a(1.0, 2.0, 3.0);
    Vec3 b(4.0, 5.0, 6.0);
    Vec3 result = a + b;
    EXPECT_DOUBLE_EQ(result.x, 5.0);
    EXPECT_DOUBLE_EQ(result.y, 7.0);
    EXPECT_DOUBLE_EQ(result.z, 9.0);
}

TEST(Vec3Test, Subtraction) {
    Vec3 a(5.0, 5.0, 5.0);
    Vec3 b(2.0, 1.0, 4.0);
    Vec3 result = a - b;
    EXPECT_DOUBLE_EQ(result.x, 3.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
    EXPECT_DOUBLE_EQ(result.z, 1.0);
}

TEST(Vec3Test, ScalarMultiplication) {
    Vec3 a(1.0, 2.0, 3.0);
    Vec3 result = a * 2.0;
    EXPECT_DOUBLE_EQ(result.x, 2.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
    EXPECT_DOUBLE_EQ(result.z, 6.0);
}

TEST(Vec3Test, Magnitude) {
    Vec3 v(3.0, 4.0, 0.0);
    EXPECT_DOUBLE_EQ(v.magnitude(), 5.0); // 3-4-5 triangle
}

TEST(Vec3Test, Normalized) {
    Vec3 v(3.0, 4.0, 0.0);
    Vec3 n = v.normalized();
    EXPECT_NEAR(n.magnitude(), 1.0, 1e-9);
}

TEST(Vec3Test, NormalizedZeroVector) {
    Vec3 v(0.0, 0.0, 0.0);
    Vec3 n = v.normalized();
    EXPECT_DOUBLE_EQ(n.magnitude(), 0.0); // shouldn't divide by zero / NaN
}

TEST(Vec3Test, DistanceTo) {
    Vec3 a(0.0, 0.0, 0.0);
    Vec3 b(3.0, 4.0, 0.0);
    EXPECT_DOUBLE_EQ(a.distanceTo(b), 5.0);
}