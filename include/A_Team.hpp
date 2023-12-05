#ifndef __A_Team__
#define __A_Team__

#include "motors.h"
#include "replay.hpp"

class A_Team {

    public: 
        void drivetrain(pros::Controller drive_con) {

            int left_stick_y = inputs[0];
            int right_stick_y = inputs[2];

            front_left.move_voltage(MOVE_VOLT * -left_stick_y);
            back_left.move_voltage(MOVE_VOLT * -left_stick_y);
            front_right.move_voltage(MOVE_VOLT * right_stick_y);
            back_right.move_voltage(MOVE_VOLT * right_stick_y);
            middle_right.move_voltage(MOVE_VOLT * -right_stick_y);
            middle_left.move_voltage(MOVE_VOLT * left_stick_y);
        }

        void acorn_grab(pros::Controller drive_con) {
            if (left_trigger) {
                acorn_grab_left.move_voltage(12000 * acorngrabvolts);
            } else if (left_bumper) {
                acorn_grab_left.move_voltage(-12000 * acorngrabvolts);
            } else {
                acorn_grab_left.move_voltage(0);
            }
        }

        void endgame(pros::Controller drive_con) {
            
        }
};
#endif