#ifndef __DRIVETRAIN__
#define __DRIVETRAIN__

#include "replay.hpp"
#include "motors.h"

int deadzone = 20;

bool left_stick_x_input = false;
bool left_stick_y_input = false;
bool right_stick_x_input = false;

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
            left_stick_x_input = (left_stick_x > deadzone || left_stick_x < -deadzone);
            left_stick_y_input = (left_stick_y > deadzone || left_stick_y < -deadzone);
            right_stick_x_input = (right_stick_x > deadzone || right_stick_x < -deadzone);
            //if diagonal zeros (maybe later)
            if (left_stick_x_input && left_stick_y_input) {
                front_left = 0;
                back_left = 0;
                front_right = 0;
                back_right = 0;
                break;
            }
            //turn left and right if no input from other stick
            if (right_stick_x_input && !(left_stick_x_input || left_stick_y_input)) {
                std::cout << "turn Left / Right" << std::endl;
                front_left.move_voltage(MOVE_VOLT * right_stick_x);
                front_right.move_voltage(MOVE_VOLT * right_stick_x);
                back_left.move_voltage(MOVE_VOLT * right_stick_x);
                back_right.move_voltage(MOVE_VOLT * right_stick_x);
                
            }
            else if (!left_stick_x_input || left_stick_y_input) {
                front_left = 0;
                back_left = 0;
                front_right = 0;
                back_right = 0;
            }
            // forward / backwards
            if (left_stick_y_input && !(right_stick_x_input || left_stick_x_input)) {
                front_left.move_voltage(MOVE_VOLT * left_stick_y);
                front_right.move_voltage(MOVE_VOLT * -left_stick_y);
                back_left.move_voltage(MOVE_VOLT * left_stick_y);
                back_right.move_voltage(MOVE_VOLT * -left_stick_y);
            }
            else if (!(left_stick_x_input || right_stick_x_input || left_stick_y_input)) {
                front_left = 0;
                back_left = 0;
                front_right = 0;
                back_right = 0;
            }
            if (left_stick_x_input && !(right_stick_x_input || left_stick_y_input)) {
                front_left.move_voltage(MOVE_VOLT * left_stick_x);
                front_right.move_voltage(MOVE_VOLT * left_stick_x);
                back_left.move_voltage(MOVE_VOLT * -left_stick_x);
                back_right.move_voltage(MOVE_VOLT * -left_stick_x);
            }
            else if (!(left_stick_x_input || left_stick_y_input || right_stick_x_input)) {
                front_left = 0;
                back_left = 0;
                front_right = 0;
                back_right = 0;
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
        case 1:
            break;
        case 2:
            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -right_stick_y);
            break;
        case 3:
            if ((left_stick_x > deadzone || left_stick_x < -deadzone) && (left_stick_y > deadzone || left_stick_y < -deadzone)) {
                front_left = 0;
                back_left = 0;
                front_right = 0;
                back_right = 0;
                break;
            }
            if ((right_stick_x > deadzone || right_stick_x < -deadzone) && !(left_stick_x > deadzone || left_stick_x < -deadzone) || (left_stick_y > deadzone || left_stick_y < -deadzone)) {
                std::cout << "turn Left / Right" << std::endl;
                front_left.move_voltage(MOVE_VOLT * right_stick_x);
                front_right.move_voltage(MOVE_VOLT * right_stick_x);
                back_left.move_voltage(MOVE_VOLT * right_stick_x);
                back_right.move_voltage(MOVE_VOLT * right_stick_x);
                
            }
            else if (!(left_stick_y > deadzone || left_stick_y < -deadzone)) {
                front_left = 0;
                back_left = 0;
                front_right = 0;
                back_right = 0;
            }
            // forward / backwards
            if (left_stick_y > deadzone || left_stick_y < -deadzone) {
                front_left.move_voltage(MOVE_VOLT * left_stick_y);
                front_right.move_voltage(MOVE_VOLT * -left_stick_y);
                back_left.move_voltage(MOVE_VOLT * left_stick_y);
                back_right.move_voltage(MOVE_VOLT * -left_stick_y);
            }
            else if (!(left_stick_x > deadzone || left_stick_x < -deadzone)) {
                front_left = 0;
                back_left = 0;
                front_right = 0;
                back_right = 0;
            }
            if (left_stick_x > deadzone || left_stick_x < -deadzone) {
                front_left.move_voltage(MOVE_VOLT * -left_stick_x);
                front_right.move_voltage(MOVE_VOLT * left_stick_x);
                back_left.move_voltage(MOVE_VOLT * -left_stick_x);
                back_right.move_voltage(MOVE_VOLT * left_stick_x);
            }
            else if (!(left_stick_y > deadzone || left_stick_y < -deadzone)) {
                front_left = 0;
                back_left = 0;
                front_right = 0;
                back_right = 0;
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

#endif