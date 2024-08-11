#include <iostream>
#include <fstream>
#include "Quaternion.h"
#include "Vector.h"
#include "Logging.h"

// 전역 변수 선언
double Vm, Alpha, Gamma, L, Yb, X, Y, Z;
double Length, Width, Height;
int status, time;

// 사용자가 입력한 변수를 받아 전역 변수에 저장하는 함수
void GetUserInput() {
    std::cout << "Enter initial velocity (Vm): ";
    std::cin >> Vm;

    std::cout << "Enter launch angle (Alpha): ";
    std::cin >> Alpha;

    std::cout << "Enter launch angle (Gamma): ";
    std::cin >> Gamma;

    std::cout << "Enter launch distance (L): ";
    std::cin >> L;

    std::cout << "Enter initial height (Yb): ";
    std::cin >> Yb;

    std::cout << "Enter target X coordinate: ";
    std::cin >> X;

    std::cout << "Enter target Y coordinate: ";
    std::cin >> Y;

    std::cout << "Enter target Z coordinate: ";
    std::cin >> Z;

    std::cout << "Enter target length: ";
    std::cin >> Length;

    std::cout << "Enter target width: ";
    std::cin >> Width;

    std::cout << "Enter target height: ";
    std::cin >> Height;
}

// 시뮬레이션을 수행하는 함수 (간단한 예시)
int DoSimulation() {
    // 간단한 시뮬레이션 로직
    time += 1; // 시간을 증가시킴

    // 포탄이 목표물에 맞았는지 여부를 판단 (단순화된 조건)
    if (X == Vm * time && Y == Vm * time) {
        return 1; // Direct Hit
    }

    // 포탄이 땅에 떨어졌는지 여부를 판단 (단순화된 조건)
    if (Yb + Vm * time < 0) {
        return 2; // Missed Target
    }

    // 타임아웃 조건을 가정 (예: 시간이 너무 오래 걸렸을 때)
    if (time > 100) {
        return 3; // Simulation Timed Out
    }

    return 0; // 계속 시뮬레이션 진행
}

// 화면 업데이트 함수 (간단한 예시)
void UpdateScreen() {
    std::cout << "Simulating... Time: " << time << std::endl;
}

int main() {
    // 유저 입력을 받아 전역 변수에 저장
    GetUserInput();

    // time과 status 변수를 초기화
    status = 0;
    time = 0;

    // 목표물을 맞히거나, 포탄이 땅에 떨어지거나, 타임아웃 될 때까지 시간단계별로 시뮬레이션을 돌린다.
    while (status == 0) {
        // 다음 시간단계를 시뮬레이션
        status = DoSimulation();

        // 화면 업데이트
        UpdateScreen();
    }

    // 결과를 보고
    if (status == 1)
        std::cout << "Direct Hit!" << std::endl;
    else if (status == 2)
        std::cout << "Missed Target!" << std::endl;
    else if (status == 3)
        std::cout << "Simulation Timed Out!" << std::endl;

    return 0;
}
