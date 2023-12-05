#ifndef __B_Team__
#define __B_Team__

#include "motors.h"
#include "replay.hpp"

class B_Team {

    public:
        void drivetrain(pros::Controller drive_con) {
            int left_stick_x = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
            int left_stick_y = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            int right_stick_x = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
            int right_stick_y = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

            int right_motors = left_stick_y + left_stick_x;
            int left_motors = left_stick_y - left_stick_x;

            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -right_stick_y);
        }

        void acorn_grab(pros::Controller drive_con) {
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
        }

        void endgame(pros::Controller drive_con) {
            
        }
};

#endif