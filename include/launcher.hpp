#ifndef __LAUNCHER__
#define __LAUNCHER__
#include "motors.h"
#include "main.h"

bool running;
bool up = true;
bool down;

pros::ADIDigitalIn launcher_switch(SWITCH_PORT);

void init_launcher() {
    catapult.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void launcher_run(pros::Controller drive_con, int team) {
    switch (team)
    {
        case 1:
            bool switch_state = launcher_switch.get_value();
            if (!switch_state) {
                catapult.move_voltage(12000);
            }
            else if (switch_state && !drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
                down = true;
                catapult.move_voltage(0);
            }

            if (drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B) && switch_state) {
                down = false;
                catapult.move_voltage(12000);
            }
        break;
    }
}

#endif