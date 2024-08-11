#include "Vector3.h"
#include <cmath>  // M_PI 및 수학 함수 사용을 위해 필요
#include <stdexcept>  // 예외 처리를 위해 필요

// 생성자
template<typename T>
Vector3<T>::Vector3(void) : x(0), y(0), z(0) {}

// 생성자
template<typename T>
Vector3<T>::Vector3(T xi, T yi, T zi) : x(xi), y(yi), z(zi) {}

// 벡터의 크기 계산
template<typename T>
T Vector3<T>::Magnitude(void) const {
    return std::sqrt(x * x + y * y + z * z);
}

// 벡터를 정규화
template<typename T>
void Vector3<T>::Normalize(void) {
    T m = Magnitude();
    if (m <= static_cast<T>(1e-6)) m = static_cast<T>(1.0);
    x /= m;
    y /= m;
    z /= m;

    if (std::fabs(x) < static_cast<T>(1e-6)) x = static_cast<T>(0.0);
    if (std::fabs(y) < static_cast<T>(1e-6)) y = static_cast<T>(0.0);
    if (std::fabs(z) < static_cast<T>(1e-6)) z = static_cast<T>(0.0);
}

// 벡터의 방향을 반대로
template<typename T>
void Vector3<T>::Reverse(void) {
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
    return Vector3<T>(u.x / s, u.y / s, u.z / s);
}

// 스칼라 삼중곱
template<typename T>
T ScalarTripleProduct(const Vector3<T>& u, const Vector3<T>& v, const Vector3<T>& w) {
    return T(u * (v ^ w));  // (u dot (v cross w))
}

// 벡터 삼중곱
template<typename T>
Vector3<T> VectorTripleProduct(const Vector3<T>& u, const Vector3<T>& v, const Vector3<T>& w) {
    return u ^ (v ^ w);  // u cross (v cross w)
}

// Pitch 회전 (X축 기준 회전)
template<typename T>
Vector3<T> Vector3<T>::Pitch(T angle) const {
    T rad = angle * static_cast<T>(M_PI) / static_cast<T>(180.0);  // 각도를 라디안으로 변환
    T cosAngle = std::cos(rad);
    T sinAngle = std::sin(rad);
    return Vector3(x, y * cosAngle - z * sinAngle, y * sinAngle + z * cosAngle);
}

// Yaw 회전 (Y축 기준 회전)
template<typename T>
Vector3<T> Vector3<T>::Yaw(T angle) const {
    T rad = angle * static_cast<T>(M_PI) / static_cast<T>(180.0);  // 각도를 라디안으로 변환
    T cosAngle = std::cos(rad);
    T sinAngle = std::sin(rad);
    return Vector3(x * cosAngle + z * sinAngle, y, -x * sinAngle + z * cosAngle);
}

// Roll 회전 (Z축 기준 회전)
template<typename T>
Vector3<T> Vector3<T>::Roll(T angle) const {
    T rad = angle * static_cast<T>(M_PI) / static_cast<T>(180.0);  // 각도를 라디안으로 변환
    T cosAngle = std::cos(rad);
    T sinAngle = std::sin(rad);
    return Vector3(x * cosAngle - y * sinAngle, x * sinAngle + y * cosAngle, z);
}

// 회전 순서에 따른 회전 적용
template<typename T>
Vector3<T> Vector3<T>::ApplyRotationOrder(const std::string& order, const Vector3& angles) const {
    Vector3 result = *this;

    for (char axis : order) {
        switch (axis) {
            case 'x':
                result = result.Pitch(angles.x);
                break;
            case 'y':
                result = result.Yaw(angles.y);
                break;
            case 'z':
                result = result.Roll(angles.z);
                break;
            default:
                throw std::invalid_argument("Invalid rotation order");
        }
    }

    return result;
}

// 템플릿 명시적 인스턴스화 (필요한 경우 사용)
template class Vector3<float>;
template class Vector3<double>;