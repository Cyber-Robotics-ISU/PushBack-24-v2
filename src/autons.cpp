#include "autons.hpp"
#include "global.hpp"

#include "liblvgl/lvgl.h"
#include "api.h"

#include <vector>  
#include <string> 
#include <cmath>

// chassis.waitUntil(10); wait untill its moves like 10 inches after moveToPose
// chassis.waitUntil(45); wait untill it moves x amount of degrees after turn to heading
// waitUntilDone

// Actual autonomous implementations
void test_auton_straight() {
    // Reset pose so 12 inches forward is along +Y
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 24, 10000, {.maxSpeed = 120}, true);
}

void test_auton_turn() {
    // Turn 90 degrees to the right from current heading
    chassis.setPose(0, 0, 0);
    chassis.turnToHeading(90, 100000, {.maxSpeed = 125}, false);
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

void exampleAuton() {
    chassis.setPose(0, 0, 0); 
    chassis.moveToPoint(0, 36, 4000, {.maxSpeed = 125});
    chassis.waitUntilDone();

    // 2. Turn Left 90 Deg
    chassis.turnToHeading(-90, 1000, {.maxSpeed = 120});
    chassis.waitUntilDone();

    // 3. Drive Forward 12"
    chassis.moveToPose(-12, 36, -90, 2000, {.maxSpeed = 120});
    chassis.waitUntilDone();

    // 4. Drive Backward 24"
    chassis.moveToPose(12, 36, -90, 3000, {.forwards = false, .maxSpeed = 120});
    chassis.waitUntilDone();

    // 5. Turn 180 Deg
    chassis.turnToHeading(90, 1000, {.maxSpeed = 120});
    chassis.waitUntilDone();
}