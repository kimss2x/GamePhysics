﻿#include <iostream>
#include <fstream>
#include "Simulator.h"  // Simulator 클래스 포함
#include <limits>

// 시뮬레이션 관련 변수들
double Vm = 100.0;      // 발사 속도
double Alpha = 45.0;    // 발사 각도 (Pitch)
double Gamma = 0.0;     // 발사 각도 (Yaw)
double Yb = 10.0;       // 발사 위치의 높이
double X = 1020.0;      // 목표물의 X 위치
double Z = 0.0;         // 목표물의 Z 위치
double Length = 10.0;   // 목표물의 길이
double Width = 10.0;    // 목표물의 폭
double Height = 10.0;   // 목표물의 높이
double tInc = 0.1;      // 시뮬레이션 시간 증가 단위

// 유저 입력을 받아 각 파라미터 설정
void GetUserInput() {
    char key;
    double inputValue;
    while (true) {
        std::cout << "Enter 'x' to set Pitch (Alpha) or 'y' to set Yaw (Gamma), or 's' to start simulation: ";
        std::cin >> key;

        if (key == 's') {
            break;
        }

        switch (key) {
        case 'x':
            std::cout << "Enter Pitch (Alpha) in degrees: ";
            std::cin >> inputValue;
            if (!std::cin.fail()) {
                Alpha = inputValue;
            }
            else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, Pitch (Alpha) remains " << Alpha << " degrees.\n";
            }
            break;
        case 'y':
            std::cout << "Enter Yaw (Gamma) in degrees: ";
            std::cin >> inputValue;
            if (!std::cin.fail()) {
                Gamma = inputValue;
            }
            else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, Yaw (Gamma) remains " << Gamma << " degrees.\n";
            }
            break;
        default:
            std::cout << "Invalid option. Please enter 'x', 'y', or 's'.\n";
            break;
        }
    }
}

int main() {
    // 유저 입력 받기
    GetUserInput();

    // 시뮬레이터 객체 생성 및 초기화
    Simulator simulator(Vm, Alpha, Gamma, Yb, X, Z, Length, Width, Height, tInc);
    simulator.initialize();

    std::cout << "Starting simulation...\n";

    // 시뮬레이션 루프
    while (simulator.runSimulationStep() == 0) {
        std::string status = simulator.getSimulationStatus();   // 현재 상태 출력
        std::cout << status << std::endl;

        // 간단한 종료 조건: 시뮬레이션 시간이 길어지면 자동 종료
        if (simulator.getSimulationTime() > 100.0) {            // 100초가 넘어가면 종료
            std::cout << "Simulation timed out.\n";
            break;
        }
    }

    // 최종 시뮬레이션 결과 출력
    if (simulator.runSimulationStep() == 1) {
        std::cout << "Target hit!" << std::endl;
    }
    else {
        std::cout << "Simulation ended without a hit." << std::endl;
    }

    return 0;
}
