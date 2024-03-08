#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"


void activate_wings(){
    if (master.get_digital_new_press(DIGITAL_R1)){ 
        wingLeft.set(!wingLeft.get());
        wingRight.set(!wingRight.get());
    }

    if (master.get_digital_new_press(DIGITAL_A)) wingLeft.set(!wingLeft.get());
    if (master.get_digital_new_press(DIGITAL_Y)) wingRight.set(!wingRight.get());
}
