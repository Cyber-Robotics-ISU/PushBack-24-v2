#include "driver_profile.hpp"
#include <vector>  
#include <string> 
#include <cmath>

#include "liblvgl/lvgl.h"
#include "api.h"

#include "global.hpp"

void default_profile_init() {
    masterController.set_text(0, 1, "Default");
    startSubsystemTask(); 
}

void default_profile_loop() {
    if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        toggleScrapper();
    }
    if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        toggleLift();
    }

    if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        test_auton_straight();
    }

    bool shift = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    bool r2 = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
    bool r1 = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    bool down = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
    bool b = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_B);

    // Determine Mode (Priority Logic)
    // The order of these if/else statements determines priority.
    // Last checked wins, or first checked wins depending on structure.
    // Here we use if-else if to ensure only ONE mode is sent.
    
    RobotMode desiredMode = RobotMode::IDLE;

    if (r1) {
        desiredMode = RobotMode::FULL_FIRE;
    } 
    else if (shift && b) {
        desiredMode = RobotMode::OUTTAKE_LOWER;
    }
    else if (b) {
        desiredMode = RobotMode::INTAKE_LOWER;
    }
    else if (shift && down) {
        desiredMode = RobotMode::UNJAM_UPPER;
    }
    else if (down) {
        desiredMode = RobotMode::SHOOT_PREP;
    }
    else if (shift && r2) {
        desiredMode = RobotMode::OUTTAKE_ALL;
    }
    else if (r2) {
        desiredMode = RobotMode::INTAKE_INDEX;
    }

    setRobotMode(desiredMode);


    int leftY = masterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = masterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    leftY = throttle_curve.curve(leftY);
    rightX = steer_curve.curve(rightX);

    chassis.arcade(leftY, rightX);
}

void testing_profile_init() {
}

void testing_profile_loop() {
    if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        toggleScrapper();
    }
    if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        toggleLift();
    }
    if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        test_auton_straight();
    }

    bool shift = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    bool r2 = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
    bool r1 = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    bool down = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
    bool b = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_B);

    // Determine Mode (Priority Logic)
    // The order of these if/else statements determines priority.
    // Last checked wins, or first checked wins depending on structure.
    // Here we use if-else if to ensure only ONE mode is sent.
    
    RobotMode desiredMode = RobotMode::IDLE;

    if (r1) {
        desiredMode = RobotMode::FULL_FIRE;
    } 
    else if (shift && b) {
        desiredMode = RobotMode::OUTTAKE_LOWER;
    }
    else if (b) {
        desiredMode = RobotMode::INTAKE_LOWER;
    }
    else if (shift && down) {
        desiredMode = RobotMode::UNJAM_UPPER;
    }
    else if (down) {
        desiredMode = RobotMode::SHOOT_PREP;
    }
    else if (shift && r2) {
        desiredMode = RobotMode::OUTTAKE_ALL;
    }
    else if (r2) {
        desiredMode = RobotMode::INTAKE_INDEX;
    }

    setRobotMode(desiredMode);


    int leftY = masterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = masterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    leftY = throttle_curve.curve(leftY);
    rightX = steer_curve.curve(rightX);

    chassis.arcade(leftY, rightX);
}

void calvin_profile_init() {
   masterController.set_text(0,1, "Calvin");
}

void calvin_profile_loop() {
   default_profile_loop();
}

void unknown_profile_init() {
    masterController.set_text(0,1, "test 2");
}

void unknown_profile_loop() {
    
}
