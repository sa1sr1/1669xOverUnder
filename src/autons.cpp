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
  chassis.pid_drive_constants_set(10, 0, 100);
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


  chassis.pid_drive_set(-24_in, 90);
  chassis.pid_wait();


  // lemChassis.setPose({0,0,0});
  // lemChassis.moveToPose(-24, 12, -90, 5000);
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

void skills_macro(){

  intake.move(-127);
  
  // chassis.pid_drive_set(-4, DRIVE_SPEED);
  // chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 40, 90);
  chassis.pid_wait();

  intake.move(0);
  
  slapper.move(127); // replace this with what practiced

  chassis.pid_drive_toggle(false);

  //delay for matchlaoding
  pros::delay(30000);

  // chassis.pid_swing_set(ez::RIGHT_SWING, 0, 90);
  // chassis.pid_wait();

  slapper.move(0); // replace this with what practiced
  chassis.pid_drive_toggle(true);
}


void prog_skills(){
  // fill out the movements for matchloading after this (could change depending on how setup)
  
  // chassis.pid_swing_set(ez::LEFT_SWING, -10, 90);
  // chassis.pid_wait();

  /*
  chassis.pid_swing_set(ez::RIGHT_SWING, 30, 90);
  chassis.pid_wait();

  chassis.pid_drive_set(-2_in, 110);
  chassis.pid_wait();
  
  chassis.pid_drive_toggle(false);

   slapper.move(127);
   pros::delay(15000);
   slapper.move(0);
  */
  intake.move(127);
  chassis.pid_swing_set(ez::LEFT_SWING, -30, 90);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 28, 90);
  chassis.pid_wait();

  chassis.pid_drive_set(-1.5_in, 90);

  intake.move(0);

  chassis.pid_drive_toggle(false);

  pros::delay(2000);

  lemChassis.setPose({0.4,-14,30}); // start at around 32 deg (have to measure)
  lemChassis.moveToPose(6, 0, 45, 4000);

  chassis.pid_drive_toggle(true);

  chassis.pid_turn_set(-135, 90);
  chassis.pid_wait();
  // lemChassis.turnTo(-24,0, 5000);
  chassis.pid_drive_toggle(false);

  lemChassis.moveToPose(35, 13.5, -90, 4000, {.forwards = false});
  
  wings.set(true);
  // chassis.pid_drive_set(-47_in, 110);
  // chassis.pid_wait();


  lemChassis.moveToPose(83.5, 13.5, -90, 5000, {.forwards = false});
  wings.set(false);

  lemChassis.moveToPose(74, 13.5, -90, 3000);

  chassis.pid_drive_toggle(true);

  chassis.pid_turn_set(0, 90);
  chassis.pid_wait();

  chassis.pid_drive_set(-3_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, -90, 90);
  chassis.pid_wait();

  chassis.pid_drive_set(-18_in, 110);
  chassis.pid_wait();
  
  chassis.pid_turn_set(-180, 90);
  chassis.pid_wait();





  // lemChassis.moveToPose(114, -5.1, 180, 7000, {.forwards = false});

  chassis.pid_drive_set(-60_in, 110);
  chassis.pid_wait();

  // chassis.pid_swing_set(ez::RIGHT_SWING, 225, 90);
  // chassis.pid_wait();

  // wings.set(false);




  // slapper.move(127); // or whatever matcloading speed
  // pros::delay(30000)
  // slapper.move(0);

  // movements after this are starting off on middle of left edge of tile on the left side of blue horiz elevation bar
  // all turns are assuming that the bot is initialized with intake pointing to elevation bar
  //    skills_macro();

  // chassis.pid_drive_set(72, DRIVE_SPEED);
  // chassis.pid_wait();
  //
  // chassis.pid_turn_set(-90, TURN_SPEED); // turn robot around so triballs can be pushed with back
  // chassis.pid_wait();
  //
  // chassis.pid_drive_set(-20, DRIVE_SPEED);
  // chassis.pid_wait();
  //
  // chassis.pid_turn_set(0, TURN_SPEED);
  // chassis.pid_wait();
  //
  // chassis.pid_drive_set(-15, DRIVE_SPEED);
  // chassis.pid_wait();
  //
  // chassis.pid_turn_set(-90, TURN_SPEED);
  // chassis.pid_wait();
  //
  // wings.set(true);
  //
  // chassis.pid_drive_set(-18, DRIVE_SPEED);
  // chassis.pid_wait();
  //
  // chassis.pid_swing_set(ez::LEFT_SWING, -180, 90);
  // chassis.pid_wait();
  //
  // chassis.pid_drive_set(-14, 127);
  // chassis.pid_wait();
  //
  //
  // chassis.pid_drive_set(20, DRIVE_SPEED);
  // chassis.pid_wait();
  // 
  // chassis.pid_swing_set(ez::LEFT_SWING, -90, 90);
  // chassis.pid_wait();
  //
  // chassis.pid_drive_set(-14, DRIVE_SPEED);
  // chassis.pid_wait();
  //
  // chassis.pid_swing_set(ez::LEFT_SWING, -180, 90);
  // chassis.pid_wait();
  //
  // chassis.pid_drive_set(-20, 12);
  // chassis.pid_wait();
}
///
// Drive Example
///
void far_side() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
  wings.set(true);

  chassis.pid_drive_set(-20_in, DRIVE_SPEED);
  chassis.pid_wait();
  

  chassis.pid_turn_set(-45, TURN_SPEED);
  chassis.pid_wait();

  wings.set(false);

  chassis.pid_drive_set(-15_in, 110); 
  chassis.pid_wait();
  
  chassis.pid_turn_set(-45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-15_in, 110);
  chassis.pid_wait();

  chassis.pid_turn_set(-45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(15_in, 90);
  chassis.pid_wait();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(18_in, 110);
  chassis.pid_wait();

  chassis.pid_turn_set(45, TURN_SPEED);
  chassis.pid_wait();

  intake.move(0);

  chassis.pid_drive_set(31_in, 90);
  chassis.pid_wait();

  // chassis.pid_drive_set(48, DRIVE_SPEED);
  // chassis.pid_wait();

  // chassis.pid_drive_set(-12, DRIVE_SPEED);
  // chassis.pid_wait();
  //
  // chassis.pid_drive_set(-12, DRIVE_SPEED);
  // chassis.pid_wait();
}



