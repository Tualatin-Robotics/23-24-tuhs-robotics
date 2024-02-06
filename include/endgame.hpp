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