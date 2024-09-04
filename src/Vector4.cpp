#ifndef VECTOR4_CPP
#define VECTOR4_CPP

#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Angle.h"
#include <stdexcept>  // 예외 처리를 위해 필요

// 기본 생성자
template<typename T>
Vector4<T>::Vector4(void) : x(0), y(0), z(0), w(0) {}

// 매개변수가 있는 생성자
template<typename T>
Vector4<T>::Vector4(T xi, T yi, T zi, T wi) : x(xi), y(yi), z(zi), w(wi) {}

// Vector4 to Vector3 변환
template<typename T>
Vector3<T> Vector4<T>::toVector3() const {
    if (w != 0) {
        return Vector3<T>(x / w, y / w, z / w);
    }
    return Vector3<T>(x, y, z);
}

// Vector4 to Quaternion 변환
template<typename T>
Quaternion<T> Vector4<T>::toQuaternion() const {
    return Quaternion<T>(w, x, y, z);
}

// Vector4를 대각 행렬로 변환
template<typename T>
Matrix3x3<T> Vector4<T>::toMatrix3x3() const {
    Matrix3x3<T> mat;
    // w 성분을 버리고 x, y, z 성분만 대각 행렬로 변환
    mat.e11 = x;
    mat.e22 = y;
    mat.e33 = z;

    // 나머지 비대각선 요소는 0으로 설정
    mat.e12 = mat.e13 = mat.e21 = mat.e23 = mat.e31 = mat.e32 = 0.0;

    return mat;
}

// Vector4를 대각 행렬로 변환
template<typename T>
Matrix4x4<T> Vector4<T>::toMatrix4x4() const {
    Matrix4x4<T> mat;
    mat.e11 = x;
    mat.e22 = y;
    mat.e33 = z;
    mat.e44 = w;
    return mat;
}

// 벡터의 크기(길이)를 계산
template<typename T>
T Vector4<T>::magnitude(void) const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

// 벡터를 정규화
template<typename T>
void Vector4<T>::normalize(void) {
    T m = magnitude();
    if (m > static_cast<T>(1e-6)) {
        x /= m;
        y /= m;
        z /= m;
        w /= m;
    }
    else {
        x = y = z = w = static_cast<T>(0.0);
    }
}

// 벡터의 방향을 반대로
template<typename T>
void Vector4<T>::reverse(void) {
    x = -x;
    y = -y;
    z = -z;
    w = -w;
}

// 벡터 덧셈 대입 연산자
template<typename T>
Vector4<T>& Vector4<T>::operator+=(const Vector4& u) {
    x += u.x;
    y += u.y;
    z += u.z;
    w += u.w;
    return *this;
}

// 벡터 뺄셈 대입 연산자
template<typename T>
Vector4<T>& Vector4<T>::operator-=(const Vector4& u) {
    x -= u.x;
    y -= u.y;
    z -= u.z;
    w -= u.w;
    return *this;
}

// 스칼라 곱셈 대입 연산자
template<typename T>
Vector4<T>& Vector4<T>::operator*=(T s) {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
}

// 스칼라 나눗셈 대입 연산자
template<typename T>
Vector4<T>& Vector4<T>::operator/=(T s) {
    if (s == static_cast<T>(0)) {
        throw std::runtime_error("Division by zero in Vector4::operator/=");
    }
    x /= s;
    y /= s;
    z /= s;
    w /= s;
    return *this;
}

// 음수 벡터 연산자
template<typename T>
Vector4<T> Vector4<T>::operator-(void) const {
    return Vector4(-x, -y, -z, -w);
}

