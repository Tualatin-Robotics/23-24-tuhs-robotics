#include "main.h"
#include <fstream>
#include "motors.h"
#include "replay.hpp"
/*
#include "A_Team.hpp"
#include "B_Team.hpp"
#include "C_Team.hpp"
*/
#include <chrono>

pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

std::ifstream A_Team_File("/usd/A_Team.txt");
std::ifstream B_Team_File("/usd/B_Team.txt");
std::ifstream C_Team_File("/usd/C_Team.txt");

/*
A_Team A_team;
B_Team B_team;
C_Team C_team;
*/

bool auton = false;
bool op = false;

bool pressed = false;

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
            std::cout << "No SD card insterted on init" << std::endl;
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

        //get_inputs();

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
    auton = false;
}

void opcontrol() {
    op = true;
    VirtualController vc(&drive_con, false);
    std::chrono::high_resolution_clock clock;

    while (true) {
        auto t1 = clock.now();
        //get_inputs();

        switch (team) {
            case 1:
                if (drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B) && !pressed) {
                    acorn_grab_right.move_voltage(-12000);
                    pressed = true;
                }
                else if (drive_con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B) && pressed){
                    acorn_grab_right.move_voltage(0);
                    pressed = false;
                }

                /*
                A_team.drivetrain(drive_con);
                A_team.acorn_grab(drive_con);
                A_team.endgame(drive_con);
                */
                break;
            case 2:
            /*
                B_team.drivetrain(drive_con);
                B_team.acorn_grab(drive_con);
            */
                break;
            case 3:
            /*
                C_team.drivetrain(drive_con);
                C_team.acorn_grab(drive_con);
            */
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
/*
void get_inputs() {
    if (auton) {
        VirtualController vc(&drive_con, false);
        int inputs[16] = {
            vc.ly, // 0 Left Y
            vc.rx, // 1 Right X
            vc.ry, // 2 Right Y
            vc.ly, // 3 Left Y

            vc.l1, // 4 L1
            vc.r1, // 6 R1
            vc.r2, // 7 R2
            vc.a, // 8 A
            vc.b, // 9 B
            vc.x, // 10 X
            vc.y, // 11 Y
            vc.d, // 12 Down
            vc.u, // 13 Up
            vc.l, // 14 
            vc.r // 15
        };
    } else if (op) {
        int inputs[16] {
            drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), // 0 Left Y
            drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), // 1 Right X
            drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), // 2 Right Y
            drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X), // 3 Left Y

            drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_L1), // 4 L1
            drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_L2), // 5 L2
            drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_R1), // 6 R1
            drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_R2), // 7 R2
            drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_A), // 8 A
            drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_B), // 9 B
            drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_X), // 10 X
            drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_Y), // 11 Y
            drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN), // 12 Down
            drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_UP), // 13 Up
            drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT), // 14 
            drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) // 15
        };
    }
    return inputs;
}
*/
