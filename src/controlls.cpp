#include "controlls.hpp"
#include <vector>  
#include <string> 
#include <cmath>

// Initialize default mode
RobotMode currentRobotMode = RobotMode::IDLE;
pros::Task* subsystemTaskHandle = nullptr;

// ODOM TRACKING
lemlib::Pose globalPose(0, 0, 0);
pros::Task* odomTaskHandle = nullptr;
pros::Mutex odomMutex;

/**
 * Logic for the background task
 * continuously updates motor powers based on currentRobotMode
 */
void subsystemControlTaskFn(void* param) {
    while (true) {
        // Define speeds locally for easy tuning
        constexpr int kMaxSpeed = 127;
        
        switch (currentRobotMode) {
            case RobotMode::IDLE:
                intake_group_lower.move(0);
                intake_group_upper.move(0);
                shooter.move(0);
                break;

            case RobotMode::OUTTAKE_ALL: // Shift + R2
                intake_group_lower.move(-kMaxSpeed);
                intake_group_upper.move(-kMaxSpeed);
                shooter.move(0);
                break;

            case RobotMode::INTAKE_INDEX_SPIN_BACK: // R2
                intake_group_lower.move(kMaxSpeed);
                intake_group_upper.move(kMaxSpeed);
                shooter.move(-30); 
                break;

            case RobotMode::INTAKE_INDEX: // R2
                intake_group_lower.move(kMaxSpeed);
                intake_group_upper.move(kMaxSpeed);
                shooter.move(0); 
                break;

            case RobotMode::UNJAM_UPPER: // Shift + Down
                intake_group_lower.move(0); 
                intake_group_upper.move(-kMaxSpeed);
                shooter.move(-kMaxSpeed);
                break;

            case RobotMode::SHOOT_PREP: // Down
                intake_group_lower.move(0);
                intake_group_upper.move(kMaxSpeed);
                shooter.move(kMaxSpeed);
                break;

            case RobotMode::OUTTAKE_LOWER: // Shift + B
                intake_group_lower.move(-kMaxSpeed);
                intake_group_upper.move(0); 
                shooter.move(0);
                break;

            case RobotMode::INTAKE_LOWER: // B
                intake_group_lower.move(kMaxSpeed);
                intake_group_upper.move(0);
                shooter.move(0);
                break;
            case RobotMode::FULL_FIRE: // R1
                intake_group_lower.move(kMaxSpeed);
                intake_group_upper.move(kMaxSpeed);
                shooter.move(kMaxSpeed);
                break;
        }

        pros::delay(10); 
    }
}

lemlib::Pose getGlobalPose() {
    odomMutex.take();
    lemlib::Pose copy = globalPose;
    odomMutex.give();
    return copy;
}

void odomTrackerTaskFn(void* param) {
    while (true) {
        odomMutex.take();
        globalPose = chassis.getPose();
        odomMutex.give();

        pros::delay(10); // 10ms update rate
    }
}

void setRobotMode(RobotMode mode) {
    currentRobotMode = mode;
}

void toggleScrapper() {
    scrapperPneumatics.toggle();
}

void toggleLift() {
    liftPneumatics.toggle();
}

void toggleDeScore(){
    deScorePneumatics.toggle();
}

// Task Management
void startSubsystemTask() {
    if (subsystemTaskHandle == nullptr) {
        subsystemTaskHandle = new pros::Task(subsystemControlTaskFn);
    }
}

void stopSubsystemTask() {
    if (subsystemTaskHandle != nullptr) {
        subsystemTaskHandle->remove();
        delete subsystemTaskHandle;
        subsystemTaskHandle = nullptr;
    }
}


void startOdomTask() {
    if (odomTaskHandle == nullptr) {
        odomTaskHandle = new pros::Task(odomTrackerTaskFn);
    }
}

void stopOdomTask() {
    if (odomTaskHandle != nullptr) {
        odomTaskHandle->remove();
        delete odomTaskHandle;
        odomTaskHandle = nullptr;
    }
}