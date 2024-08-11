#include "Quaternion.h"
#include "Constants.h"
#include <cmath>
#include <stdexcept>

// 기본 생성자
Quaternion::Quaternion(void) : n(0), v(0, 0, 0) {}

// 매개변수가 있는 생성자
Quaternion::Quaternion(float e0, float e1, float e2, float e3) : n(e0), v(e1, e2, e3) {}

// 크기 계산
float Quaternion::Magnitude(void) const {
    return std::sqrt(n * n + v.x * v.x + v.y * v.y + v.z * v.z);
}

// 벡터 부분 반환
Vector Quaternion::GetVector(void) const {
    return v;
}

// 스칼라 부분 반환
float Quaternion::GetScalar(void) const {
    return n;
}

// 쿼터니언 합: += 연산자
Quaternion& Quaternion::operator+=(const Quaternion& q) {
    n += q.n;
    v += q.v;
    return *this;
}

// 쿼터니언 뺄셈: -= 연산자
Quaternion& Quaternion::operator-=(const Quaternion& q) {
    n -= q.n;
    v -= q.v;
    return *this;
}

// 쿼터니언 곱: *= 연산자
Quaternion& Quaternion::operator*=(float s) {
    n *= s;
    v *= s;
    return *this;
}

// 쿼터니언 나눗셈: /= 연산자
Quaternion& Quaternion::operator/=(float s) {
    n /= s;
    v /= s;
    return *this;
}

// 켤레: ~ 연산자
Quaternion Quaternion::operator~(void) const {
    return Quaternion(n, -v.x, -v.y, -v.z);
}

// 쿼터니언 합: + 연산자
Quaternion operator+(const Quaternion& q1, const Quaternion& q2) {
    return Quaternion(
        q1.n + q2.n, 
        q1.v.x + q2.v.x, 
        q1.v.y + q2.v.y, 
        q1.v.z + q2.v.z
    );
}

// 쿼터니언 뺄셈: - 연산자
Quaternion operator-(const Quaternion& q1, const Quaternion& q2) {
    return Quaternion(
        q1.n - q2.n, 
        q1.v.x - q2.v.x, 
        q1.v.y - q2.v.y, 
        q1.v.z - q2.v.z
    );
}

// 쿼터니언 곱: * 연산자
Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
    float new_n = q1.n * q2.n - q1.v.x * q2.v.x - q1.v.y * q2.v.y - q1.v.z * q2.v.z;
    Vector new_v(
        q1.n * q2.v.x + q1.v.x * q2.n + q1.v.y * q2.v.z - q1.v.z * q2.v.y,
        q1.n * q2.v.y - q1.v.x * q2.v.z + q1.v.y * q2.n + q1.v.z * q2.v.x,
        q1.n * q2.v.z + q1.v.x * q2.v.y - q1.v.y * q2.v.x + q1.v.z * q2.n
    );
    return Quaternion(new_n, new_v.x, new_v.y, new_v.z);
}

// 스칼라 곱: * 연산자
Quaternion operator*(const Quaternion& q, float s) {
    return Quaternion(q.n * s, q.v.x * s, q.v.y * s, q.v.z * s);
}

Quaternion operator*(float s, const Quaternion& q) {
    return Quaternion(q.n * s, q.v.x * s, q.v.y * s, q.v.z * s);
}

// 벡터 곱: * 연산자
Quaternion operator*(const Quaternion& q, const Vector& v) {
    return Quaternion(
        -(q.v.x * v.x + q.v.y * v.y + q.v.z * v.z), 
        q.n * v.x + q.v.y * v.z - q.v.z * v.y, 
        q.n * v.y + q.v.z * v.x - q.v.x * v.z, 
        q.n * v.z + q.v.x * v.y - q.v.y * v.x
    );
}

