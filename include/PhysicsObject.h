#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix3x3.h"

class PhysicsObject {
public:
    PhysicsObject();

    // Position 접근자
    Vector3<double> getPosition() const { return position; }
    void setPosition(const Vector3<double>& pos) { position = pos; }

    // Velocity 접근자
    Vector3<double> getVelocity() const { return velocity; }
    void setVelocity(const Vector3<double>& vel) { velocity = vel; }

    // Mass 접근자
    double getMass() const { return mass; }
    void setMass(double m) { mass = m; calculateInertiaTensor(); }

    // Scale 접근자
    Vector3<double> getScale() const { return scale; }
    void setScale(const Vector3<double>& sc) { scale = sc; calculateInertiaTensor(); }

    // GroundHeight 접근자
    double getGroundHeight() const { return groundHeight; }
    void setGroundHeight(double gh) { groundHeight = gh; }

    void applyForce(const Vector3<double>& newForce);
    void applyTorque(const Vector3<double>& torque);
    void updatePosition(double deltaTime);
    void updateRotation(double deltaTime);
    void update(double deltaTime);
    void onCollision(PhysicsObject& other);
    void onGroundCollision(); // 바닥 충돌 처리 함수

private:
    Vector3<double> position;
    Quaternion<double> orientation;
    Vector3<double> scale;
    double mass;
    Vector3<double> velocity;
    Vector3<double> acceleration;
    Vector3<double> force;
    Matrix3x3<double> inertiaTensor;        // 관성 텐서
    Matrix3x3<double> inverseInertiaTensor; // 역관성 텐서
    Vector3<double> angularVelocity;        // 각속도
    double groundHeight;                    // 바닥 높이

    void calculateInertiaTensor();          // 관성 텐서를 계산하는 함수
};

#endif // PHYSICSOBJECT_H