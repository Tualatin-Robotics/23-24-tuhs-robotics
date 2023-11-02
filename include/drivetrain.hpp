#ifndef __DRIVETRAIN__
#define __DRIVETRAIN__

#include "replay.hpp"
#include "motors.h"

int deadzone = 10;
bool diagonal = false;
bool acorngrabbing = true; // true means it is closed, false means it is open
int acorngrabvolts = 64;

void init_drivetrain() {
    front_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    front_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    back_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    back_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    acorn_grab_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    acorn_grab_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void drive_op(int team, pros::Controller drive_con) {

    int left_stick_y = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right_stick_y = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    int left_stick_x = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    int right_stick_x = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    int right_trigger = drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);
    int left_bumper = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    int left_trigger = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

    int right_motors = left_stick_y + left_stick_x;
    int left_motors = left_stick_y - left_stick_x;

    switch (team) {
        case 1:
            front_left.move_voltage(MOVE_VOLT * -left_stick_y);
            back_left.move_voltage(MOVE_VOLT * -left_stick_y);
            front_right.move_voltage(MOVE_VOLT * right_stick_y);
            back_right.move_voltage(MOVE_VOLT * right_stick_y);

            if (left_bumper) {
                acorn_grab_left.move_voltage(MOVE_VOLT * acorngrabvolts);
            } else if (left_trigger) {
                acorn_grab_left.move_voltage(MOVE_VOLT * -acorngrabvolts);
            } else {
                acorn_grab_left.move_voltage(0);
            }
            break;
        case 2:
            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -right_stick_y);
            if (right_trigger == false) { break; }
            if (acorngrabbing) {
                acorn_grab_left.move_voltage(MOVE_VOLT * acorngrabvolts);
                acorn_grab_right.move_voltage(MOVE_VOLT * -acorngrabvolts);
            } else {
                acorn_grab_left.move_voltage(MOVE_VOLT * -acorngrabvolts);
                acorn_grab_right.move_voltage(MOVE_VOLT * acorngrabvolts);
            }
            acorngrabbing = (acorngrabbing != true);

            
            break;
        case 3:
            front_left.move_voltage(MOVE_VOLT * right_motors);
            back_left.move_voltage(MOVE_VOLT * left_motors);
            front_right.move_voltage(MOVE_VOLT * -left_motors);
            back_right.move_voltage(MOVE_VOLT * -right_motors);

            if (abs(right_stick_x) > 1) {
                front_left.move_voltage(MOVE_VOLT * right_stick_x);
                back_left.move_voltage(MOVE_VOLT * right_stick_x);
                front_right.move_voltage(MOVE_VOLT * right_stick_x);
                back_right.move_voltage(MOVE_VOLT * right_stick_x);
            }
            break;
        default:
            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            back_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -right_stick_y);
            back_right.move_voltage(MOVE_VOLT * -right_stick_y);
            break;
    }
}

void drive_auton(VirtualController* vc, int team) {
    int left_stick_y = vc->ly;
	int right_stick_y = vc->ry;
    int left_stick_x = vc->lx;
    int right_stick_x = vc->rx;

    switch (team) {
        case 2:
            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -right_stick_y);
            break;
        case 3:
            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -left_stick_y);
            break;
        default:
            front_left.move_voltage(MOVE_VOLT * -left_stick_y);
            back_left.move_voltage(MOVE_VOLT * -left_stick_y);
            front_right.move_voltage(MOVE_VOLT * right_stick_y);
            back_right.move_voltage(MOVE_VOLT * right_stick_y);
            break;
    }
}

#endif