#ifndef __MOTORS__
#define __MOTORS__

#include "main.h"

float const MOVE_TOTAL = 12000;
float const MOVE_VOLT = MOVE_TOTAL / 128;

#define FRONT_LEFT_MOTOR 11
#define FRONT_RIGHT_MOTOR 12
#define BACK_LEFT_MOTOR 13
#define BACK_RIGHT_MOTOR 14

#define MIDDLE_RIGHT_MOTOR 15
#define MIDDLE_LEFT_MOTOR 16

#define ACORN_GRAB_LEFT_MOTOR 17
#define ACORN_GRAB_RIGHT_MOTOR 18

#define WING_LEFT 'A'
#define WING_RIGHT 'B'

#define CATAPULT_MOTOR 10

#define ENDGAME_MOTOR 19

pros::Motor front_right(FRONT_RIGHT_MOTOR);
pros::Motor front_left(FRONT_LEFT_MOTOR);
pros::Motor back_right(BACK_RIGHT_MOTOR);
pros::Motor back_left(BACK_LEFT_MOTOR);
pros::Motor middle_left(MIDDLE_LEFT_MOTOR);
pros::Motor middle_right(MIDDLE_RIGHT_MOTOR);

pros::Motor acorn_grab_left(ACORN_GRAB_LEFT_MOTOR);
pros::Motor acorn_grab_right(ACORN_GRAB_RIGHT_MOTOR);

pros::Motor catapult(CATAPULT_MOTOR);

pros::Motor endgame_motor(ENDGAME_MOTOR);

#endif