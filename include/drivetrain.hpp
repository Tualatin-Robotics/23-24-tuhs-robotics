#ifndef __DRIVETRAIN__
#define __DRIVETRAIN__

#include "motors.h"

void init_drivetrain() {
    
}

void drivetrain(int team, pros::Controller drive_con) {

    int leftstick_x = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    int leftstick_y = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightstick_x = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    int rightstick_y = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    switch (team) {
        /* leftstick_x and leftstick_y control direction with this equasion 
            the table it makes (with just 1, 0, and -1) looks like this:
              -leftstick_y + leftstick_x
      leftstick_x  -1  0  1

               -1   0  1  2
   leftstick_y  0  -1  0  1
                1  -2 -1  0
            making leftstick_x negative flips the table
            what this does is :
            when the joystick is pointed up, both motors get 1, making it go forward.
            when the joystick is pointed upright, the left motor gets 1 (bc below if statements make it not 2) and the right motor gets 0, making it turn right
            when the joystick is pointed right, the left motor gets 1 and the right motor gets -1, making it spin to the right in place
            when the joystick is pointed downright, the left motor gets 0 and the right motor gets -1, making it spin to the right with the other motor as it's axis
            when the joystick is pointed down, both motors get -1, making it go backward.
            all these values are flipped for the other side.
        */
        int left_motors = -leftstick_y + leftstick_x;
        int right_motors = -leftstick_y - leftstick_x;
        // we can get numbers above 1, make those equal 1
        if (left_motors > 1) { left_motors = 1; }
        if (left_motors <-1) { left_motors =-1; }
        if (right_motors > 1) { right_motors = 1; }
        if (right_motors <-1) { right_motors =-1; }
        /* multiply both by rightstick_y, the speed
            add 1.1 because then when you don't have the right joystick pointed anywhere, 
            it isn't just completely stopped, but you can pull back on it to slow way down and forward to speed up
            divide it by 2 so we don't give it values higher than the motor can go
            the proportions of this need to be tweaked ofc
        */
        left_motors = left_motors * (rightstick_y + 1.1) / 2;
        right_motors = right_motors * (rightstick_y + 1.1) / 2;

        case 2:
            front_left = left_motors;
            front_right = right_motors;
            break;
        default:
            front_left = left_motors;
            back_left = left_motors;
            front_right = right_motors;
            back_right = right_motors;
            break;
    }
}

#endif