#pragma once
#include "api.h"
#include "lemlib/api.hpp"
#include "autons.hpp"  
#include "driver_profile.hpp"
#include "pid.hpp"

/** Define global variables and objects here */
struct ProfileOption { // profile option struct
    const char* name;
    void (*func)();
};
extern int current_profile_selection; // current profile selection
extern std::vector<ProfileOption> profile_list;

struct AutonOption { // Auton Option struct
    const char* name;
    void (*func)();
};
extern int autonColor;
extern int current_auton_selection; // Current auton selection
extern std::vector<AutonOption> auton_list;

// Define global variables and objects here
extern pros::Controller masterController;

// Define VEX Motors

// Define VEX Motor Groups
extern pros::MotorGroup left_motor_group;
extern pros::MotorGroup right_motor_group;

// Define VEX Sensors
extern pros::Imu imu;
extern pros::Rotation horizontal_encoder;
extern pros::Rotation vertical_encoder;

// Define LebLib
extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::TrackingWheel vertical_tracking_wheel;
extern lemlib::ControllerSettings empty_controller;
extern lemlib::OdomSensors sensors;
extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis chassis;