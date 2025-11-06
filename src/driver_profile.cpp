#include "driver_profile.hpp"
#include <vector>  
#include <string> 
#include <cmath>

#include "liblvgl/lvgl.h"
#include "api.h"

#include "global.hpp"

void testOptical(){
  pros::c::optical_rgb_s_t rgb_value;
    rgb_value = optical_sensor.get_rgb();
    if (rgb_value.blue > rgb_value.green && rgb_value.blue > rgb_value.red){
        masterController.clear_line(0);
        pros::delay(100);
        masterController.set_text(0, 1, "blue");
    } else if(rgb_value.green > rgb_value.blue && rgb_value.green > rgb_value.red){
        masterController.clear_line(0);
        pros::delay(100);
        masterController.set_text(0, 1, "green");
    } else if (rgb_value.red > rgb_value.blue && rgb_value.red > rgb_value.green){
        masterController.clear_line(0);
        pros::delay(100);
        masterController.set_text(0, 1, "red");
    }
    pros::delay(20);
  
}

void default_profile_init() {
    masterController.clear();
}

void default_profile_loop() {
    int leftY = masterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightY = masterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    chassis.tank(leftY, rightY);
    testOptical();
}

void calvin_profile_init() {
   
}

void calvin_profile_loop() {
   
}

void unknown_profile_init() {
    
}

void unknown_profile_loop() {
    
}