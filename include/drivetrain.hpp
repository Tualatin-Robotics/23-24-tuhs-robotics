#ifndef __DRIVETRAIN__
#define __DRIVETRAIN__

#include "replay.hpp"
#include "motors.h"

<<<<<<< Updated upstream
int deadzone = 20;

bool left_stick_x_input = false;
bool left_stick_y_input = false;
bool right_stick_x_input = false;

=======
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======

    int right_motors = left_stick_y + left_stick_x;
    int left_motors = left_stick_y - left_stick_x;
>>>>>>> Stashed changes

    switch (team) {
        //A Team
        case 1:
            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            back_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -right_stick_y);
            back_right.move_voltage(MOVE_VOLT * -right_stick_y);
            break;
        //B1 Team
        case 2:
            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -right_stick_y);
            break;
        //B2 Team
        case 3:
<<<<<<< Updated upstream
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
=======
            front_right.move_voltage(MOVE_VOLT * -right_motors);
            front_left.move_voltage(MOVE_VOLT * -left_motors);
            back_right.move_voltage(MOVE_VOLT * left_motors);
            back_left.move_voltage(MOVE_VOLT * right_motors);

            if (abs(right_stick_x) > 0 && !(abs(left_stick_y) > 0 || abs(left_stick_x) > 0)) {
                front_left.move_voltage(MOVE_VOLT * right_stick_x);
                back_left.move_voltage(MOVE_VOLT * right_stick_x);
                front_right.move_voltage(MOVE_VOLT * right_stick_x);
                back_right.move_voltage(MOVE_VOLT * right_stick_x);
            }
            else if (abs(right_stick_x) > 0 && (abs(left_stick_y) > 0 || abs(left_stick_x) > 0)) {
                if (abs(left_stick_x) > 2 && abs(left_stick_y) > 2) {
                    //going diagonal with slight dead zone
                    if (left_stick_y > 0 && left_stick_x > 0) {
                        //top right
                        front_right.move_voltage(MOVE_VOLT * right_stick_x);
                        back_left.move_voltage(MOVE_VOLT * right_stick_x);
                    }
                    else if (left_stick_y > 0 && left_stick_x < 0) {
                        //top left
                        front_left.move_voltage(MOVE_VOLT * right_stick_x);
                        back_right.move_voltage(MOVE_VOLT * right_stick_x);
                    }
                    else if (left_stick_y < 0 && left_stick_x < 0) {
                        //bottom left
                        front_right.move_voltage(MOVE_VOLT * right_stick_x);
                        back_left.move_voltage(MOVE_VOLT * right_stick_x);
                    }
                    else if (left_stick_y < 0 && left_stick_x > 0) {
                        //bottom right
                        front_left.move_voltage(MOVE_VOLT * right_stick_x);
                        back_right.move_voltage(MOVE_VOLT * right_stick_x);
                    }
                }
            }
            break;
        default:
>>>>>>> Stashed changes
            break;
    }
}

void drive_auton(VirtualController* vc, int team) {
    int left_stick_y = vc->ly;
	int right_stick_y = vc->ry;
    int left_stick_x = vc->lx;
    int right_stick_x = vc->rx;

    int right_motors = left_stick_y + left_stick_x;
    int left_motors = left_stick_y - left_stick_x;

    switch (team) {
        case 1:
<<<<<<< Updated upstream
            break;
=======
            front_left.move_voltage(MOVE_VOLT * -left_stick_y);
            back_left.move_voltage(MOVE_VOLT * -left_stick_y);
            front_right.move_voltage(MOVE_VOLT * right_stick_y);
            back_right.move_voltage(MOVE_VOLT * right_stick_y);
>>>>>>> Stashed changes
        case 2:
            front_left.move_voltage(MOVE_VOLT * left_stick_y);
            front_right.move_voltage(MOVE_VOLT * -right_stick_y);
            break;
        case 3:
<<<<<<< Updated upstream
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

=======
            front_right.move_voltage(MOVE_VOLT * -right_motors);
            front_left.move_voltage(MOVE_VOLT * -left_motors);
            back_right.move_voltage(MOVE_VOLT * left_motors);
            back_left.move_voltage(MOVE_VOLT * right_motors);

            if (abs(right_stick_x) > 0 && !(abs(left_stick_y) > 0 || abs(left_stick_x) > 0)) {
                front_left.move_voltage(MOVE_VOLT * right_stick_x);
                back_left.move_voltage(MOVE_VOLT * right_stick_x);
                front_right.move_voltage(MOVE_VOLT * right_stick_x);
                back_right.move_voltage(MOVE_VOLT * right_stick_x);
            }
            else if (abs(right_stick_x) > 0 && (abs(left_stick_y) > 0 || abs(left_stick_x) > 0)) {
                if (abs(left_stick_x) > 2 && abs(left_stick_y) > 2) {
                    //going diagonal with slight dead zone
                    if (left_stick_y > 0 && left_stick_x > 0) {
                        //top right
                        front_right.move_voltage(MOVE_VOLT * right_stick_x);
                        back_left.move_voltage(MOVE_VOLT * right_stick_x);
                    }
                    else if (left_stick_y > 0 && left_stick_x < 0) {
                        //top left
                        front_left.move_voltage(MOVE_VOLT * right_stick_x);
                        back_right.move_voltage(MOVE_VOLT * right_stick_x);
                    }
                    else if (left_stick_y < 0 && left_stick_x < 0) {
                        //bottom left
                        front_right.move_voltage(MOVE_VOLT * right_stick_x);
                        back_left.move_voltage(MOVE_VOLT * right_stick_x);
                    }
                    else if (left_stick_y < 0 && left_stick_x > 0) {
                        //bottom right
                        front_left.move_voltage(MOVE_VOLT * right_stick_x);
                        back_right.move_voltage(MOVE_VOLT * right_stick_x);
                    }
                }
            }
>>>>>>> Stashed changes
            break;
        default:
            break;
    }
}

#endif