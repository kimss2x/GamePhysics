#ifndef SIMULATOR_CPP
#define SIMULATOR_CPP

#include <iostream>
#include <limits>
#include "Simulator.h"
#include "Constants.h"

Simulator::Simulator(double Vm, double Alpha, double Gamma, double Yb, double X, double Z, double Length, double Width, double Height, double tInc, double floorHeight)
    : Vm(Vm), Alpha(Alpha), Gamma(Gamma), Yb(Yb), X(X), Z(Z), Length(Length), Width(Width), Height(Height), simulationTime(0.0), tInc(tInc), floorHeight(floorHeight), status(0) {}

void Simulator::initialize() {
    // 발사체 초기화
    projectile.setPosition(Vector3<double>(0.0, Yb, 0.0));
    projectile.setMass(1.0);

    // 초기 속도 설정
    Vector3<double> initialVelocity = Vector3<double>(Vm, 0.0, 0.0).pitch(Alpha).yaw(Gamma);

    projectile.setVelocity(initialVelocity);

    // 목표물의 밀도와 부피를 통한 질량 계산
    double targetDensity = 500.0; // kg/m^3
    double targetVolume = Length * Width * Height;
    double targetMass = targetDensity * targetVolume;

    // 목표물 설정
    target.setPosition(Vector3<double>(X, 0.0, Z));
    target.setMass(targetMass);
    target.setScale(Vector3<double>(Length, Height, Width));
}

int Simulator::runSimulationStep() {
    // 발사체 업데이트
    updateProjectile();

    // 충돌 확인
    if (checkCollision()) {
        status = 1;  // 충돌 발생
        return status;
    }

    // 시간 초과 여부 확인
    if (isSimulationTimedOut()) {
        status = 3;  // 시간 초과
        return status;
    }

    simulationTime += tInc;
    return status;  // 시뮬레이션 계속
}

std::string Simulator::getSimulationStatus() const {
    return "Time: " + std::to_string(simulationTime) + "s, Position: (" +
        std::to_string(projectile.getPosition().x) + ", " +
        std::to_string(projectile.getPosition().y) + ", " +
        std::to_string(projectile.getPosition().z) + ")";
}

double Simulator::getSimulationTime() const {
    return simulationTime;
}

void Simulator::updateProjectile() {
    // 로그 기록
    logAndPrint(std::cout, "Time: " + std::to_string(simulationTime) +
        ", Position: (" + std::to_string(projectile.getPosition().x) + ", " +
        std::to_string(projectile.getPosition().y) + ", " +
        std::to_string(projectile.getPosition().z) + ")"
    );

    // 중력 재적용
    Vector3<double> gravity(0.0, -projectile.getMass() * Constants<double>::GRAVITY, 0.0);
    projectile.applyForce(gravity);

    // 발사체 업데이트
    projectile.update(tInc);

    // 발사체가 바닥을 통과하지 않도록 바닥의 높이를 적용
    if (projectile.getPosition().y < floorHeight) {
        Vector3<double> pos = projectile.getPosition();
        pos.y = floorHeight;
        projectile.setPosition(pos);
    }
}

bool Simulator::checkCollision() const {
    // 목표물의 절반 크기 계산
    double halfLength = Length / 2.0;
    double halfWidth = Width / 2.0;
    double halfHeight = Height / 2.0;

    // 목표물의 중심 좌표
    Vector3<double> targetCenter = target.getPosition() + Vector3<double>(halfLength, halfHeight, halfWidth);

    // 발사체 위치와 목표물 범위 내에 있는지 확인
    Vector3<double> projPos = projectile.getPosition();
    if (projPos.y <= floorHeight) {
        return (projPos.x >= targetCenter.x - halfLength && projPos.x <= targetCenter.x + halfLength &&
            projPos.y >= targetCenter.y - halfHeight && projPos.y <= targetCenter.y + halfHeight &&
            projPos.z >= targetCenter.z - halfWidth && projPos.z <= targetCenter.z + halfWidth);
    }
    return false;
}

bool Simulator::isSimulationTimedOut() const {
    return simulationTime > 60.0;  // 60초 초과 시 타임아웃 처리
}

#endif // SIMULATOR_CPP