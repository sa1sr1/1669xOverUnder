#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"

pros::Motor intake(4);
ez::Piston wings('C');
ez::Piston ratchet ('G');

pros::Motor slapper(18);
pros::Motor hang(6);
