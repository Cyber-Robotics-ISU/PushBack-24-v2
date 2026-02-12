#include "driver_profile.hpp"
#include <vector>  
#include <string> 
#include <cmath>

#include "autons.hpp"
#include "liblvgl/lvgl.h"
#include "api.h"

#include "global.hpp"

bool lowerIntakeToggle = false;
bool upperIntakeToggle = false;

void togglenLowerIntake(int velocity, int direction){
    if(!lowerIntakeToggle){
        intake_group_lower.move(velocity * direction);
        pros::delay(10);
        lowerIntakeToggle = true;
    } else {
        intake_group_lower.move(0);
        pros::delay(10);
        lowerIntakeToggle = false;
    }
}

void togglenUpperIntake(int velocity, int direction){
    if(!upperIntakeToggle){
        intake_group_upper.move(velocity * direction);
        pros::delay(10);
        upperIntakeToggle = true;
    } else {
        intake_group_upper.move(0);
        pros::delay(10);
        upperIntakeToggle = false;
    }
}

void intakeHold(pros::controller_digital_e_t in,
                pros::controller_digital_e_t out,
                pros::MotorGroup& intake,
                int speed = 125) {

    if (masterController.get_digital(in)){
        intake.move(-speed);
    } else if (masterController.get_digital(out)) {
        intake.move(speed);
    } else {
        intake.move(0);
    }
}



void default_profile_init() {
    masterController.set_text(0,1, "default");
}

void default_profile_loop() {

    /*if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
        scrapperPneumatics.toggle();
    }*/

    if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
        liftPneumatics.toggle();
    }
    if(masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        auton_right();
    }

    const bool shift = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    const bool r2 = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
    const bool r1 = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    const bool down = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
    const bool b = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_B);

    constexpr int kMaxSpeed = 127;
    constexpr int kShooterSlow = 0; // ~25% reverse for intake assist
    int lower_intake_cmd = 0;
    int upper_intake_cmd = 0;
    int shooter_cmd = 0;

    if (shift && r2) {
        lower_intake_cmd = -kMaxSpeed;
        upper_intake_cmd = -kMaxSpeed;
    } else if (r2) {
        lower_intake_cmd = kMaxSpeed;
        upper_intake_cmd = kMaxSpeed;
        shooter_cmd = kShooterSlow;
    }

    if (shift && down) {
        upper_intake_cmd = -kMaxSpeed;
        shooter_cmd = -kMaxSpeed;
    } else if (down) {
        upper_intake_cmd = kMaxSpeed;
        shooter_cmd = kMaxSpeed;
    }

    if (shift && b) {
        lower_intake_cmd = -kMaxSpeed;
    } else if (b) {
        lower_intake_cmd = kMaxSpeed;
    }

    if (r1) {
        shooter_cmd = kMaxSpeed;
        lower_intake_cmd = kMaxSpeed;
        upper_intake_cmd = kMaxSpeed;
    }

    intake_group_lower.move(lower_intake_cmd);
    intake_group_upper.move(upper_intake_cmd);
    shooter.move(shooter_cmd);

    int leftY = masterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = masterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    leftY = throttle_curve.curve(leftY);
    rightX = steer_curve.curve(rightX);
    //chassis.arcade(leftY, rightX);
    //hold task

    chassis.arcade(leftY, rightX);
    pros::delay(10);

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
