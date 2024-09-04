#ifndef QUATERNION_TPP
#define QUATERNION_TPP

#include "Quaternion.h"

// 사원수 템플릿 메서드 구현

template<typename T>
Quaternion<T>::Quaternion(void) : n(0), v(0, 0, 0) {}

template<typename T>
Quaternion<T>::Quaternion(T e0, T e1, T e2, T e3) : n(e0), v(e1, e2, e3) {}

template<typename T>
Quaternion<T>::Quaternion(const Vector4<T>& vec) : n(vec.w), v(vec.x, vec.y, vec.z) {}

template<typename T>
T Quaternion<T>::magnitude(void) const {
    return std::sqrt(n * n + v.x * v.x + v.y * v.y + v.z * v.z);
}

template<typename T>
void Quaternion<T>::normalize(void) {
    T mag = magnitude();
    if (mag > 0) {
        n /= mag;
        v.x /= mag;
        v.y /= mag;
        v.z /= mag;
    } else {
        throw std::runtime_error("Cannot normalize a quaternion with zero magnitude.");
    }
}

template<typename T>
Vector4<T> Quaternion<T>::toVector4() const {
    return Vector4<T>(v.x, v.y, v.z, n);
}

template<typename T>
Matrix3x3<T> Quaternion<T>::toMatrix3x3() const {
    Matrix3x3<T> matrix;
    T xx = v.x * v.x;
    T yy = v.y * v.y;
    T zz = v.z * v.z;
    T xy = v.x * v.y;
    T xz = v.x * v.z;
    T yz = v.y * v.z;
    T wx = n * v.x;
    T wy = n * v.y;
    T wz = n * v.z;

    matrix.e11 = 1.0 - 2.0 * (yy + zz);
    matrix.e12 = 2.0 * (xy - wz);
    matrix.e13 = 2.0 * (xz + wy);

    matrix.e21 = 2.0 * (xy + wz);
    matrix.e22 = 1.0 - 2.0 * (xx + zz);
    matrix.e23 = 2.0 * (yz - wx);

    matrix.e31 = 2.0 * (xz - wy);
    matrix.e32 = 2.0 * (yz + wx);
    matrix.e33 = 1.0 - 2.0 * (xx + yy);

    return matrix;
}

template<typename T>
Matrix4x4<T> Quaternion<T>::toMatrix4x4() const {
    Matrix4x4<T> matrix;
    T xx = v.x * v.x;
    T yy = v.y * v.y;
    T zz = v.z * v.z;
    T xy = v.x * v.y;
    T xz = v.x * v.z;
    T yz = v.y * v.z;
    T wx = n * v.x;
    T wy = n * v.y;
    T wz = n * v.z;

    matrix.e11 = 1.0 - 2.0 * (yy + zz);
    matrix.e12 = 2.0 * (xy - wz);
    matrix.e13 = 2.0 * (xz + wy);
    matrix.e14 = 0.0;

    matrix.e21 = 2.0 * (xy + wz);
    matrix.e22 = 1.0 - 2.0 * (xx + zz);
    matrix.e23 = 2.0 * (yz - wx);
    matrix.e24 = 0.0;

    matrix.e31 = 2.0 * (xz - wy);
    matrix.e32 = 2.0 * (yz + wx);
    matrix.e33 = 1.0 - 2.0 * (xx + yy);
    matrix.e34 = 0.0;

    matrix.e41 = 0.0;
    matrix.e42 = 0.0;
    matrix.e43 = 0.0;
    matrix.e44 = 1.0;

    return matrix;
}

template<typename T>
Quaternion<T> Quaternion<T>::fromAngularVelocity(const Vector3<T>& angularVelocity, T deltaTime) {
    T angle = angularVelocity.magnitude() * deltaTime;
    if (angle < std::numeric_limits<T>::epsilon()) {
        return Quaternion<T>(1, 0, 0, 0);
    }

    Vector3<T> axis = angularVelocity;
    axis.normalize();
    T halfAngle = angle / static_cast<T>(2.0);
    T sinHalfAngle = std::sin(halfAngle);

    return Quaternion<T>(std::cos(halfAngle), axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle);
}

