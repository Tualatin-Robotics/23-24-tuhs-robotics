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
        // leftstick_x and leftstick_y control direction with this equasion
        int left_motors = -leftstick_y + leftstick_x;
        int right_motors = -leftstick_y - leftstick_x;
        // the equasion has numbers above 1, make those equal 1
        if (left_motors > 1) { left_motors = 1; }
        if (left_motors <-1) { left_motors =-1; }
        if (right_motors > 1) { right_motors = 1; }
        if (right_motors <-1) { right_motors =-1; }
        // multiply both by rightstick_y, the speed
        left_motors *= rightstick_y + 1.1;
        right_motors *= rightstick_y + 1.1;

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