#ifndef __A_Team__
#define __A_Team__

#include "motors.h"
#include "replay.hpp"

class A_Team {

    bool acorngrabbing = false; // true means it is closed, false means it is open
    bool reloaded = true;
    float acorngrabvolts = 1; // percentage
    float idlegrabvolts = 1; // percentage

    public: 
        void drivetrain(pros::Controller drive_con, int * inputs) {

            int left_stick_y = inputs[0];
            int right_stick_y = inputs[2];

            front_left.move_voltage(MOVE_VOLT * -left_stick_y);
            back_left.move_voltage(MOVE_VOLT * -left_stick_y);
            front_right.move_voltage(MOVE_VOLT * right_stick_y);
            back_right.move_voltage(MOVE_VOLT * right_stick_y);
            middle_right.move_voltage(MOVE_VOLT * -right_stick_y);
            middle_left.move_voltage(MOVE_VOLT * left_stick_y);
        }

        void acorn_grab(pros::Controller drive_con, int * inputs) {
            bool pressed = false;
            
            int left_bumper = inputs[4];
            int left_trigger = inputs[7];

            // Grabber
            if (left_trigger) {
                acorn_grab_left.move_voltage(12000 * acorngrabvolts);
            } else if (left_bumper) {
                acorn_grab_left.move_voltage(-12000 * acorngrabvolts);
            } else {
                acorn_grab_left.move_voltage(0);
            }

            // Launcher
            if (drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B) && !pressed) {
                    acorn_grab_right.move_voltage(-12000);
                    pressed = true;
            }
            else if (drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B) && pressed){
                acorn_grab_right.move_voltage(0);
                pressed = false;
            }
        }

        void endgame(pros::Controller drive_con, int * inputs) {
            int right_bumper = inputs[5];
            int right_trigger = inputs[6];
            if (right_bumper && right_trigger) {
                acorn_grab_right.move_voltage(-12000);
            }
        }
};
#endif