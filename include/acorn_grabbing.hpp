#ifndef __ACORN_GRABBING__
#define __ACORN_GRABBING__

#include "replay.hpp"
#include "motors.h"

bool acorngrabbing = true; // true means it is closed, false means it is open
int acorngrabvolts = 64;

void acorn_grabbing(int * c, int team) {
    int right_trigger = c[1];
	int left_trigger = c[2];
    int left_bumper = c[3];

    switch (team) {
        case 1:
            if (left_trigger) {
                acorn_grab_left.move_voltage(MOVE_VOLT * acorngrabvolts);
            } else if (left_bumper) {
                acorn_grab_left.move_voltage(MOVE_VOLT * -acorngrabvolts);
            }
            break;
        case 2:
            if (!right_trigger) {
                break;
            }
            if (!acorngrabbing) {
                acorn_grab_left.move_voltage(MOVE_VOLT * -acorngrabvolts);
                acorn_grab_right.move_voltage(MOVE_VOLT * acorngrabvolts);
                pros::delay(5); //value will need tweaking
                acorn_grab_left.move_voltage(0);
                acorn_grab_right.move_voltage(0);
                acorngrabbing = true;
            } else {
                acorn_grab_left.move_voltage(MOVE_VOLT * acorngrabvolts);
                acorn_grab_right.move_voltage(MOVE_VOLT * -acorngrabvolts);
                pros::delay(5); //value will need tweaking
                acorn_grab_left.move_voltage(0);
                acorn_grab_right.move_voltage(0);
                acorngrabbing = false;
            }
            break;
        case 3:
            break;
    }
}

void acorn_grabbing_op(pros::Controller drive_con, int team) {
    int inputs[3] = {
        drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2),
        drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2),
        drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)
        
    };

    acorn_grabbing(inputs, team);
}

void acorn_grabbing_auton(VirtualController* vc, int team) {
    /*int inputs[2] = {
        
    };*/

    //acorn_grabbing(inputs, team);
}

#endif