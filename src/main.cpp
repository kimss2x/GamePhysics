#include <iostream>
#include "PhysicsObject.h"
#include "Constants.h"

// 시뮬레이션에 필요한 변수들
double Vm = 100.0;    // 투사체의 초기 탄속, m/s
double Alpha = 45.0;  // Pitch (각도), degrees
double Gamma = 0.0;   // Yaw (각도), degrees

double Yb = 10.0;     // 대포의 초기 높이, m

double X = 100.0;     // 목표물의 중심 x좌표, m
double Z = 50.0;      // 목표물의 중심 z좌표, m
double Length = 10.0; // 목표물의 길이(x축), m
double Width = 10.0;  // 목표물의 너비(z축), m
double Height = 10.0; // 목표물의 높이(y축), m

double time = 0.0;    // 포탄이 대포에서 발사된 순간의 시간, seconds
double tInc = 0.1;    // 시뮬레이션 중에 한 단계마다 증가시킬 시간 값, seconds

// 시뮬레이션의 상태를 나타내는 변수
int status = 0;

// 시뮬레이션 함수
int DoSimulation(PhysicsObject& projectile, PhysicsObject& target) {
    // 시간에 따른 위치 계산
    projectile.Update(tInc);

    // 목표물 충돌 확인
    if (projectile.getPosition().y <= 0) {  // 포탄이 땅에 떨어졌다면
        if (projectile.getPosition().x >= X && projectile.getPosition().x <= (X + Length) &&
            projectile.getPosition().z >= Z && projectile.getPosition().z <= (Z + Width)) {
            return 1;  // Direct Hit
        }
        return 2;  // Missed Target
    }

    // 시간 초과 확인 (예: 60초 이상 시뮬레이션이 진행되었을 때)
    if (time > 60) {
        return 3;  // Simulation Timed Out
    }

    return 0;  // 계속 시뮬레이션
}

int main() {
    // 대포 발사체 초기화
    PhysicsObject projectile;
    projectile.setPosition(Vector3<double>(0.0, Yb, 0.0));
    projectile.setMass(1.0);

    // 초기 속도 설정
    Vector3<double> initialVelocity = Vector3<double>(Vm, 0.0, 0.0);
    initialVelocity = initialVelocity.Pitch(Alpha);  // Pitch 회전 (X축 기준 회전)
    initialVelocity = initialVelocity.Yaw(Gamma);    // Yaw 회전 (Y축 기준 회전)
    projectile.setVelocity(initialVelocity);

    // 중력 적용
    projectile.ApplyForce(Vector3<double>(0.0, -projectile.getMass() * Constants<double>::GRAVITY, 0.0));

    // 목표물 초기화
    PhysicsObject target;
    target.setPosition(Vector3<double>(X, 0.0, Z));
    target.setMass(100.0);  // 임의의 질량
    target.setScale(Vector3<double>(Length, Height, Width));

    // 시뮬레이션 루프
    while (status == 0) {
        // 시뮬레이션 진행
        status = DoSimulation(projectile, target);

        // 화면 업데이트 (여기서는 간단히 출력)
        std::cout << "Time: " << time << "s, Position: " << projectile.getPosition() << std::endl;

        // 시간 증가
        time += tInc;
    }

    // 결과 출력
    if (status == 1) {
        std::cout << "Direct Hit!" << std::endl;
    } else if (status == 2) {
        std::cout << "Missed Target!" << std::endl;
    } else if (status == 3) {
        std::cout << "Simulation Timed Out!" << std::endl;
    }

    return 0;
}
