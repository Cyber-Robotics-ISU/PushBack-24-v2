#include "driver_profile.hpp"
#include <vector>  
#include <string> 
#include <cmath>

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

void default_profile_init() {
    masterController.set_text(0,1, "test 0");
}

void default_profile_loop() {

    if ((masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))) { 
        togglenLowerIntake(-120, -1);  
    } else if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){ 
        togglenLowerIntake(120, 1);  
    }  

    if ((masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))) { 
        togglenUpperIntake(-120, -1);  
    } else if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){ 
        togglenUpperIntake(120, 1);  
    }

    static bool last_l1 = false;
    const bool l1 = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_X);
    if (l1 && !last_l1) {
        auton_right();
    }
    last_l1 = l1;

    if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
        scrapperPneumatics.toggle();
    }

    if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
        liftPneumatics.toggle();
    }

    if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
        hoodPneumatics.toggle();
    }

    int leftY = masterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = masterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    leftY = throttle_curve.curve(leftY);
    rightX    = steer_curve.curve(rightX);
    //chassis.arcade(leftY, rightX);
    //hold task

    chassis.arcade(leftY, rightX);
    //chassis.curvature(leftY, rightX);
    pros::delay(10);

}

void calvin_profile_init() {
   masterController.set_text(0,1, "test 1");
}

void calvin_profile_loop() {
   
}

void unknown_profile_init() {
    masterController.set_text(0,1, "test 2");
}

void unknown_profile_loop() {
    
}
