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


bool auton = false;
bool op = false;

int inputs[16];

using namespace std::chrono_literals;

int team = 0;

void get_inputs() {
    if (auton) {
        VirtualController vc(&drive_con, false);
            inputs[0] = vc.ly; // 0 Left Y
            inputs[1] = vc.rx; // 1 Right X
            inputs[2] = vc.ry; // 2 Right Y
            inputs[3] = vc.lx; // 3 Left X

            inputs[4] = vc.l1; // 4 L1
            inputs[5] = vc.r1; // 5 R1
            inputs[6] = vc.r2; // 6 R2
            inputs[7] = vc.l2; // 7 L2

            inputs[8] = vc.a; // 8 A
            inputs[9] = vc.b; // 9 B
            inputs[10] = vc.x; // 10 X
            inputs[11] = vc.y; // 11 Y
            
            inputs[12] = vc.d; // 12 Down
            inputs[13] = vc.u; // 13 Up
            inputs[14] = vc.l; // 14 Left
            inputs[15] = vc.r; // 15 Right
    } else if (op) {
        inputs[0] = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y); // 0 Left Y
        inputs[1] = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // 1 Right X
        inputs[2] = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y); // 2 Right Y
        inputs[3] = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X); // 3 Left X

        inputs[4] = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_L1); // 4 L1
        inputs[5] = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_R1); // 5 R1
        inputs[6] = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_R2); // 6 R2
        inputs[7] = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_L2); // 7 L2

        inputs[8] = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_A); // 8 A
        inputs[9] = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_B); // 9 B
        inputs[10] = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_X); // 10 X
        inputs[11] = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_Y); // 11 Y

        inputs[12] = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN); // 12 Down
        inputs[13] = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_UP); // 13 Up
        inputs[14] = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT); // 14 Left
        inputs[15] = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT); // 15 Right
    }
}

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
    auton = true;
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
            std::cout << "No SD card insterted on auton" << std::endl;
            team = 4;
        }
    }

    std::cout << "Auton passed file check" << std::endl;
    VirtualController vc(&drive_con, true);
    std::chrono::high_resolution_clock clock;

    std::cout << "auton passed vc check" << std::endl;

    while (true) {
        std::cout << "auton running" << std::endl;
        auto t1 = clock.now();

        get_inputs();

        vc.read_from_file();

        switch (team) {
            case 1:
                A_team.drivetrain(inputs);
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
    auton = false;
}

void opcontrol() {
    op = true;
    VirtualController vc(&drive_con, false);
    std::chrono::high_resolution_clock clock;

    while (true) {
        auto t1 = clock.now();
        get_inputs();

        switch (team) {
            case 1:
                A_team.drivetrain(inputs);
                A_team.acorn_grab(inputs);
                A_team.endgame(inputs);
                break;
            case 2:
                B_team.drivetrain(inputs);
                B_team.acorn_grab(inputs);
                break;
            case 3:
                C_team.drivetrain(inputs);
                C_team.acorn_grab(inputs);
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
    op = false;
}
