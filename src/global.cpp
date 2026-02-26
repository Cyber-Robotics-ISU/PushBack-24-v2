#include "global.hpp"


/** Define Variables  */
int current_profile_selection = 0; // Currently selected profile index
std::vector<ProfileOption> profile_list = {
    {"Default", default_profile_init, default_profile_loop, "Basic default driving profile"},
    {"IDK", unknown_profile_init, unknown_profile_loop, "Experimental profile"}
};

// -1 = red, 1 = blue
int autonColor = 1; // default blue

int current_auton_selection = 0;

// ALL autons stored here
std::vector<AutonOption> auton_master_list = {
    { "Red Side",
        "loads and color shorts",
        test_auton_turn,
      0 }, // red
     { "Blue Side",
        "loads and color shorts",
        test_auton_turn,
      1 }, // blue
    { "EXAMPLE",
      "1234567890123456789\n1234567890123456789\n1234567890123456789\n1234567890123456789\n1234567890123456789",
      test_auton_turn,
      2 }, // blue

    { "RED",
      "Rush the middle mogo. Scores 2 rings.\nFast and consistent.",
      test_auton_turn,
      0 }, // red

    { "BLUE",
      "Blue version of Mogo Rush.\nScores 2 rings.",
      test_auton_turn,
      1 }, // blue

    { "Left Skills Auton",
      "Runs full skills path.\nLeft Side",
      test_auton_straight,
      2 },
      
      { "Right Skills Auton",
      "Runs full skills path.\nRight Side",
      test_auton_straight,
      2 },// both
};
std::vector<AutonOption> auton_list;

// Define variables 

// Defined VEX Main Master Controller
pros::Controller masterController(pros::E_CONTROLLER_MASTER);

// Define VEX Motors

// Define VEX Motor Groups
pros::MotorGroup left_motor_group({-9,8,6,7}, pros::MotorGearset::blue); // left motors use 600 RPM cartrifges
pros::MotorGroup right_motor_group({1,-2,-3,-4}, pros::MotorGearset::blue); // right motors use 600 RPM cartridges
pros::MotorGroup intake_group_lower({-11,20}, pros::MotorGearset::blue); // four intake motors run together with blue cartridges (flip signs if wiring requires reversal)
pros::MotorGroup intake_group_upper({-16}, pros::MotorGearset::blue);
pros::MotorGroup shooter({17}, pros::MotorGearset::blue);
// Define Pneumatics
pros::adi::Pneumatics scrapperPneumatics({'A'}, false);
pros::adi::Pneumatics liftPneumatics({'B'}, false);
pros::adi::Pneumatics hoodPneumatics({'C'}, false);

// Define VEX Sensors
pros::Imu imu(15); 
// pros::Distance distance(16);
pros::Rotation horizontal_encoder(19); // horizontal tracking wheel Rotation sensor
pros::Rotation vertical_encoder(18); // vertical tracking wheel Rotation sensor

lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// Define LebLib 
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, -4); // distance needs to be changed
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, 0); // distance needs to be changed
lemlib::ControllerSettings angular_controller(
    12, 0.0, 0.65,   // kP, kI, kD
    0,         // antiWindup
    0, 0,      // small error range & timeout
    0, 0,      // large error range & timeout
    0          // max slew
);

lemlib::ControllerSettings lateral_controller(
    16, 0.0, 21,   // kP, kI, kD 8.95
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
                              11, // 10 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 4" omnis
                              600, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

// Create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);
