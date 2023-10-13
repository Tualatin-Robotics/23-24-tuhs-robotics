#ifndef __DRIVETRAIN__
#define __DRIVETRAIN__

#include "replay.hpp"
#include "motors.h"

void init_drivetrain() {
    front_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    front_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    back_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    back_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void drive_op(int team, pros::Controller drive_con) {

    int left_stick = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right_stick = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    switch (team) {
        case 2:
            front_left.move_voltage(MOVE_VOLT * left_stick);
            front_right.move_voltage(MOVE_VOLT * -right_stick);
            break;
        default:
            front_left.move_voltage(MOVE_VOLT * -left_stick);
            back_left.move_voltage(MOVE_VOLT * -left_stick);
            front_right.move_voltage(MOVE_VOLT * right_stick);
            back_right.move_voltage(MOVE_VOLT * right_stick);
            break;
    }
}

void drive_auton(VirtualController* vc, int team) {
    int left_stick = vc->ly;
	int right_stick = vc->ry;

    front_left.move_voltage(MOVE_VOLT * left_stick);
    back_left.move_voltage(MOVE_VOLT * left_stick);
    front_right.move_voltage(MOVE_VOLT * right_stick);
    back_right.move_voltage(MOVE_VOLT * right_stick);
}

#endif