#ifndef __MOTORS__
#define __MOTORS__

#include "main.h"

#define FRONT_LEFT_MOTOR 1
#define FRONT_RIGHT_MOTOR 11
#define BACK_LEFT_MOTOR 10
#define BACK_RIGHT_MOTOR 20

pros::Motor front_right(FRONT_RIGHT_MOTOR);
pros::Motor front_left(FRONT_LEFT_MOTOR, true);
pros::Motor back_right(BACK_RIGHT_MOTOR);
pros::Motor back_left(BACK_LEFT_MOTOR, true);

#endif