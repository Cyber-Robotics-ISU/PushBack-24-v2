#pragma once

#include <cmath>
#include <vector>
#include <string>

#include "liblvgl/lvgl.h"
#include "api.h"

#include "global.hpp"

// Define all the distinct behaviors your robot can be in
enum class RobotMode {
    IDLE,
    OUTTAKE_ALL,        // Shift + R2: Reverse intakes
    INTAKE_INDEX,       // R2: Intakes forward, Shooter off/slow
    UNJAM_UPPER,        // Shift + Down: Upper & Shooter reverse
    SHOOT_PREP,         // Down: Upper & Shooter forward
    OUTTAKE_LOWER,      // Shift + B: Lower reverse
    INTAKE_LOWER,       // B: Lower forward
    FULL_FIRE           // R1: Everything forward
};

// Global mode variable (extern so other files can see it if needed)
extern RobotMode currentRobotMode;

// Task management
void startSubsystemTask();
void stopSubsystemTask();

// Setters
void setRobotMode(RobotMode mode);

// Helper for pneumatics (since they are instant toggles, not continuous states)
void toggleScrapper();
void toggleLift();