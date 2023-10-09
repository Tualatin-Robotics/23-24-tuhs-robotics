#include "main.h"
#include <fstream>
#include "motors.h"
#include "drivetrain.hpp"

pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

std::ifstream A_Team("/usd/A_Team.txt");
std::ifstream B1_Team("/usd/B1_Team.txt");
std::ifstream B2_Team("/usd/B2_Team.txt");

int bot = 0;

void initialize() {
    if (bot == 0) {
        if (A_Team) {
            bot = 1;
            std::cout << "A Bot" << std::endl;
        }
        if (B1_Team) {
            bot = 2;
            std::cout << "B Bot" << std::endl;
        }
        if (B2_Team) {
            bot = 3;
            std::cout << "C Bot" << std::endl;
        }
        if (!A_Team && !B1_Team && !B2_Team) {
            bot = 4;
            std::cout << "No SD card insterted" << std::endl;
        }
    }
}

void autonomous() {
    if (bot == 0) {
        if (A_Team) {
            bot = 1;
            std::cout << "A Bot" << std::endl;
        }
        if (B1_Team) {
            bot = 2;
            std::cout << "B Bot" << std::endl;
        }
        if (B2_Team) {
            bot = 3;
            std::cout << "C Bot" << std::endl;
        }
        if (!A_Team && !B1_Team && !B2_Team) {
            bot = 4;
            std::cout << "No SD card insterted" << std::endl;
        }
    }
}

void opcontrol() {
    while (true) {
        drivetrain(bot, drive_con);

        pros::delay(20);
    }
}
