#ifndef __MOTORS__
#define __MOTORS__

#include "main.h"

float const MOVE_VOLT = 12000 / 128;

#define FRONT_LEFT_MOTOR 1
#define FRONT_RIGHT_MOTOR 10
#define BACK_LEFT_MOTOR 11
#define BACK_RIGHT_MOTOR 20

#define ACORN_GRAB_LEFT_MOTOR 19
#define ACORN_GRAB_RIGHT_MOTOR 12

pros::Motor front_right(FRONT_RIGHT_MOTOR);
pros::Motor front_left(FRONT_LEFT_MOTOR);
pros::Motor back_right(BACK_RIGHT_MOTOR);
pros::Motor back_left(BACK_LEFT_MOTOR);

pros::Motor acorn_grab_left(ACORN_GRAB_LEFT_MOTOR);
pros::Motor acorn_grab_right(ACORN_GRAB_RIGHT_MOTOR);

#endif