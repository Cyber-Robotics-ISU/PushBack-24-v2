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
    chassis.turnToHeading(90, 4000, {.maxSpeed = 127}, true);
}

void red_side() {
    chassis.setPose(0, 0, 0);
    constexpr int kIntakeSpeed = 127;
    scrapper.toggle();
    pros::delay(250);
    extender.toggle();
    pros::delay(250);
    extender.toggle();
    pros::delay(250);
    scrapper.toggle();
    pros::delay(250);
    chassis.moveToPose(0,34.5,-90, 3000);
    chassis.waitUntilDone();
    scrapper.toggle();
    chassis.waitUntilDone();
    intake.move(kIntakeSpeed);
    pros::delay(1000);
    chassis.moveToPose(-13.5, 29, -90, 2000);
    pros::delay(3000);
    lemlib::Pose pose = chassis.getPose();
    chassis.moveToPoint(
        pose.x+23,        // new X
        pose.y,    // keep current Y
        3000,
        {.forwards = false}       // timeout
    );
    chassis.waitUntilDone();
    pros::delay(250);
    extender.toggle();
    pros::delay(250);
    scrapper.toggle();
    scorer.move_absolute(650, 40);
    // pose = chassis.getPose();
    // chassis.waitUntilDone();
    // //added on
    // pros::delay(250);
    // lemlib::Pose pose = chassis.getPose();
    // chassis.moveToPoint(
    //     10,        // new X
    //     pose.y,    // keep current Y
    //     4000       // timeout
    // );
    // chassis.waitUntilDone();
    // scrapper.toggle();
    // extender.toggle();
    // chassis.moveToPose(
    //     -32,        // new X
    //     pose.y+2.5,    // keep current Y
    //     -90,
    //     4000       // timeout
    // );
    // chassis.waitUntilDone();
    // pros::delay(1000);
    // intake.move(0);
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
