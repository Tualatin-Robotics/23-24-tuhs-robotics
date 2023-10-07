#ifndef __DRIVETRAIN__
#define __DRIVETRAIN__

#include "motors.h"

void init_drivetrain() {
    
}

void drivetrain(int team, pros::Controller drive_con) {

    int leftstick_x = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    int leftstick_y = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightstick_x = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    int rightstick_y = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    switch (team) {
        int left_motors = leftstick_y;
        int right_motors = rightstick_y;
        case 2:
            front_left = left_motors;
            front_right = right_motors;
            break;
        default:
            front_left = left_motors;
            back_left = left_motors;
            front_right = right_motors;
            back_right = right_motors;
            break;
    }
}

#endif