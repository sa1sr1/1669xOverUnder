#include "slapper.hpp"
#include <string>
#include "main.h"
#include "globals.hpp"
#include "pros/llemu.hpp"

bool slapperFire = false;
int power = 127;
void slapper_toggle(){
if(master.get_digital_new_press(DIGITAL_UP)) power = power + 10;
if(master.get_digital_new_press(DIGITAL_DOWN)) power = power - 10;

if(master.get_digital_new_press(DIGITAL_R2)) {
    slapperFire = !slapperFire;
    slapper.move(power*slapperFire);
}

    ez::screen_print("Voltage: "+to_string(power), 6);

}
