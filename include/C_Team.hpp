#ifndef __C_Team__
#define __C_Team__

#include "motors.h"
#include "replay.hpp"

class C_Team {

    public:
        void drivetrain(pros::Controller drive_con) {

        }

        void acorn_grab(pros::Controller drive_con) {
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
        }

        void endgame(pros::Controller drive_con) {

        }
};

#endif