// 템플릿 함수들의 정의
template<typename T>
Vector4<T> operator+(const Vector4<T>& u, const Vector4<T>& v) {
    return Vector4<T>(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

template<typename T>
Vector4<T> operator-(const Vector4<T>& u, const Vector4<T>& v) {
    return Vector4<T>(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

// Vector4에 대한 외적 연산자
template<typename T>
Vector4<T> operator^(const Vector4<T>& u, const Vector4<T>& v) {
    return Vector4<T>(
        u.y * v.z - u.z * v.y,  // x 성분 계산
        u.z * v.x - u.x * v.z,  // y 성분 계산
        u.x * v.y - u.y * v.x,  // z 성분 계산
        0.0                     // w 성분은 0으로 설정
    );
}

// 내적 연산
template<typename T>
T operator*(const Vector4<T>& u, const Vector4<T>& v) {
    return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
}

// 스칼라 곱셈 연산자
template<typename T>
Vector4<T> operator*(const Vector4<T>& u, T s) {
    return Vector4<T>(u.x * s, u.y * s, u.z * s, u.w * s);
}

template<typename T>
Vector4<T> operator*(T s, const Vector4<T>& u) {
    return Vector4<T>(u.x * s, u.y * s, u.z * s, u.w * s);
}

// 스칼라 나눗셈 연산자
template<typename T>
Vector4<T> operator/(const Vector4<T>& u, T s) {
    if (s == static_cast<T>(0)) {
        throw std::runtime_error("Division by zero in Vector4::operator/");
    }
    return Vector4<T>(u.x / s, u.y / s, u.z / s, u.w / s);
}

// Pitch 회전 (X축 기준 회전)
template<typename T>
Vector4<T> Vector4<T>::pitch(T angle) const {
    T rad = Angle::degToRad(angle);  // 각도를 라디안으로 변환
    T cosAngle = std::cos(rad);
    T sinAngle = std::sin(rad);
    return Vector4(x, y * cosAngle - z * sinAngle, y * sinAngle + z * cosAngle, w); // w 성분은 그대로 유지
}

// Yaw 회전 (Y축 기준 회전)
template<typename T>
Vector4<T> Vector4<T>::yaw(T angle) const {
    T rad = Angle::degToRad(angle);  // 각도를 라디안으로 변환
    T cosAngle = std::cos(rad);
    T sinAngle = std::sin(rad);
    return Vector4(x * cosAngle + z * sinAngle, y, -x * sinAngle + z * cosAngle, w); // w 성분은 그대로 유지
}

// Roll 회전 (Z축 기준 회전)
template<typename T>
Vector4<T> Vector4<T>::roll(T angle) const {
    T rad = Angle::degToRad(angle);  // 각도를 라디안으로 변환
    T cosAngle = std::cos(rad);
    T sinAngle = std::sin(rad);
    return Vector4(x * cosAngle - y * sinAngle, x * sinAngle + y * cosAngle, z, w); // w 성분은 그대로 유지
}

// 회전 순서에 따른 회전 적용
template<typename T>
Vector4<T> Vector4<T>::rotation(T pitch, T yaw, T roll, const std::string& order) const {
    Vector4<T> result = *this;  // 현재 벡터 값을 복사

    for (char axis : order) {
        switch (axis) {
        case 'x':
            result = result.pitch(pitch);  // X축 기준 회전
            break;
        case 'y':
            result = result.yaw(yaw);      // Y축 기준 회전
            break;
        case 'z':
            result = result.roll(roll);    // Z축 기준 회전
            break;
        default:
            throw std::invalid_argument("Invalid rotation axis");
        }
    }

    return result;  // 회전된 결과를 반환
}

// 스칼라 삼중곱
template<typename T>
T scalarTripleProduct(const Vector4<T>& u, const Vector4<T>& v, const Vector4<T>& w) {
    return u * (v ^ w);  // (u dot (v cross w))
}

// 벡터 삼중곱
template<typename T>
Vector4<T> vectorTripleProduct(const Vector4<T>& u, const Vector4<T>& v, const Vector4<T>& w) {
    return u ^ (v ^ w);  // u cross (v cross w)
}

//// 중복된 정의 방지를 위한 매크로 설정
//#ifndef MATRIX_VECTOR4_MULT_DEFINED
//#define MATRIX_VECTOR4_MULT_DEFINED
//
//// Matrix4x4와 Vector4의 곱셈 연산 정의
//template<typename T>
//Vector4<T> operator*(const Matrix4x4<T>& m, const Vector4<T>& v) {
//    return Vector4<T>(
//        m.e11 * v.x + m.e12 * v.y + m.e13 * v.z + m.e14 * v.w,  // 첫 번째 성분
//        m.e21 * v.x + m.e22 * v.y + m.e23 * v.z + m.e24 * v.w,  // 두 번째 성분
//        m.e31 * v.x + m.e32 * v.y + m.e33 * v.z + m.e34 * v.w,  // 세 번째 성분
//        m.e41 * v.x + m.e42 * v.y + m.e43 * v.z + m.e44 * v.w   // 네 번째 성분
//    );
//}
//
//#endif // MATRIX_VECTOR4_MULT_DEFINED

//// 명시적 인스턴스화 보호
//#ifndef OPERATOR_MULT_DEFINED
//#define OPERATOR_MULT_DEFINED
//
//// 템플릿 명시적 인스턴스화 (필요한 경우 사용)
//template class Vector4<double>;
//template Vector4<double> operator/(const Vector4<double>& u, double s);
//template Vector4<double> operator*(const Vector4<double>& u, double s);
//template Vector4<double> operator*(double s, const Vector4<double>& u);
//template Vector4<double> operator*(const Matrix4x4<double>& m, const Vector4<double>& v);
//
//#endif // OPERATOR_MULT_DEFINED

#endif // VECTOR4_CPP