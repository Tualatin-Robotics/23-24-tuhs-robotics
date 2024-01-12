#ifndef __ENDGAME__
#define __ENDAME_

#include "motors.h"

bool pressed = false;

void init_endgame() {
    endgame_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void endgame(pros::Controller drive_con, int team) {

    switch (team) 
    {
    case 1:
        if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !pressed) {
            pros::Task endgame {[=] {
                pressed = true;
                endgame_motor.move_voltage(12000);
                pros::delay(40);
                endgame_motor.move_voltage(0);
            }};
        }  

        if (pressed) {
            endgame_motor.move_voltage(12000);
            endgame_motor.move_voltage(-12000);
        } 
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
       
}
#endif