// QGetAngle: 회전 각도 반환
template<typename T>
T Quaternion<T>::qGetAngle(void) const {
    return static_cast<T>(2.0) * std::acos(n);
}

// QGetAxis: 회전 축 반환
template<typename T>
Vector3<T> Quaternion<T>::qGetAxis(void) const {
    T sinThetaOver2 = std::sqrt(static_cast<T>(1.0) - n * n);
    if (sinThetaOver2 < static_cast<T>(1e-6)) {
        return Vector3<T>(static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0)); // 임의의 축 반환
    } else {
        return Vector3<T>(v.x / sinThetaOver2, v.y / sinThetaOver2, v.z / sinThetaOver2);
    }
}

// QRotate: 벡터 회전
template<typename T>
Vector3<T> Quaternion<T>::qRotate(const Vector3<T>& v) const {
    Quaternion<T> qVec(static_cast<T>(0), v.x, v.y, v.z);
    Quaternion<T> qConjugate = ~(*this);
    Quaternion<T> result = (*this) * qVec * qConjugate;
    return result.getVector();
}

// QVRotate: 벡터를 사용하여 쿼터니언 회전
template<typename T>
Quaternion<T> Quaternion<T>::qVRotate(const Vector3<T>& axis, T angle) {
    T halfAngle = angle / static_cast<T>(2.0);
    T sinHalfAngle = std::sin(halfAngle);
    return Quaternion<T>(std::cos(halfAngle), axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle);
}

template<typename T>
Vector3<T> Quaternion<T>::getVector(void) const {
    return v;
}

