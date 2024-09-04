#ifndef PHYSICSOBJECT_CPP
#define PHYSICSOBJECT_CPP

#include "PhysicsObject.h"
#include "Constants.h"

// 기본 생성자
PhysicsObject::PhysicsObject()
    : position(0.0, 0.0, 0.0),
    orientation(1.0, 0.0, 0.0, 0.0),
    scale(1.0, 1.0, 1.0),
    mass(1.0),
    velocity(0.0, 0.0, 0.0),
    acceleration(0.0, 0.0, 0.0),
    force(0.0, 0.0, 0.0),
    inertiaTensor(Matrix3x3<double>::identity()),
    inverseInertiaTensor(Matrix3x3<double>::identity()),
    angularVelocity(0.0, 0.0, 0.0),
    groundHeight(0.0)
{
    calculateInertiaTensor();
}

// 힘을 적용하는 함수
void PhysicsObject::applyForce(const Vector3<double>& newForce) {
    force += newForce;
}

// 토크를 적용하는 함수
void PhysicsObject::applyTorque(const Vector3<double>& torque) {
    // 각가속도 = 역관성 텐서 * 토크
    Vector3<double> angularAcceleration = inverseInertiaTensor * torque;
    angularVelocity += angularAcceleration; // 각속도 업데이트
}

// 위치 업데이트 함수
void PhysicsObject::updatePosition(double deltaTime) {
    // 중력 가속도 적용
    Vector3<double> gravityForce(0.0, -mass * Constants<double>::GRAVITY, 0.0);
    acceleration = (force + gravityForce) / mass;

    // 속도와 위치 업데이트
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;

    // 외력 초기화
    force = Vector3<double>(0.0, 0.0, 0.0);
}

// 회전 업데이트 함수
void PhysicsObject::updateRotation(double deltaTime) {
    Quaternion<double> deltaRotation = Quaternion<double>::fromAngularVelocity(angularVelocity, deltaTime);
    orientation = deltaRotation * orientation;
    orientation.normalize();
}

// 전체 상태 업데이트 함수
void PhysicsObject::update(double deltaTime) {
    updatePosition(deltaTime);
    updateRotation(deltaTime);
}

// 충돌 처리 함수 (단순화된 예시)
void PhysicsObject::onCollision(PhysicsObject& other) {
    double restitution = 0.8;
    velocity = -velocity * restitution;
    other.velocity = -other.velocity * restitution;
}

// 관성 텐서 계산 함수 (구형 또는 박스형 객체에 대한 관성 텐서 계산)
void PhysicsObject::calculateInertiaTensor() {
    if (scale.x == scale.y && scale.y == scale.z) {
        // 구형 객체에 대한 관성 모멘트 공식: I = (2/5) * m * r^2
        double radius = scale.x; // 구형 객체의 반지름
        double inertia = (2.0 / 5.0) * mass * radius * radius;

        // 관성 텐서를 대각 행렬로 설정 (구형 객체의 경우)
        inertiaTensor = Matrix3x3<double>::identity() * inertia;
    }
    else {
        // 박스형 객체에 대한 관성 모멘트 공식: I = (1/12) * m * (w^2 + h^2)
        double I_x = (1.0 / 12.0) * mass * (scale.y * scale.y + scale.z * scale.z);
        double I_y = (1.0 / 12.0) * mass * (scale.x * scale.x + scale.z * scale.z);
        double I_z = (1.0 / 12.0) * mass * (scale.x * scale.x + scale.y * scale.y);

        // 관성 텐서를 대각 행렬로 설정 (박스형 객체의 경우)
        inertiaTensor = Matrix3x3<double>(
            I_x, 0.0, 0.0,
            0.0, I_y, 0.0,
            0.0, 0.0, I_z
        );
    }

    // 역관성 텐서 계산
    inverseInertiaTensor = inertiaTensor.inverse();
}

// 바닥 충돌 처리 함수
void PhysicsObject::onGroundCollision() {
    if (position.y <= groundHeight) {
        position.y = groundHeight; // 바닥에 붙임
        velocity.y = -velocity.y * 0.8; // 반발 계수를 사용한 속도 반전
    }
}

#endif // PHYSICSOBJECT_CPP