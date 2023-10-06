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
        case 2:
            front_left = leftstick_y;
            front_right = rightstick_y;
            break;
        default:
            front_left = leftstick_y;
            back_left = leftstick_y;
            front_right = rightstick_y;
            back_right = rightstick_y;
            break;
    }
}

#endif