#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"

bool intakeToggle = false;
int direction = 1;

void move_intake(){
if (master.get_digital_new_press(DIGITAL_L1)) intakeToggle = !intakeToggle;

if (master.get_digital(DIGITAL_L2)) direction = -1;
else direction = 1;

intake.move_velocity(600*direction*intakeToggle);
}

