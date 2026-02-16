#include "autons.hpp"
#include "global.hpp"

#include "liblvgl/lvgl.h"
#include "api.h"

#include <vector>  
#include <string> 
#include <cmath>

// Actual autonomous implementations
void test_auton_straight() {
    // Reset pose so 12 inches forward is along +Y
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 12, 2000, {}, false);
}

void test_auton_turn() {
    // Turn 90 degrees to the right from current heading
    chassis.setPose(0, 0, 0);
    chassis.turnToHeading(90, 2000, {.maxSpeed = 100}, false);
}

void red_side() {
    startSubsystemTask();
    
    chassis.setPose(0, 0, 0);

    setRobotMode(RobotMode::INTAKE_INDEX);
    
    chassis.moveToPoint(0, 24, 2000);
    chassis.waitUntilDone();

    setRobotMode(RobotMode::IDLE);


    chassis.turnToHeading(90, 1000);
    chassis.waitUntilDone();

    setRobotMode(RobotMode::FULL_FIRE);
    
    pros::delay(1000);
    
    setRobotMode(RobotMode::IDLE);


    toggleScrapper();
    
    chassis.moveToPoint(0, 10, 2000, {.forwards = false});
    chassis.waitUntilDone();
    
    toggleScrapper();
}

void blue_side(){
    
}

void auton_skills() {

}
