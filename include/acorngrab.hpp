#ifndef __ACORN_GRABBING__
#define __ACORN_GRABBING__

#include "replay.hpp"
#include "motors.h"

bool acorngrabbing = true; // true means it is closed, false means it is open
bool reloaded = true;
float acorngrabvolts = 1;
float acornungrabvolts = 0.25;
float idlegrabvolts = 1;
int acorngrabtime[5] {
    0, 0, 500, 500, 0
};

void init_acorngrab() {
    acorn_grab_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    acorn_grab_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void acorngrab(int * c, int team) {
    int right_trigger = c[0];
    int right_bumper = c[1];
	int left_trigger = c[2];
    int left_bumper = c[3];

    switch (team) {
        // A Team
        case 1:
            if (left_trigger) {
                acorn_grab_left.move_voltage(12000 * acorngrabvolts);
            } else if (left_bumper) {
                acorn_grab_left.move_voltage(-12000 * acorngrabvolts);
            } else {
                acorn_grab_left.move_voltage(0);
            }
            
            /*endgame
            if (right_bumper && right_trigger) {
                acorn_grab_right.move_voltage(-12000);
            }
            
             shooter switched for endgame save this for later
            if (right_bumper && reloaded) {
                pros::Task {[=] {
                    reloaded = false;
                    acorn_grab_right.move_voltage(12000);
                    pros::delay(2*1000);
                    std::cout << "launch" << std::endl;
                    acorn_grab_right.move_voltage(-12000);
                    pros::delay(1*1000);
                    acorn_grab_right.move_voltage(0);
                    reloaded = true;
                }};
            }
            */
            break;
        //B Team
        case 2: 
            if (right_trigger && !acorngrabbing) {
                pros::Task grab {[=] {
                    std::cout << "Right Trigger pressed" << std::endl;
                    acorn_grab_left.move_voltage(MOVE_TOTAL * -acorngrabvolts);
                    acorn_grab_right.move_voltage(MOVE_TOTAL * acorngrabvolts);
                    pros::delay(acorngrabtime[team]); //value will need tweaking
                    acorn_grab_left.move_voltage(MOVE_TOTAL * -idlegrabvolts);
                    acorn_grab_right.move_voltage(MOVE_TOTAL * idlegrabvolts);
                    acorngrabbing = true;
                }};
            } else if (right_trigger && acorngrabbing) {
                pros::Task ungrab {[=] {
                    acorn_grab_left.move_voltage(MOVE_TOTAL * acornungrabvolts);
                    acorn_grab_right.move_voltage(MOVE_TOTAL * -acornungrabvolts);
                    pros::delay(acorngrabtime[team]); //value will need tweaking
                    acorn_grab_left.move_voltage(MOVE_TOTAL * idlegrabvolts);
                    acorn_grab_right.move_voltage(MOVE_TOTAL * -idlegrabvolts);
                    acorngrabbing = false;
                }};
            }
            break;
        //C Team
        case 3:
            if (right_trigger && !acorngrabbing) {
                pros::Task grab {[=] {
                    std::cout << "Right Trigger pressed" << std::endl;
                    acorn_grab_left.move_voltage(MOVE_TOTAL * -acorngrabvolts);
                    pros::delay(acorngrabtime[team]); //value will need tweaking
                    acorn_grab_left.move_voltage(MOVE_TOTAL * -idlegrabvolts);
                    acorngrabbing = true;
                }};
            } else if (right_trigger && acorngrabbing) {
                pros::Task ungrab {[=] {
                    acorn_grab_left.move_voltage(MOVE_TOTAL * acornungrabvolts);
                    acorn_grab_right.move_voltage(MOVE_TOTAL * -acornungrabvolts);
                    pros::delay(acorngrabtime[team]); //value will need tweaking
                    acorn_grab_left.move_voltage(MOVE_TOTAL * idlegrabvolts);
                    acorngrabbing = false;
                }};
            }
            break;
    }
}

void acorngrab_op(pros::Controller drive_con, int team) {
    int inputs[4] = {
        drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2),
        drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1),
        drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_L2),
        drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_L1)
        
    };

    acorngrab(inputs, team);
}

void acorngrab_auton(VirtualController* vc, int team) {
    int inputs[4] = {
        vc->r2,
        vc->r1,
        vc->l2,
        vc->l1
    };

    acorngrab(inputs, team);
}

#endif