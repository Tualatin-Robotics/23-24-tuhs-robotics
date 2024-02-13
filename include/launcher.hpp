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
            switch_state = launcher_switch.get_value();
            if (drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
                if (!switch_state) {
                    pros::Task launcher_down {[=] {
                        while (!switch_state) {
                            catapult.move_voltage(12000);
                            switch_state = launcher_switch.get_value();
                        }
                        catapult.move_voltage(0);
                        down = true;
                    }};
                }
                else if (switch_state && down) {
                    pros::Task launcher_up {[=] {
                        catapult.move_voltage(12000);
                        pros::delay(500); // needs tweaking
                        catapult.move_voltage(0);
                        down = false;
                    }};
                }
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