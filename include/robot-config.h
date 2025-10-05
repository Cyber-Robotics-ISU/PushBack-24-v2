#pragma once
#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/rotation.hpp"
#include "pros/vision.hpp"
#include "pros/llemu.hpp"
#include "pros/optical.hpp"
#include "pros/motor_group.hpp"

extern pros::Motor intake_leftmotor;
extern pros::Motor intake_rightmotor;
extern pros::MotorGroup intake;

// optical sensor
extern pros::Optical intake_optical;