Quaternion operator*(const Vector& v, const Quaternion& q) {
    return Quaternion(
        -(q.v.x * v.x + q.v.y * v.y + q.v.z * v.z), 
        q.n * v.x + q.v.y * v.z - q.v.z * v.y, 
        q.n * v.y + q.v.z * v.x - q.v.x * v.z, 
        q.n * v.z + q.v.x * v.y - q.v.y * v.x
    );
}

// 스칼라 나눗셈: / 연산자
Quaternion operator/(const Quaternion& q, float s) {
    return Quaternion(q.n / s, q.v.x / s, q.v.y / s, q.v.z / s);
}

// QGetAngle: 회전 각도 반환
float Quaternion::QGetAngle(void) const {
    return 2.0f * std::acos(n);
}

// QGetAxis: 회전 축 반환
Vector Quaternion::QGetAxis(void) const {
    float sinThetaOver2 = std::sqrt(1.0f - n * n);
    if (sinThetaOver2 < TOLERANCE) {
        return Vector(1.0f, 0.0f, 0.0f); // 임의의 축 반환
    } else {
        return Vector(v.x / sinThetaOver2, v.y / sinThetaOver2, v.z / sinThetaOver2);
    }
}

// QRotate: 벡터 회전
Vector Quaternion::QRotate(const Vector& v) const {
    Quaternion qVec(0, v.x, v.y, v.z);
    Quaternion qConjugate = ~(*this);
    Quaternion result = (*this) * qVec * qConjugate;
    return result.GetVector();
}

// QVRotate: 벡터를 사용하여 쿼터니언 회전
Quaternion Quaternion::QVRotate(const Vector& axis, float angle) {
    float halfAngle = angle / 2.0f;
    float sinHalfAngle = std::sin(halfAngle);
    return Quaternion(std::cos(halfAngle), axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle);
}

// MakeQFromEulerAngles: 오일러 각도로부터 쿼터니언 생성
Quaternion Quaternion::MakeQFromEulerAngles(float pitch, float yaw, float roll) {
    float halfPitch = DegToRad(pitch) / 2.0f;
    float halfYaw = DegToRad(yaw) / 2.0f;
    float halfRoll = DegToRad(roll) / 2.0f;

    float cosHalfPitch = std::cos(halfPitch);
    float sinHalfPitch = std::sin(halfPitch);
    float cosHalfYaw = std::cos(halfYaw);
    float sinHalfYaw = std::sin(halfYaw);
    float cosHalfRoll = std::cos(halfRoll);
    float sinHalfRoll = std::sin(halfRoll);

    return Quaternion(
        cosHalfPitch * cosHalfYaw * cosHalfRoll + sinHalfPitch * sinHalfYaw * sinHalfRoll,
        sinHalfPitch * cosHalfYaw * cosHalfRoll - cosHalfPitch * sinHalfYaw * sinHalfRoll,
        cosHalfPitch * sinHalfYaw * cosHalfRoll + sinHalfPitch * cosHalfYaw * sinHalfRoll,
        cosHalfPitch * cosHalfYaw * sinHalfRoll - sinHalfPitch * sinHalfYaw * cosHalfRoll
    );
}

// MakeEulerAnglesFromQ: 쿼터니언으로부터 오일러 각도 반환
Vector Quaternion::MakeEulerAnglesFromQ(void) const {
    float pitch = std::atan2(2.0f * (n * v.x + v.y * v.z), 1.0f - 2.0f * (v.x * v.x + v.y * v.y));
    float yaw = std::asin(2.0f * (n * v.y - v.z * v.x));
    float roll = std::atan2(2.0f * (n * v.z + v.x * v.y), 1.0f - 2.0f * (v.y * v.y + v.z * v.z));
    return Vector(RadToDeg(pitch), RadToDeg(yaw), RadToDeg(roll));
}

// 각도 변환 함수: DegToRad, RadToDeg
float DegToRad(float deg) {
    return deg * PI / 180.0f;
}

float RadToDeg(float rad) {
    return rad * 180.0f / PI;
}
