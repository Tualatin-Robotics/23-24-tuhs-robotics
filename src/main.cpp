#include "main.h"
#include <fstream>
#include "motors.h"
#include "drivetrain.hpp"
#include "replay.hpp"
#include "acorngrab.hpp"
#include "endgame.hpp"
#include <chrono>

pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

std::ifstream A_Team("/usd/A_Team.txt");
std::ifstream B_Team("/usd/B_Team.txt");
std::ifstream C_Team("/usd/C_Team.txt");

using namespace std::chrono_literals;

int team = 0;

void initialize() {
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

    /*
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

        drive_auton(&vc, team);

        acorngrab_auton(&vc, team);

        auto t2 = clock.now();
		std::chrono::milliseconds ms_adjust = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		std::cout << "Auton control took " << ms_adjust.count() << " ms" << std::endl;
		pros::delay(11); //number should be tweeked for different autons
    }*/

    while (true) {
        front_left.move_voltage(-12000);
        front_right.move_voltage(12000);
        back_right.move_voltage(-12000);
        back_left.move_voltage(12000);
    }
}

void opcontrol() {
    init_drivetrain();
    init_acorngrab();

    VirtualController vc(&drive_con, false);
    std::chrono::high_resolution_clock clock;

    while (true) {
        auto t1 = clock.now();

        drive_op(drive_con, team);

        acorngrab_op(drive_con, team);
        endgame(drive_con, team);

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
