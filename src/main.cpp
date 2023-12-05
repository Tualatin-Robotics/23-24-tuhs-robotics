#include "main.h"
#include <fstream>
#include "motors.h"
#include "replay.hpp"
#include "A_Team.hpp"
#include "B_Team.hpp"
#include "C_Team.hpp"
#include <chrono>

pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

std::ifstream A_Team_File("/usd/A_Team.txt");
std::ifstream B_Team_File("/usd/B_Team.txt");
std::ifstream C_Team_File("/usd/C_Team.txt");

A_Team A_team;
B_Team B_team;
C_Team C_team;

using namespace std::chrono_literals;

int team = 0;

void initialize() {
    if (team == 0) {
        if (A_Team_File) {
            team = 1;
            std::cout << "A team" << std::endl;
        }
        if (B_Team_File) {
            team = 2;
            std::cout << "B team" << std::endl;
        }
        if (C_Team_File) {
            team = 3;
            std::cout << "C team" << std::endl;
        }
        if (!A_Team_File && !B_Team_File && !C_Team_File) {
            std::cout << "No SD card insterted on init" << std::endl;
            team = 4;
        }
    }
}

void autonomous() {
    std::cout << "Auton started" << std::endl;
    if (team == 0) {
        if (A_Team) {
            team = 1;
            std::cout << "A team" << std::endl;
        }
        if (B_Team) {
            team = 2;
            std::cout << "B team" << std::endl;
        }
        if (C_Team) {
            team = 3;
            std::cout << "C team" << std::endl;
        }
        if (!A_Team && !B_Team && !C_Team) {
            std::cout << "No SD card insterted on init" << std::endl;
            team = 4;
        }
    }

    std::cout << "Auton passed file check" << std::endl;
    init_drivetrain();
    init_acorngrab();
    init_endgame();
    VirtualController vc(&drive_con, true);
    std::chrono::high_resolution_clock clock;

    std::cout << "auton passed vc check" << std::endl;

    while (true) {
        std::cout << "auton running" << std::endl;
        auto t1 = clock.now();

        vc.read_from_file();

        switch (team) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
        }

        auto t2 = clock.now();
		std::chrono::milliseconds ms_adjust = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		std::cout << "Auton control took " << ms_adjust.count() << " ms" << std::endl;
		pros::delay(11); //number should be tweeked for different autons
    }
}

void opcontrol() {

    VirtualController vc(&drive_con, false);
    std::chrono::high_resolution_clock clock;

    while (true) {
        auto t1 = clock.now();

        switch (team) {
            case 1:
                A_team.drivetrain(drive_con);
                break;
            case 2:
                B_team.drivetrain(drive_con);
                
                break;
            case 3:
                C_team.drivetrain(drive_con);
                C_team.acorn_grab(drive_con);
                break;
        }

        // Replay code
		vc.record_frame();
		vc.write_to_file();

		// Record time for replay adjustment
		auto t2 = clock.now();
		std::chrono::milliseconds ms_adjust = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		std::cout << "Op control took " << ms_adjust.count() << " ms" << std::endl;
		pros::delay(10);
    }
}
