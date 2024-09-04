#ifndef VECTOR3_CPP
#define VECTOR3_CPP

#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Constants.h"
#include "Angle.h"
#include <stdexcept>  // 예외 처리를 위해 필요

// 생성자
template<typename T>
Vector3<T>::Vector3(void) : x(0), y(0), z(0) {}

// 생성자
template<typename T>
Vector3<T>::Vector3(T xi, T yi, T zi) : x(xi), y(yi), z(zi) {}

// Vector3를 Vector4로 변환
template<typename T>
Vector4<T> Vector3<T>::toVector4(T w) const {
    return Vector4<T>(x, y, z, w);
}

// Vector3를 회전 축으로 하는 Quaternion으로 변환
template<typename T>
Quaternion<T> Vector3<T>::toQuaternion(T angle) const {
    Vector3<T> axis = *this;
    axis.normalize();
    T halfAngle = angle / 2.0;
    T sinHalfAngle = std::sin(halfAngle);
    T cosHalfAngle = std::cos(halfAngle);

    return Quaternion<T>(cosHalfAngle, axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle);
}

template<typename T>
Matrix3x3<T> Vector3<T>::toMatrix3x3() const {
    Matrix3x3<T> mat;
    mat.e11 = x;
    mat.e22 = y;
    mat.e33 = z;
    return mat;
}

template<typename T>
Matrix4x4<T> Vector3<T>::toMatrix4x4() const {
    Matrix4x4<T> mat;
    mat.e11 = x;
    mat.e22 = y;
    mat.e33 = z;
    mat.e44 = 1;
    return mat;
}

// 벡터의 크기 계산
template<typename T>
T Vector3<T>::magnitude(void) const {
    return std::sqrt(x * x + y * y + z * z);
}

// 벡터를 정규화
template<typename T>
void Vector3<T>::normalize(void) {
    T m = magnitude();
    if (m > static_cast<T>(1e-6)) {
        x /= m;
        y /= m;
        z /= m;
    }
    else {
        x = y = z = static_cast<T>(0.0);
    }
}

// 벡터의 방향을 반대로
template<typename T>
void Vector3<T>::reverse(void) {
    x = -x;
    y = -y;
    z = -z;
}

// 벡터 덧셈 대입 연산자
template<typename T>
Vector3<T>& Vector3<T>::operator+=(const Vector3& u) {
    x += u.x;
    y += u.y;
    z += u.z;
    return *this;
}

// 벡터 뺄셈 대입 연산자
template<typename T>
Vector3<T>& Vector3<T>::operator-=(const Vector3& u) {
    x -= u.x;
    y -= u.y;
    z -= u.z;
    return *this;
}

