#ifndef __LAUNCHER__
#define __LAUNCHER__
#include "motors.h"
#include "main.h"

bool running;
bool down;
bool switch_state;

pros::ADIDigitalIn launcher_switch(SWITCH_PORT);

void init_launcher() {
    catapult.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void launcher_run(pros::Controller drive_con, int team) {
    switch (team)
    {
        case 1: {
            if (drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
                running = !running;
                catapult.move_voltage(12000*running);
            }
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            if (drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
                running = !running;
                catapult.move_voltage(10000 * running);
                catapult_2.move_voltage(-10000 * running);
            }
            break;
        }
    }
}

#endif