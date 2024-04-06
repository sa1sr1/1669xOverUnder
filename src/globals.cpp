#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"

pros::Motor intake(4);
ez::Piston wingLeft (4);
ez::Piston wingRight (2);
ez::Piston ratchet (1);

pros::Motor slapper(18);
pros::Motor hang(11);
