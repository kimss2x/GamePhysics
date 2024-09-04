#include <iostream>
#include <limits>
#include "Simulator.h"
#include "Constants.h"

Simulator::Simulator(double Vm, double Alpha, double Gamma, double Yb, double X, double Z, double Length, double Width, double Height, double tInc)
    : Vm(Vm), Alpha(Alpha), Gamma(Gamma), Yb(Yb), X(X), Z(Z), Length(Length), Width(Width), Height(Height), simulationTime(0.0), tInc(tInc), status(0) {}

void Simulator::initialize() {
    // 대포 발사체 초기화
    projectile.setPosition(Vector3<double>(0.0, Yb, 0.0));
    projectile.setMass(1.0);

    // 초기 속도 설정
    Vector3<double> initialVelocity = Vector3<double>(Vm, 0.0, 0.0);
    initialVelocity = initialVelocity.Pitch(Alpha);
    initialVelocity = initialVelocity.Yaw(Gamma);
    projectile.setVelocity(initialVelocity);

    // 중력 적용
    projectile.ApplyForce(Vector3<double>(0.0, -projectile.getMass() * Constants<double>::GRAVITY, 0.0));

    // 목표물 초기화
    target.setPosition(Vector3<double>(X, 0.0, Z));
    target.setMass(100.0);  // 임의의 질량
    target.setScale(Vector3<double>(Length, Height, Width));
}


int Simulator::runSimulationStep() {
    // 시간에 따른 위치 계산
    updateProjectile();

    // 충돌 또는 시간 초과 여부 확인
    if (checkCollision()) {
        status = 1;  // Direct Hit
    } else if (isSimulationTimedOut()) {
        status = 3;  // Simulation Timed Out
    } else {
        simulationTime += tInc;
    }
    return status;
}

std::string Simulator::getSimulationStatus() const {
    std::string positionStr = "Time: " + std::to_string(simulationTime) + "s, Position: " + 
                               std::to_string(projectile.getPosition().x) + ", " +
                               std::to_string(projectile.getPosition().y) + ", " +
                               std::to_string(projectile.getPosition().z);
    return positionStr;
}

void Simulator::updateProjectile() {
    projectile.Update(tInc);
}

bool Simulator::checkCollision() const {
    if (projectile.getPosition().y <= 0) {
        if (projectile.getPosition().x >= X && projectile.getPosition().x <= (X + Length) &&
            projectile.getPosition().z >= Z && projectile.getPosition().z <= (Z + Width)) {
            return true;
        }
        return false;
    }
    return false;
}

bool Simulator::isSimulationTimedOut() const {
    return simulationTime > 60;
}
