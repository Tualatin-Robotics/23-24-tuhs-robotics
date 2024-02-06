#ifndef __WINGS__
#define __WINGS__

#include "main.h"
#include "motors.h"

bool wing_down = false;
pros::ADIDigitalOut wing_right(WING_RIGHT);
pros::ADIDigitalOut wing_left(WING_LEFT);

void wings(pros::Controller drive_con, int team) {
    switch (team)
    {
        case 1:
            if (drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
                if (!wing_down) {
                    wing_right.set_value(true);
                    wing_left.set_value(true);
                    wing_down = true;
                }
                else {
                    wing_right.set_value(false);
                    wing_left.set_value(false);
                    wing_down = false;
                }
            }
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
}

#endif