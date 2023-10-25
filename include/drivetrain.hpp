#ifndef __DRIVETRAIN__
#define __DRIVETRAIN__

#include "replay.hpp"
#include "motors.h"

int deadzone = 10;
bool diagonal = false;

void init_drivetrain() {
    front_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    front_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    back_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    back_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void drive_op(int team, pros::Controller drive_con) {

    int left_stick_y = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right_stick_y = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    int left_stick_x = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    int right_stick_x = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    switch (team) {
        case 1:
            break;
        case 2:
            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -right_stick_y);
            break;
        case 3:
            // diagonal movement
            if ((left_stick_x > deadzone+10 && left_stick_y > deadzone+10) || (left_stick_y < -(deadzone+10) && left_stick_x < -(deadzone+10)) || (left_stick_x < -(deadzone+10) && left_stick_y > deadzone+10) || (left_stick_x > deadzone+10 && left_stick_y < -(deadzone+10))) {
                diagonal = true;
                int average = (abs(left_stick_x)+abs(left_stick_y))/2; // average value for sticks
                // if stick it top right
                if (left_stick_x > 0 && left_stick_y > 0) {
                    front_left.move_voltage(MOVE_VOLT * average);
                    back_right.move_voltage(MOVE_VOLT * average);
                    front_right = 0;
                    back_left = 0;
                }
                // if stick is top left
                if (left_stick_x < 0 && left_stick_y > 0) {
                    front_right.move_voltage(MOVE_VOLT * average);
                    back_left.move_voltage(MOVE_VOLT * -average);
                    front_left = 0;
                    back_right = 0;
                }
                // if stick if bottom left
                if (left_stick_x < 0 && left_stick_y < 0) {
                    front_left.move_voltage(MOVE_VOLT * -average);
                    back_right.move_voltage(MOVE_VOLT * -average);
                    front_right = 0;
                    back_left = 0;
                }
                // if stick is bottom right
                if (left_stick_x > 0 && left_stick_y < 0) {
                    front_right.move_voltage(MOVE_VOLT * average);
                    back_left.move_voltage(MOVE_VOLT * -average);
                    front_left = 0;
                    back_right = 0;
                }
            }
            else {
                diagonal = false;
            }
            // if not moving diagonal 
            if (!diagonal) {
                // turn left / right
                if (left_stick_x > deadzone || left_stick_x < -deadzone) {
                    front_left.move_voltage(MOVE_VOLT * left_stick_x);
                    front_right.move_voltage(MOVE_VOLT * left_stick_x);
                    back_left.move_voltage(MOVE_VOLT * left_stick_x);
                    back_right.move_voltage(MOVE_VOLT * left_stick_x);
                    
                }
                // make sure motors reset to 0
                else {
                    front_left = 0;
                    front_right = 0;
                    back_left = 0;
                    back_right = 0;
                }
                // forward / backwards
                if (left_stick_y > deadzone || left_stick_y < -deadzone) {
                    front_left.move_voltage(MOVE_VOLT * left_stick_y);
                    front_right.move_voltage(MOVE_VOLT * -left_stick_y);
                    back_left.move_voltage(MOVE_VOLT * left_stick_y);
                    back_right.move_voltage(MOVE_VOLT * -left_stick_y);
                } 
                else {
                    front_left = 0;
                    front_right = 0;
                    back_left = 0;
                    back_right = 0;
                }
            }
            break;
        default:
            front_left.move_voltage(MOVE_VOLT * -left_stick_y);
            back_left.move_voltage(MOVE_VOLT * -left_stick_y);
            front_right.move_voltage(MOVE_VOLT * right_stick_y);
            back_right.move_voltage(MOVE_VOLT * right_stick_y);
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