// 스칼라 곱셈 대입 연산자
template<typename T>
Vector3<T>& Vector3<T>::operator*=(T s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

// 스칼라 나눗셈 대입 연산자
template<typename T>
Vector3<T>& Vector3<T>::operator/=(T s) {
    if (s == static_cast<T>(0)) {
        throw std::runtime_error("Division by zero in Vector3::operator/=");
    }
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

// 음수 벡터 연산자
template<typename T>
Vector3<T> Vector3<T>::operator-(void) const {
    return Vector3(-x, -y, -z);
}

// 벡터 덧셈 연산자
template<typename T>
Vector3<T> operator+(const Vector3<T>& u, const Vector3<T>& v) {
    return Vector3<T>(u.x + v.x, u.y + v.y, u.z + v.z);
}

// 벡터 뺄셈 연산자
template<typename T>
Vector3<T> operator-(const Vector3<T>& u, const Vector3<T>& v) {
    return Vector3<T>(u.x - v.x, u.y - v.y, u.z - v.z);
}

// 외적
template<typename T>
Vector3<T> operator^(const Vector3<T>& u, const Vector3<T>& v) {
    return Vector3<T>(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

// 내적
template<typename T>
T operator*(const Vector3<T>& u, const Vector3<T>& v) {
    return (u.x * v.x + u.y * v.y + u.z * v.z);
}

// 스칼라 곱셈 연산자
template<typename T>
Vector3<T> operator*(const Vector3<T>& u, T s) {
    return Vector3<T>(u.x * s, u.y * s, u.z * s);
}

template<typename T>
Vector3<T> operator*(T s, const Vector3<T>& u) {
    return Vector3<T>(u.x * s, u.y * s, u.z * s);
}

// 스칼라 나눗셈 연산자
template<typename T>
Vector3<T> operator/(const Vector3<T>& u, T s) {
    if (s == static_cast<T>(0)) {
        throw std::runtime_error("Division by zero in Vector3::operator/=");
    }
    return Vector3<T>(u.x / s, u.y / s, u.z / s);
}

// Pitch 회전 (X축 기준 회전)
template<typename T>
Vector3<T> Vector3<T>::pitch(T angle) const {
    T rad = Angle::degToRad(angle);  // 각도를 라디안으로 변환
    T cosAngle = std::cos(rad);
    T sinAngle = std::sin(rad);
    return Vector3(x, y * cosAngle - z * sinAngle, y * sinAngle + z * cosAngle);
}

// Yaw 회전 (Y축 기준 회전)
template<typename T>
Vector3<T> Vector3<T>::yaw(T angle) const {
    T rad = Angle::degToRad(angle);  // 각도를 라디안으로 변환
    T cosAngle = std::cos(rad);
    T sinAngle = std::sin(rad);
    return Vector3(x * cosAngle + z * sinAngle, y, -x * sinAngle + z * cosAngle);
}

// Roll 회전 (Z축 기준 회전)
template<typename T>
Vector3<T> Vector3<T>::roll(T angle) const {
    T rad = Angle::degToRad(angle);  // 각도를 라디안으로 변환
    T cosAngle = std::cos(rad);
    T sinAngle = std::sin(rad);
    return Vector3(x * cosAngle - y * sinAngle, x * sinAngle + y * cosAngle, z);
}

// Rotation 함수 - Pitch, Yaw, Roll을 주어진 순서로 회전
template<typename T>
Vector3<T> Vector3<T>::rotation(T pitch, T yaw, T roll, const std::string& order) const {
    Vector3 result = *this;
    for (char axis : order) {
        switch (axis) {
        case 'x':
            result = result.pitch(pitch);
            break;
        case 'y':
            result = result.yaw(yaw);
            break;
        case 'z':
            result = result.roll(roll);
            break;
        default:
            throw std::invalid_argument("Invalid rotation axis");
        }
    }
    return result;
}

// 스칼라 삼중곱
template<typename T>
T scalarTripleProduct(const Vector3<T>& u, const Vector3<T>& v, const Vector3<T>& w) {
    return u * (v ^ w);  // (u dot (v cross w))
}

// 벡터 삼중곱
template<typename T>
Vector3<T> vectorTripleProduct(const Vector3<T>& u, const Vector3<T>& v, const Vector3<T>& w) {
    return u ^ (v ^ w);  // u cross (v cross w)
}

//// 중복된 정의 방지를 위한 매크로 설정
//#ifndef MATRIX_VECTOR3_MULT_DEFINED
//#define MATRIX_VECTOR3_MULT_DEFINED
//
//// Matrix3x3와 Vector3의 곱셈 연산 정의
//template<typename T>
//Vector3<T> operator*(const Matrix3x3<T>& m, const Vector3<T>& v) {
//    return Vector3<T>(
//        m.e11 * v.x + m.e12 * v.y + m.e13 * v.z,  // 첫 번째 성분
//        m.e21 * v.x + m.e22 * v.y + m.e23 * v.z,  // 두 번째 성분
//        m.e31 * v.x + m.e32 * v.y + m.e33 * v.z   // 세 번째 성분
//    );
//}
//
//#endif // MATRIX_VECTOR3_MULT_DEFINED

// 명시적 인스턴스화 보호
#ifndef OPERATOR_MULT_DEFINED
#define OPERATOR_MULT_DEFINED

// 명시적 인스턴스화 추가
template class Vector3<double>;
template Vector3<double> operator+(const Vector3<double>& u, const Vector3<double>& v);
template Vector3<double> operator-(const Vector3<double>& u, const Vector3<double>& v);
template Vector3<double> operator*(const Vector3<double>& u, double s);
template Vector3<double> operator/(const Vector3<double>& u, double s);
template Vector3<double> operator*(const Matrix3x3<double>& m, const Vector3<double>& v);

#endif // OPERATOR_MULT_DEFINED

#endif // VECTOR3_CPP