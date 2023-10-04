#include "main.h"
#include <fstream>
#include "motors.hpp"

pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

std::ifstream A_Team("/usd/A_Team.txt");
std::ifstream B_Team("/usd/B_Team.txt");
std::ifstream C_Team("/usd/C_Team.txt");

int bot = 0;

void initialize() {
    if (bot == 0) {
        if (A_Team) {
            bot = 1;
            std::cout << "A Bot" << std::endl;
        }
        if (B_Team) {
            bot = 2;
            std::cout << "B Bot" << std::endl;
        }
        if (C_Team) {
            bot = 3;
            std::cout << "C Bot" << std::endl;
        }
        if (!A_Team && !B_Team && !C_Team) {
            bot = 4;
            std::cout << "No SD card insterted" << std::endl;
        }
    }
}

void autonomous() {}

void opcontrol() {
    while (true) {
        
        switch (bot)
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

        int left_stick = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int right_stick = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        front_left = left_stick;
        back_left = left_stick;
        front_right = right_stick;
        back_right = right_stick;

        pros::delay(20);
    }
}
