#ifndef __ACORN_GRABBING__
#define __ACORN_GRABBING__

#include "replay.hpp"
#include "motors.h"

bool acorngrabbing = true; // true means it is closed, false means it is open
int acorngrabvolts = 64;
int idlegrabvolts = 16;
int acorngrabtime = 125;

void init_acorngrab() {
    acorn_grab_left.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    acorn_grab_right.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void acorngrab(int * c, int team) {
    int right_trigger = c[0];
	int left_trigger = c[1];
    int left_bumper = c[2];

    switch (team) {
        // A Team
        case 1:
            if (left_trigger) {
                acorn_grab_left.move_voltage(MOVE_VOLT * acorngrabvolts);
            } else if (left_bumper) {
                acorn_grab_left.move_voltage(MOVE_VOLT * -acorngrabvolts);
            }
            break;
        // B or C Team
        case 2: case 3:
            if (right_trigger && !acorngrabbing) {
                acorn_grab_left.move_voltage(MOVE_VOLT * -acorngrabvolts);
                acorn_grab_right.move_voltage(MOVE_VOLT * acorngrabvolts);
                pros::delay(acorngrabtime); //value will need tweaking
                acorn_grab_left.move_voltage(0);
                acorn_grab_right.move_voltage(0);
                acorngrabbing = true;
            } else if (right_trigger && acorngrabbing) {
                acorn_grab_left.move_voltage(MOVE_VOLT * acorngrabvolts);
                acorn_grab_right.move_voltage(MOVE_VOLT * -acorngrabvolts);
                pros::delay(acorngrabtime); //value will need tweaking
                acorn_grab_left.move_voltage(MOVE_VOLT * idlegrabvolts);
                acorn_grab_right.move_voltage(MOVE_VOLT * idlegrabvolts);
                acorngrabbing = false;
            }
            break;
    }
}

void acorngrab_op(pros::Controller drive_con, int team) {
    int inputs[3] = {
        drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2),
        drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_L2),
        drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_L1)
        
    };

    acorngrab(inputs, team);
}

void acorngrab_auton(VirtualController* vc, int team) {
    /*int inputs[2] = {
        
    };*/

    //acorn_grabbing(inputs, team);
}

#endif