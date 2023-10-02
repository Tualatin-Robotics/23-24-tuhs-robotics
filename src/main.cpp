#include "main.h"

#define FRONT_LEFT_MOTOR 1
#define FRONT_RIGHT_MOTOR 2
#define BACK_LEFT_MOTOR 3
#define BACK_RIGHT_MOTOR 4

pros::Motor front_right(FRONT_RIGHT_MOTOR);
pros::Motor front_left(FRONT_LEFT_MOTOR, true);
pros::Motor back_right(BACK_RIGHT_MOTOR);
pros::Motor back_left(BACK_LEFT_MOTOR, true);

pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

void initialize() {}

void autonomous() {}

void opcontrol() {

    while (true) {
        int left_stick = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int right_stick = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        front_left = left_stick;
        back_left = left_stick;
        front_right = right_stick;
        back_right = right_stick;

        pros::delay(20);
    }
}
