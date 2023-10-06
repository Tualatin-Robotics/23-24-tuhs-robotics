#ifndef __DRIVETRAIN__
#define __DRIVETRAIN__

#include "motors.h"

void init_drivetrain() {
    
}

void drivetrain(int team, pros::Controller drive_con) {

    int lx = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    int ly = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rx = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    int ry = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    int lv = lx * ry;
        int rv = abs(lx) * ry;
    switch (team) {
    case 2:
        left = lv;
        right = rv;
    default:
        front_left = lv;
        back_left = lv;
        front_right = rv;
        back_right = rv;
    }
    std::cout << "left: " + lv << std::endl;
    std::cout << "left: " + rv << std::endl;
}

#endif