#ifndef __ACORN_GRABBING__
#define __ACORN_GRABBING__

#include "replay.hpp"
#include "motors.h"

bool acorngrabbing = true; // true means it is closed, false means it is open
int acorngrabvolts = 64;

void acorn_grabbing_op(int team, pros::Controller drive_con) {
    switch (team) {
        case 1:
            break;
        case 2:
            if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !acorngrabbing) {
                acorn_grab_left.move_voltage(MOVE_VOLT * -acorngrabvolts);
                acorn_grab_right.move_voltage(MOVE_VOLT * acorngrabvolts);
                pros::delay(5); //value will need tweaking
                acorngrabbing = true;
            } else if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && acorngrabbing) {
                acorn_grab_left.move_voltage(MOVE_VOLT * acorngrabvolts);
                acorn_grab_right.move_voltage(MOVE_VOLT * -acorngrabvolts);
                pros::delay(5); //value will need tweaking
                acorngrabbing = false;
            }
            break;
        case 3:
            break;
    }
}
void acorn_grabbing_auton(VirtualController* vc, int team) {
    switch (team)
    {
        case 1:
            break;
        case 2:
            if (vc->r2 && !acorngrabbing) {
                acorn_grab_left.move_voltage(MOVE_VOLT * -acorngrabvolts);
                acorn_grab_right.move_voltage(MOVE_VOLT * acorngrabvolts);
                pros::delay(5);
                acorngrabbing = true;
            } else if (vc->r2 && acorngrabbing) {
                acorn_grab_left.move_voltage(MOVE_VOLT * acorngrabvolts);
                acorn_grab_right.move_voltage(MOVE_VOLT * -acorngrabvolts);
                pros::delay(5);
                acorngrabbing = false;
            }
            break;
        case 3:
            break;
        default:
            break;
    }
}

#endif