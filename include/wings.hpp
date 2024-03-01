#ifndef __WINGS__
#define __WINGS__

#include "main.h"
#include "motors.h"

bool wings_down = false;
bool left_wing_down = false;
bool right_wing_down = false;
pros::ADIDigitalOut wing_right(WING_RIGHT);
pros::ADIDigitalOut wing_left(WING_LEFT);

void wings(pros::Controller drive_con, int team) {
    switch (team)
    {
        case 1:
            if (drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                wings_down = !wings_down;
                if (!right_wing_down) {
                    wing_right.set_value(wings_down);
                    right_wing_down = wings_down;
                }
                if (!left_wing_down) {
                    wing_left.set_value(wings_down);
                    left_wing_down = wings_down;
                }
            }
            if (drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
                if (left_wing_down && !right_wing_down) {
                    wings_down = true;
                }
                right_wing_down = !right_wing_down;
                wing_right.set_value(right_wing_down);
            }
            if (drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                if (right_wing_down && !left_wing_down) {
                    wings_down = true;
                }
                left_wing_down = !left_wing_down;
                wing_left.set_value(left_wing_down);
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