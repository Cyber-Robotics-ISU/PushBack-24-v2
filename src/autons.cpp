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
    extender.toggle();
    pros::delay(150);
    chassis.moveToPose(0,33.5,-90, 2000);
    chassis.waitUntilDone();
    intake.move(kIntakeSpeed);
    lemlib::Pose pose = chassis.getPose();
    chassis.moveToPoint(
        pose.x-13,        // new X
        pose.y,    // keep current Y
        2500,
        {.maxSpeed=30}
    );
    pros::delay(2000);
    pose = chassis.getPose();
    chassis.moveToPoint(
        pose.x+3.5,        // new X
        pose.y,    // keep current Y
        500,
        {.forwards = false}       // timeout
    );
    pros::delay(1000);
    pose = chassis.getPose();
    chassis.moveToPoint(
        pose.x-5.5,        // new X
        pose.y,    // keep current Y
        500,
        {.forwards = false}       // timeout
    );
    pros::delay(1000);
    pose = chassis.getPose();
    chassis.moveToPoint(
        pose.x+3.5,        // new X
        pose.y,    // keep current Y
        500,
        {.forwards = false}       // timeout
    );

    pros::delay(1000);
    pose = chassis.getPose();
    chassis.moveToPoint(
        pose.x+23,        // new X
        pose.y,    // keep current Y
        2000,
        {.forwards = false}       // timeout
    );
    chassis.waitUntilDone();
    blocker.toggle();
    pros::delay(1000);
    scorer.move_absolute(650, 40);
    pros::delay(2000);
    scorer.move_absolute(-650, 40);
    pros::delay(1500);
    blocker.toggle();
    pros::delay(1550);

    // pose = chassis.getPose();
    // chassis.moveToPoint(
    //     pose.x-26.5,        // new X
    //     pose.y,    // keep current Y
    //     3000
    // );
    // chassis.waitUntilDone();
    // pose = chassis.getPose();
    // chassis.moveToPoint(
    //     pose.x-4.5,        // new X
    //     pose.y,    // keep current Y
    //     250,
    //     {.forwards = false}       // timeout
    // );
    // pose = chassis.getPose();
    // chassis.moveToPoint(
    //     pose.x+3.5,        // new X
    //     pose.y,    // keep current Y
    //     250,
    //     {.forwards = false}       // timeout
    // );
    // pros::delay(1000);
    // pose = chassis.getPose();
    // chassis.moveToPoint(
    //     pose.x-6.5,        // new X
    //     pose.y,    // keep current Y
    //     500,
    //     {.forwards = false}       // timeout
    // );
    // pros::delay(1000);
    // extender.toggle();
    // pros::delay(100);
    // blocker.toggle();
    // pros::delay(250);
    // scorer.move_absolute(750, 40);
    // pros::delay(150);
    // scorer.move_absolute(-750, 40);
    // blocker.toggle();
    // pros::delay(250);

    // pros::delay(4000);
    // pose = chassis.getPose();
    // chassis.moveToPoint(
    //     pose.x+7,        // new X
    //     pose.y,    // keep current Y
    //     500,
    //     {.forwards = false}       // timeout
    // );
    // chassis.waitUntilDone();
    // chassis.moveToPose(42,0,-455, 3000);
    // pros::delay(100);
    // blocker.toggle();
    // pros::delay(250);
    // scorer.move_absolute(750, 40);
    // pros::delay(150);
    // scorer.move_absolute(-750, 40);
    // blocker.toggle();

    //fuck

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
    chassis.setPose(0, 0, 0); 
    scorer.move_absolute(650, 40);

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
