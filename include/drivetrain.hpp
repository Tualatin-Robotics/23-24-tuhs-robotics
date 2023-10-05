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
            left = left_stick;
            right = right_stick;
        default:
            front_left = left_stick;
            back_left = left_stick;
            front_right = right_stick;
            back_right = right_stick;
    }
}

#endif