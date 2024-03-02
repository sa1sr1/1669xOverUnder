#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"


void activate_wings(){
    if (master.get_digital_new_press(DIGITAL_R1)){ 
        wings.set(!wings.get());
    }

    if (master.get_digital_new_press(DIGITAL_A)) wings.set(!wings.get());
}
