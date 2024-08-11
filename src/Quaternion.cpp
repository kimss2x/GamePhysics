#include "Quaternion.h"
#include "Constants.h"
#include <cmath>
#include <stdexcept>

// 기본 생성자
template<typename T>
Quaternion<T>::Quaternion(void) : n(0), v(0, 0, 0) {}

// 매개변수가 있는 생성자
template<typename T>
Quaternion<T>::Quaternion(T e0, T e1, T e2, T e3) : n(e0), v(e1, e2, e3) {}

// 크기 계산
template<typename T>
T Quaternion<T>::Magnitude(void) const {
    return std::sqrt(n * n + v.x * v.x + v.y * v.y + v.z * v.z);
}

// 벡터 부분 반환
template<typename T>
Vector3<T> Quaternion<T>::GetVector(void) const {
    return v;
}

// 스칼라 부분 반환
template<typename T>
T Quaternion<T>::GetScalar(void) const {
    return n;
}

// 쿼터니언 합: += 연산자
template<typename T>
Quaternion<T>& Quaternion<T>::operator+=(const Quaternion& q) {
    n += q.n;
    v += q.v;
    return *this;
}

// 쿼터니언 뺄셈: -= 연산자
template<typename T>
Quaternion<T>& Quaternion<T>::operator-=(const Quaternion& q) {
    n -= q.n;
    v -= q.v;
    return *this;
}

// 쿼터니언 곱: *= 연산자
template<typename T>
Quaternion<T>& Quaternion<T>::operator*=(T s) {
    n *= s;
    v *= s;
    return *this;
}

// 쿼터니언 나눗셈: /= 연산자
template<typename T>
Quaternion<T>& Quaternion<T>::operator/=(T s) {
    n /= s;
    v /= s;
    return *this;
}

// 켤레: ~ 연산자
template<typename T>
Quaternion<T> Quaternion<T>::operator~(void) const {
    return Quaternion(n, -v.x, -v.y, -v.z);
}

// QGetAngle: 회전 각도 반환
template<typename T>
T Quaternion<T>::QGetAngle(void) const {
    return static_cast<T>(2.0) * std::acos(n);
}

// QGetAxis: 회전 축 반환
template<typename T>
Vector3<T> Quaternion<T>::QGetAxis(void) const {
    T sinThetaOver2 = std::sqrt(static_cast<T>(1.0) - n * n);
    if (sinThetaOver2 < static_cast<T>(1e-6)) {
        return Vector3<T>(static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0)); // 임의의 축 반환
    } else {
        return Vector3<T>(v.x / sinThetaOver2, v.y / sinThetaOver2, v.z / sinThetaOver2);
    }
}

// QRotate: 벡터 회전
template<typename T>
Vector3<T> Quaternion<T>::QRotate(const Vector3<T>& v) const {
    Quaternion qVec(static_cast<T>(0), v.x, v.y, v.z);
    Quaternion qConjugate = ~(*this);
    Quaternion result = (*this) * qVec * qConjugate;
    return result.GetVector();
}

// QVRotate: 벡터를 사용하여 쿼터니언 회전
template<typename T>
Quaternion<T> Quaternion<T>::QVRotate(const Vector3<T>& axis, T angle) {
    T halfAngle = angle / static_cast<T>(2.0);
    T sinHalfAngle = std::sin(halfAngle);
    return Quaternion(std::cos(halfAngle), axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle);
}

// MakeQFromEulerAngles: 오일러 각도로부터 쿼터니언 생성
template<typename T>
Quaternion<T> Quaternion<T>::MakeQFromEulerAngles(T pitch, T yaw, T roll) {
    T halfPitch = DegToRad(pitch) / static_cast<T>(2.0);
    T halfYaw = DegToRad(yaw) / static_cast<T>(2.0);
    T halfRoll = DegToRad(roll) / static_cast<T>(2.0);

    T cosHalfPitch = std::cos(halfPitch);
    T sinHalfPitch = std::sin(halfPitch);
    T cosHalfYaw = std::cos(halfYaw);
    T sinHalfYaw = std::sin(halfYaw);
    T cosHalfRoll = std::cos(halfRoll);
    T sinHalfRoll = std::sin(halfRoll);

    return Quaternion(
        cosHalfPitch * cosHalfYaw * cosHalfRoll + sinHalfPitch * sinHalfYaw * sinHalfRoll,
        sinHalfPitch * cosHalfYaw * cosHalfRoll - cosHalfPitch * sinHalfYaw * sinHalfRoll,
        cosHalfPitch * sinHalfYaw * cosHalfRoll + sinHalfPitch * cosHalfYaw * sinHalfRoll,
        cosHalfPitch * cosHalfYaw * sinHalfRoll - sinHalfPitch * sinHalfYaw * cosHalfRoll
    );
}

// MakeEulerAnglesFromQ: 쿼터니언으로부터 오일러 각도 반환
template<typename T>
Vector3<T> Quaternion<T>::MakeEulerAnglesFromQ(void) const {
    T pitch = std::atan2(static_cast<T>(2.0) * (n * v.x + v.y * v.z), static_cast<T>(1.0) - static_cast<T>(2.0) * (v.x * v.x + v.y * v.y));
    T yaw = std::asin(static_cast<T>(2.0) * (n * v.y - v.z * v.x));
    T roll = std::atan2(static_cast<T>(2.0) * (n * v.z + v.x * v.y), static_cast<T>(1.0) - static_cast<T>(2.0) * (v.y * v.y + v.z * v.z));
    return Vector3<T>(RadToDeg(pitch), RadToDeg(yaw), RadToDeg(roll));
}

// 회전 순서에 따른 회전 적용
template<typename T>
Quaternion<T> Quaternion<T>::ApplyRotationOrder(const std::string& order, const Vector3<T>& angles) const {
    Quaternion q = *this;
    for (char axis : order) {
        switch (axis) {
            case 'x':
                q = q * QVRotate(Vector3<T>(static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0)), angles.x);
                break;
            case 'y':
                q = q * QVRotate(Vector3<T>(static_cast<T>(0.0), static_cast<T>(1.0), static_cast<T>(0.0)), angles.y);
                break;
            case 'z':
                q = q * QVRotate(Vector3<T>(static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0)), angles.z);
                break;
            default:
                throw std::invalid_argument("Invalid rotation order");
        }
    }
    return q;
}
