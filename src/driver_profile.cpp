#include "driver_profile.hpp"
#include <vector>  
#include <string> 
#include <cmath>

#include "liblvgl/lvgl.h"
#include "api.h"

#include "global.hpp"

void default_profile_init() {
    masterController.set_text(0, 1, "Default");
    driver_controls_init();
}

void default_profile_loop() {
    if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        red_side();
    }
    driver_controls_update();


    int leftY = masterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = masterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    leftY = throttle_curve.curve(leftY);
    rightX = steer_curve.curve(rightX);

    chassis.arcade(leftY, rightX);
}

void testing_profile_init() {
    driver_controls_init();
}

void testing_profile_loop() {
    if (masterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        red_side();
    }
    driver_controls_update();


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