template<typename T>
T Quaternion<T>::getScalar(void) const {
    return n;
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator+=(const Quaternion& q) {
    n += q.n;
    v += q.v;
    return *this;
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator-=(const Quaternion& q) {
    n -= q.n;
    v -= q.v;
    return *this;
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator*=(T s) {
    n *= s;
    v *= s;
    return *this;
}

template<typename T>
Quaternion<T>& Quaternion<T>::operator/=(T s) {
    n /= s;
    v /= s;
    return *this;
}

template<typename T>
Quaternion<T> Quaternion<T>::makeQFromEulerAngles(T pitch, T yaw, T roll) {
    T halfPitch = Angle::degToRad(pitch) / static_cast<T>(2.0);
    T halfYaw = Angle::degToRad(yaw) / static_cast<T>(2.0);
    T halfRoll = Angle::degToRad(roll) / static_cast<T>(2.0);

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

template<typename T>
Vector3<T> Quaternion<T>::makeEulerAnglesFromQ(void) const {
    T pitch = std::atan2(static_cast<T>(2.0) * (n * v.x + v.y * v.z), static_cast<T>(1.0) - static_cast<T>(2.0) * (v.x * v.x + v.y * v.y));
    T yaw = std::asin(static_cast<T>(2.0) * (n * v.y - v.z * v.x));
    T roll = std::atan2(static_cast<T>(2.0) * (n * v.z + v.x * v.y), static_cast<T>(1.0) - static_cast<T>(2.0) * (v.y * v.y + v.z * v.z));
    
    return Vector3<T>(Angle::radToDeg(pitch), Angle::radToDeg(yaw), Angle::radToDeg(roll));
}


template<typename T>
Quaternion<T> Quaternion<T>::applyRotationOrder(const std::string& order, const Vector3<T>& angles) const {
    Quaternion q = *this;
    for (char axis : order) {
        switch (axis) {
            case 'x':
                q = q * qVRotate(Vector3<T>(static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0)), angles.x);
                break;
            case 'y':
                q = q * qVRotate(Vector3<T>(static_cast<T>(0.0), static_cast<T>(1.0), static_cast<T>(0.0)), angles.y);
                break;
            case 'z':
                q = q * qVRotate(Vector3<T>(static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0)), angles.z);
                break;
            default:
                throw std::invalid_argument("Invalid rotation order");
        }
    }
    return q;
}

template<typename T>
Quaternion<T> operator+(const Quaternion<T>& q1, const Quaternion<T>& q2) {
    return Quaternion<T>(q1.n + q2.n, q1.v.x + q2.v.x, q1.v.y + q2.v.y, q1.v.z + q2.v.z);
}

template<typename T>
Quaternion<T> operator-(const Quaternion<T>& q1, const Quaternion<T>& q2) {
    return Quaternion<T>(q1.n - q2.n, q1.v.x - q2.v.x, q1.v.y - q2.v.y, q1.v.z - q2.v.z);
}

template<typename T>
Quaternion<T> operator*(const Quaternion<T>& q1, const Quaternion<T>& q2) {
    T new_n = q1.n * q2.n - q1.v.x * q2.v.x - q1.v.y * q2.v.y - q1.v.z * q2.v.z;
    Vector3<T> new_v(
        q1.n * q2.v.x + q1.v.x * q2.n + q1.v.y * q2.v.z - q1.v.z * q2.v.y,
        q1.n * q2.v.y - q1.v.x * q2.v.z + q1.v.y * q2.n + q1.v.z * q2.v.x,
        q1.n * q2.v.z + q1.v.x * q2.v.y - q1.v.y * q2.v.x + q1.v.z * q2.n
    );
    return Quaternion<T>(new_n, new_v.x, new_v.y, new_v.z);
}

template<typename T>
Quaternion<T> operator*(const Quaternion<T>& q, T s) {
    return Quaternion<T>(q.n * s, q.v.x * s, q.v.y * s, q.v.z * s);
}

template<typename T>
Quaternion<T> operator*(T s, const Quaternion<T>& q) {
    return Quaternion<T>(q.n * s, q.v.x * s, q.v.y * s, q.v.z * s);
}

template<typename T>
Vector3<T> operator*(const Matrix3x3<T>& m, const Vector3<T>& v) {
    return Vector3<T>(
        m.e11 * v.x + m.e12 * v.y + m.e13 * v.z,
        m.e21 * v.x + m.e22 * v.y + m.e23 * v.z,
        m.e31 * v.x + m.e32 * v.y + m.e33 * v.z
    );
}

template<typename T>
Vector4<T> operator*(const Matrix4x4<T>& m, const Vector4<T>& v) {
    return Vector4<T>(
        m.e11 * v.x + m.e12 * v.y + m.e13 * v.z + m.e14 * v.w,
        m.e21 * v.x + m.e22 * v.y + m.e23 * v.z + m.e24 * v.w,
        m.e31 * v.x + m.e32 * v.y + m.e33 * v.z + m.e34 * v.w,
        m.e41 * v.x + m.e42 * v.y + m.e43 * v.z + m.e44 * v.w
    );
}

template<typename T>
Quaternion<T> operator/(const Quaternion<T>& q, T s) {
    return Quaternion<T>(q.n / s, q.v.x / s, q.v.y / s, q.v.z / s);
}

template<typename T>
Quaternion<T> operator/(const Quaternion<T>& q1, const Quaternion<T>& q2) {
    Quaternion<T> q2_conjugate = ~q2;
    T denom = q2 * q2_conjugate;
    return (q1 * q2_conjugate) / denom;
}

template<typename T>
Quaternion<T> Quaternion<T>::operator~(void) const {
    return Quaternion<T>(n, -v.x, -v.y, -v.z);
}

// 템플릿 명시적 인스턴스화 (필요한 경우 사용)
template class Quaternion<float>;
template class Quaternion<double>;

#endif // QUATERNION_TPP
