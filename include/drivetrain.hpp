#ifndef __DRIVETRAIN__
#define __DRIVETRAIN__

#include "replay.hpp"
#include "motors.h"

void init_drivetrain() {
    front_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    front_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    back_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    back_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    middle_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    middle_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void drive(int * c, int team) {
    int left_stick_x = c[0];
	int left_stick_y = c[1];
    int right_stick_x = c[2];
    int right_stick_y = c[3];

    int right_motors = left_stick_y + left_stick_x;
    int left_motors = left_stick_y - left_stick_x;

    switch (team) {
        //A Team
        case 1:
            front_left.move_voltage(MOVE_VOLT * -left_stick_y);
            back_left.move_voltage(MOVE_VOLT * -left_stick_y);
            front_right.move_voltage(MOVE_VOLT * right_stick_y);
            back_right.move_voltage(MOVE_VOLT * right_stick_y);
            middle_right.move_voltage(MOVE_VOLT * -right_stick_y);
            middle_left.move_voltage(MOVE_VOLT * left_stick_y);
            break;
        //B Team
        case 2:
            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -right_stick_y);
            break;
        //C Team
        case 3:
            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            back_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -right_stick_y);
            back_right.move_voltage(MOVE_VOLT * -right_stick_y);
            break;
        default:
            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            back_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -right_stick_y);
            back_right.move_voltage(MOVE_VOLT * -right_stick_y);
            break;
    }
}

void drive_op(pros::Controller drive_con, int team) {

    int inputs[4] = {
        drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X),
        drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
        drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X),
        drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)
    };

    drive(inputs, team);
}

void drive_auton(VirtualController* vc, int team) {

    int inputs[4] = {
        vc->lx,
        vc->ly,
        vc->rx,
        vc->ry
    };

    drive(inputs, team);
}


#endif