#include "global.hpp"
#include "lemlib/api.hpp"
#include "autons.hpp"  
#include "driver_profile.hpp"

/** Define Variables  */
int current_profile_selection = 0; // Currently selected profile index
std::vector<ProfileOption> profile_list = {
    {"Default", default_profile_init, default_profile_loop},
    {"Calvin", calvin_profile_init, calvin_profile_loop},
    {"IDK", unknown_profile_init, unknown_profile_loop}
};

int current_auton_selection = 0;// Currently selected auton index

std::vector<AutonOption> auton_list = {
    {"Left Auton", auton_left},
    {"Right Auton", auton_right},
    {"Skills", auton_skills}
};
int autonColor = 1; // 1 is blue by defualt  -1 is red

// Define variables 

// Defined VEX Main Master Controller
pros::Controller masterController(pros::E_CONTROLLER_MASTER);

// Define VEX Motors

// Define VEX Motor Groups
pros::MotorGroup left_motor_group({-7,8,9,10}, pros::MotorGearset::blue); // left motors use 600 RPM cartrifges
pros::MotorGroup right_motor_group({1,-2,-3,-4}, pros::MotorGearset::blue); // right motors use 600 RPM cartridges
pros::MotorGroup intake_group({17, 18, -19, -20}, pros::MotorGearset::blue); // four intake motors run together with blue cartridges (flip signs if wiring requires reversal)

// Define Pneumatics
pros::adi::Pneumatics pneumatic_group({'A'}, false);

// Define VEX Sensors
pros::Imu imu(17); 
pros::Distance distance(16);
pros::Rotation horizontal_encoder(20); // horizontal tracking wheel Rotation sensor
pros::Rotation vertical_encoder(21); // vertical tracking wheel Rotation sensor

// Define LebLib 
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.75); // horizontal tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5); // vertical tracking wheel
lemlib::ControllerSettings angular_controller(
    0, 0, 0,   // kP, kI, kD
    0,         // antiWindup
    0, 0,      // small error range & timeout
    0, 0,      // large error range & timeout
    0          // max slew
);

lemlib::ControllerSettings lateral_controller(
    0, 0, 0,   // kP, kI, kD
    0,         // antiWindup
    0, 0,      // small error range & timeout
    0, 0,      // large error range & timeout
    0          // max slew
);

// Odometry settings
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// Drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              360, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

// Create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);
