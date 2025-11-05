#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

/**
 *  This toggle function is used for the intake motor to allow the driver to
 *  open or close a flap that is used to eject incorrect blocks 
 *  via the R1 button on the PROS controller. The function returns a boolean value 
 *  motorOn which represents the current state of the motor either on or off (1 or 0)
 *    
 */
bool ToggleButton(){
    // create a previous button state and motor state to compare with 
    // Initially the button is unpressed and the motor is off
    
    static bool last_Button_State = false; 
    static bool motorOn = false;
    bool current_Button_State = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    
    // checks if current state has changed from past state
    if(current_Button_State && !last_Button_State){  
        motorOn = !motorOn; // Change the current motor state 
    }
    last_Button_State = current_Button_State; // update last button state
    return motorOn; // Return the last motor state
}
/**
 *  This is a function used for the turn on the intake motor while the driver is holding button R2
 *  on the PROS controller. This motor is used to open or close a flap that eject incorrect blocks 
 */
void HoldButton(){
    bool button_R2 = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
    if(button_R2) {
        intake_motor_group.move(MAX_SPEED);
    }
    else{
        intake_motor_group.move(MOTOR_OFF);
    }
}

void opcontrol() {
	while (true) {	
        bool is_Motor_On = ToggleButton();
        bool R2_BUTTON_PRESSED = masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
        // If button R2 is pressed, use the HoldButton function to control the motor 
        if(R2_BUTTON_PRESSED){ 
            HoldButton();
        // Otherwise use the ToggleButton function to control the motor
        }else{
            // If motor is on, set motor to max speed otherwise the motor is turned off
            intake_motor_group.move(is_Motor_On ? MAX_SPEED: MOTOR_OFF); 
        }     
        pros::delay(20);  // Run for 20 ms then update 
    }            
} // End of opcontrol 