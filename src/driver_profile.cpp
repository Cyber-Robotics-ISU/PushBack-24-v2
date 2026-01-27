#include "driver_profile.hpp"
#include <vector>  
#include <string> 
#include <cmath>

#include "liblvgl/lvgl.h"
#include "api.h"

#include "global.hpp"

void default_profile_init() {
    masterController.set_text(0,1, "test 0");
}

void default_profile_loop() {
    
    if(masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
        belt_move(127);
    }else if(masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
        belt_move(-127);
    }else{
        belt_move(0);
    }

    static bool last_l1 = false;
    const bool l1 = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    if (l1 && !last_l1) {
        auton_right();
    }
    last_l1 = l1;

    if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        pneumatic_group.toggle();
    }

    int leftY = masterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = masterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    chassis.arcade(leftY, rightX);

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
