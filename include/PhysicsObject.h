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
    void setMass(double m) { mass = m; }

    // Scale 접근자
    Vector3<double> getScale() const { return scale; }
    void setScale(const Vector3<double>& sc) { scale = sc; }

    void ApplyForce(const Vector3<double>& newForce);
    void ApplyTorque(const Vector3<double>& torque);
    void UpdatePosition(double deltaTime);
    void UpdateRotation(double deltaTime);
    void Update(double deltaTime);
    void OnCollision(PhysicsObject& other);

private:
    Vector3<double> position;
    Quaternion<double> orientation;
    Vector3<double> scale;
    double mass;
    Vector3<double> velocity;
    Vector3<double> acceleration;
    Vector3<double> force;
    Matrix3x3<double> inertiaTensor;
    Vector3<double> angularVelocity;
};

#endif // PHYSICSOBJECT_H
