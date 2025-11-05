#pragma once
#include "api.h"
#include "lemlib/api.hpp"


// Define global variables and objects here
extern pros::Controller masterController;
const extern int MAX_SPEED = 127;
const extern int MOTOR_OFF = 0;

// Define VEX Motors

// Define VEX Motor Groups
extern pros::MotorGroup left_motor_group;
extern pros::MotorGroup right_motor_group;
extern pros::MotorGroup intake_motor_group;
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