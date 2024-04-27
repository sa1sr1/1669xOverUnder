#include "globals.hpp"
bool ratchet_toggle = false;
void move_hang(){

if (master.get_digital(DIGITAL_R2)) hang.move(-127);
else if (master.get_digital(DIGITAL_X)) hang.move(127);
else hang.move(0);

if (master.get_digital_new_press(DIGITAL_Y)) ratchet_toggle = !ratchet_toggle;

ratchet.set(ratchet_toggle);

  
}
