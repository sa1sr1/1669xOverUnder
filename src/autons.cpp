#include "autons.hpp"
#include "EZ-Template/util.hpp"
#include "main.h"
#include "globals.hpp"
#include "pros/rtos.hpp"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.slew_drive_constants_set(7_in, 80);

  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(12.5, 0, 100);
  chassis.pid_turn_constants_set(3, 0.003, 20);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);
}

void one_mogo_constants() {
  // chassis.set_slew_min_power(80, 80);
  // chassis.set_slew_distance(7, 7);
  // chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  // chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  // chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  // chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  // chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  // chassis.set_slew_min_power(80, 80);
  // chassis.set_slew_distance(7, 7);
  // chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  // chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  // chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  // chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  // chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void modified_exit_condition() {
  // chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  // chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  // chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void drive_and_turn() {
  slapper.move(107);

  pros::delay(7000);

  slapper.move(0);
}

void keep_turn(int turn){
  pros::delay(5000);
  slapper.move(0);
  chassis.pid_swing_set(ez::RIGHT_SWING, turn, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(-2_in, DRIVE_SPEED);
  chassis.pid_wait();
  slapper.move(127);
  
}

void brake(int time){
  chassis.left_motors[0].brake();
  chassis.left_motors[1].brake();
  chassis.left_motors[2].brake();

  chassis.right_motors[0].brake();
  chassis.right_motors[1].brake();
  chassis.right_motors[2].brake();

  pros::delay(time);

}

void far_side() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
  intake.move(127);

  // wingRight.set(true);

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  // wingRight.set(false);


chassis.pid_drive_set(-3_in, DRIVE_SPEED);
chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, -45, 90, 15);
  chassis.pid_wait();


  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 74, 90, 20);
  chassis.pid_wait();

  intake.move(127);

chassis.pid_drive_set(38.5_in, DRIVE_SPEED);
chassis.pid_wait();

chassis.pid_turn_set(-16, 90);
chassis.pid_wait();

  // wingLeft.set(true);

  chassis.pid_swing_set(ez::RIGHT_SWING, 45, 90, 10);
  chassis.pid_wait();

chassis.pid_drive_set(-24_in, DRIVE_SPEED);
chassis.pid_wait();

chassis.pid_drive_set(12_in, DRIVE_SPEED);
chassis.pid_wait();

chassis.pid_turn_set(-135, 90);
chassis.pid_wait();

chassis.pid_drive_set(16_in, DRIVE_SPEED);
chassis.pid_wait();



  chassis.pid_turn_set(205, 90);
  chassis.pid_wait();

chassis.pid_drive_set(30_in, DRIVE_SPEED);
chassis.pid_wait();



}



///
// Turn Example
///
void near_side() {

  chassis.pid_drive_set(-40_in, DRIVE_SPEED);
  chassis.pid_wait();

  // wingLeft.set(true);
  // wingRight.set(true);

  chassis.pid_swing_set(ez::RIGHT_SWING, 90, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-20_in, DRIVE_SPEED);
  chassis.pid_wait();

  // wingLeft.set(false);
  // wingRight.set(false);

}
///
// Combining Turn + Drive
///



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.pid_drive_set(24, DRIVE_SPEED, true);
  chassis.pid_wait_until(6);
  chassis.pid_speed_max_set(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.pid_wait();

  chassis.pid_turn_set(45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.pid_drive_set(-24, DRIVE_SPEED, true);
  chassis.pid_wait_until(-6);
  chassis.pid_speed_max_set(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.pid_wait();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24, DRIVE_SPEED, true);
  chassis.pid_wait();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.pid_drive_set(24, DRIVE_SPEED, true);
 chassis.pid_wait();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.pid_turn_set(90, TURN_SPEED);
 chassis.pid_wait();
}



// . . .
// Make your own autonomous functions here!
// . . .
