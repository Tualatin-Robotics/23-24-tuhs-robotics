#ifndef __C_Team__
#define __C_Team__

#include "motors.h"
#include "replay.hpp"

class C_Team {

    bool acorngrabbing = false; // true means it is closed, false means it is open
    bool reloaded = true;
    float acorngrabvolts = 1; // percentage
    float acornungrabvolts = 0.25; // percentage
    float idlegrabvolts = 1;
    public:
        void drivetrain(pros::Controller drive_con, int * inputs) {
            int left_stick_x = inputs[3];
            int left_stick_y = inputs[0];
            int right_stick_x = inputs[1];
            int right_stick_y = inputs[2];

            int right_motors = left_stick_y + left_stick_x;
            int left_motors = left_stick_y - left_stick_x;

            front_right.move_voltage(MOVE_VOLT * (-right_motors + right_stick_x));
            front_left.move_voltage(MOVE_VOLT * (-left_motors + right_stick_x));
            back_right.move_voltage(MOVE_VOLT * (left_motors + right_stick_x));
            back_left.move_voltage(MOVE_VOLT * (right_motors + right_stick_x));
        }

        void acorn_grab(pros::Controller drive_con, int * inputs) {
            int right_bumper = inputs[5];
            int right_trigger = inputs[6];
            if (right_trigger && !acorngrabbing) {
                pros::Task grab {[=] {
                    std::cout << "Right Trigger pressed" << std::endl;
                    acorn_grab_left.move_voltage(MOVE_TOTAL * -acorngrabvolts);
                    pros::delay(500); //value will need tweaking
                    acorn_grab_left.move_voltage(MOVE_TOTAL * -idlegrabvolts);
                    acorngrabbing = true;
                }};
            } else if (right_trigger && acorngrabbing) {
                pros::Task ungrab {[=] {
                    acorn_grab_left.move_voltage(MOVE_TOTAL * acornungrabvolts);
                    acorn_grab_right.move_voltage(MOVE_TOTAL * -acornungrabvolts);
                    pros::delay(500); //value will need tweaking
                    acorn_grab_left.move_voltage(MOVE_TOTAL * idlegrabvolts);
                    acorngrabbing = false;
                }};
            }
        }

        void endgame(pros::Controller drive_con, int * inputs) {

        }
};

#endif