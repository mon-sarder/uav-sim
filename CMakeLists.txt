cmake_minimum_required(VERSION 3.20)
project(uav_sim VERSION 0.1.0 LANGUAGES CXX)

# ── C++ standard ──────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Google Test (fetched automatically) ───────────────────────
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ── Core library ──────────────────────────────────────────────
# All reusable sim logic goes here. Both the main executable
# and the test executable link against this.
add_library(uav_core STATIC
        src/UAVState.cpp
)
target_include_directories(uav_core PUBLIC include)

# ── Main executable ───────────────────────────────────────────
add_executable(uav_main
        src/main.cpp
)
target_link_libraries(uav_main PRIVATE uav_core)

# ── Test executable ───────────────────────────────────────────
enable_testing()
add_executable(uav_tests
        tests/test_UAVState.cpp
)
target_link_libraries(uav_tests PRIVATE uav_core GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(uav_tests)