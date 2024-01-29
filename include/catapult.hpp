#ifndef __CATAPULT__
#define __CATAPULT__
#include "motors.h"

bool running;
bool up = true;
bool down;

void init_catapult() {
    catapult.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void catapult_run(pros::Controller drive_con, int team) {
    switch (team)
    {
        case 1:
            if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
                if (!running) {
                    catapult.move_voltage(12000);
                    running = true;
                }
                else {
                    catapult.move_voltage(0);
                    running = false;
                }
            }

            if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
                if (!running) {
                    if (up) {
                        catapult.move_voltage(12000);
                        pros::delay(1500);
                        catapult.move_voltage(0);
                        up = false;
                        down = true;
                    }
                    else if (down) {
                        catapult.move_voltage(12000);
                        pros::delay(100);
                        down = false;
                        up = true;
                    }
                }
            }
        break;
    }
}

#endif