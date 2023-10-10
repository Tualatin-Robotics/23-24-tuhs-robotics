#ifndef __DRIVETRAIN__
#define __DRIVETRAIN__

#include "motors.h"

void init_drivetrain() {
    
}

void drivetrain(int team, pros::Controller drive_con) {

    int left_stick = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right_stick = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    switch (team) {
        case 2:
            front_left.move_velocity(MOVE_VOLT * left_stick);
            front_right.move_voltage(MOVE_VOLT * right_stick);
            break;
        default:
            front_left.move_velocity(MOVE_VOLT * -left_stick);
            back_left.move_velocity(MOVE_VOLT * -left_stick);
            front_right.move_voltage(MOVE_VOLT * right_stick);
            back_right.move_voltage(MOVE_VOLT * right_stick);
            break;
    }
}

#endif