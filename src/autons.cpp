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
    chassis.moveToPose(
    0, // x = 0
    24, // y = 0
    0, // theta = 0
    4000, // timeout of 4000ms
    {.lead = 0.3}
);
    //chassis.moveToPoint(0, 36, 4000, {.maxSpeed = 120}, true);
}

void test_auton_turn() {
    // Turn 90 degrees to the right from current heading
    chassis.setPose(0, 0, 0);
    chassis.turnToHeading(90, 4000, {.maxSpeed = 125}, true);
}

void red_side() {
    startSubsystemTask();
    chassis.setPose(0, 0, 0);
    chassis.moveToPose(0,35,90, 4000);
    chassis.waitUntilDone();
    scrapperPneumatics.toggle();
    setRobotMode(RobotMode::INTAKE_LOWER);
    chassis.moveToPose(29, 23, 90, 4000);
    chassis.waitUntilDone();
    //added on
    pros::delay(250);
    lemlib::Pose pose = chassis.getPose();
    chassis.moveToPoint(
        10,        // new X
        pose.y,    // keep current Y
        4000       // timeout
    );
    chassis.waitUntilDone();
    scrapperPneumatics.toggle();
    hoodPneumatics.toggle();
    chassis.moveToPose(
        -32,        // new X
        pose.y+2.5,    // keep current Y
        -90,
        4000       // timeout
    );
    chassis.waitUntilDone();
    setRobotMode(RobotMode::FULL_FIRE);
    pros::delay(1000);
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