///
// Turn Example
///
void near_side() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at
  
  chassis.pid_drive_set(-40_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 90, TURN_SPEED);
  chassis.pid_wait();

  wings.set(true);

  chassis.pid_drive_set(-20_in, DRIVE_SPEED);
  chassis.pid_wait();

  
  /* chassis.pid_turn_set(90, TURN_SPEED); */
  /* chassis.pid_wait(); */
  /**/
  /* chassis.pid_drive_set(-12, DRIVE_SPEED); */
  /* chassis.pid_wait(); */
  /**/
  /* chassis.pid_drive_set(14, 110); */
  /* chassis.pid_wait(); */
  /**/
  /* chassis.pid_turn_set(90, TURN_SPEED); */
  /* chassis.pid_wait(); */
  /**/
  /* chassis.pid_drive_set(-11, DRIVE_SPEED); */
  /* chassis.pid_wait(); */
  /**/
  /* chassis.pid_turn_set(135, TURN_SPEED); */
  /* chassis.pid_wait(); */
  /**/
  /* chassis.pid_drive_set(-34, DRIVE_SPEED); */
  /* chassis.pid_wait(); */
  /**/
  /* chassis.pid_turn_set(180, TURN_SPEED); */
  /* chassis.pid_wait(); */
  /**/
  /* chassis.pid_drive_set(-30, DRIVE_SPEED); */
  /* chassis.pid_wait(); */

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
