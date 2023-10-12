#include "main.h"
#include <fstream>
#include "motors.h"
#include "drivetrain.hpp"

pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

std::ifstream A_Team("/usd/A_Team.txt");
std::ifstream B1_Team("/usd/B1_Team.txt");
std::ifstream B2_Team("/usd/B2_Team.txt");

int team = 0;

void initialize() {
    if (team == 0) {
        if (A_Team) {
            team = 1;
            std::cout << "A team" << std::endl;
        }
        if (B1_Team) {
            team = 2;
            std::cout << "B team" << std::endl;
        }
        if (B2_Team) {
            team = 3;
            std::cout << "C team" << std::endl;
        }
        if (!A_Team && !B1_Team && !B2_Team) {
            team = 4;
            std::cout << "No SD card insterted" << std::endl;
        }
    }
}

void autonomous() {
    if (team == 0) {
        if (A_Team) {
            team = 1;
            std::cout << "A team" << std::endl;
        }
        if (B1_Team) {
            team = 2;
            std::cout << "B team" << std::endl;
        }
        if (B2_Team) {
            team = 3;
            std::cout << "C team" << std::endl;
        }
        if (!A_Team && !B1_Team && !B2_Team) {
            team = 4;
            std::cout << "No SD card insterted" << std::endl;
        }
    }
}

void opcontrol() {
    init_drivetrain();

    while (true) {
        drivetrain(team, drive_con);

        pros::delay(20);
    }
}
