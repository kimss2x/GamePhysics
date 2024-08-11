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
      angularVelocity(0.0, 0.0, 0.0)
{}

// 힘을 적용하는 함수
void PhysicsObject::ApplyForce(const Vector3<double>& newForce) {
    force += newForce;
}

// 토크를 적용하는 함수
void PhysicsObject::ApplyTorque(const Vector3<double>& torque) {
    // 각가속도 업데이트
    Vector3<double> angularAcceleration = inertiaTensor.inverse() * torque;
    angularVelocity += angularAcceleration;
}

// 위치 업데이트 함수
void PhysicsObject::UpdatePosition(double deltaTime) {
    acceleration = force / mass;  // F = ma 에 따라 가속도 계산
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}

// 회전 업데이트 함수
void PhysicsObject::UpdateRotation(double deltaTime) {
    Quaternion<double> deltaRotation = Quaternion<double>::fromAngularVelocity(angularVelocity, deltaTime);
    orientation = deltaRotation * orientation;
    orientation.Normalize();
}

// 전체 상태 업데이트 함수
void PhysicsObject::Update(double deltaTime) {
    UpdatePosition(deltaTime);
    UpdateRotation(deltaTime);

    // 힘 초기화 (매 프레임마다 새로운 힘 적용)
    force = Vector3<double>(0.0, 0.0, 0.0);
}

// 충돌 처리 함수
void PhysicsObject::OnCollision(PhysicsObject& other) {
    // 간단한 충돌 반응 (반사 처리)
    velocity = -velocity;
    other.velocity = -other.velocity;
}
