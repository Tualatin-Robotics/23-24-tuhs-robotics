#ifndef __MOTORS__
#define __MOTORS__

#include "main.h"

float const MOVE_TOTAL = 12000;
float const MOVE_VOLT = MOVE_TOTAL / 128;

#define FRONT_LEFT_MOTOR 1
#define FRONT_RIGHT_MOTOR 10
#define BACK_LEFT_MOTOR 11
#define BACK_RIGHT_MOTOR 20

#define MIDDLE_RIGHT_MOTOR 15
#define MIDDLE_LEFT_MOTOR 5

#define ACORN_GRAB_LEFT_MOTOR 9
#define ACORN_GRAB_RIGHT_MOTOR 2

pros::Motor front_right(FRONT_RIGHT_MOTOR);
pros::Motor front_left(FRONT_LEFT_MOTOR);
pros::Motor back_right(BACK_RIGHT_MOTOR);
pros::Motor back_left(BACK_LEFT_MOTOR);
pros::Motor middle_left(MIDDLE_LEFT_MOTOR);
pros::Motor middle_right(MIDDLE_RIGHT_MOTOR);

pros::Motor acorn_grab_left(ACORN_GRAB_LEFT_MOTOR);
pros::Motor acorn_grab_right(ACORN_GRAB_RIGHT_MOTOR);

#endif