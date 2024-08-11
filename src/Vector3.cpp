#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Constants.h"
#include <stdexcept>  // 예외 처리를 위해 필요

// 생성자
template<typename T>
Vector3<T>::Vector3(void) : x(0), y(0), z(0) {}

// 생성자
template<typename T>
Vector3<T>::Vector3(T xi, T yi, T zi) : x(xi), y(yi), z(zi) {}

// Vector3를 Vector4로 변환
template<typename T>
Vector4<T> Vector3<T>::ToVector4(T w) const {
    return Vector4<T>(x, y, z, w);
}

// Vector3를 회전 축으로 하는 Quaternion으로 변환
template<typename T>
Quaternion<T> Vector3<T>::ToQuaternion(T angle) const {
    Vector3<T> axis = *this;
    axis.Normalize();
    T halfAngle = angle / 2.0;
    T sinHalfAngle = std::sin(halfAngle);
    T cosHalfAngle = std::cos(halfAngle);

    return Quaternion<T>(cosHalfAngle, axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle);
}

template<typename T>
Matrix3x3<T> Vector3<T>::ToMatrix3x3() const {
    Matrix3x3<T> mat;
    mat.e11 = x;
    mat.e22 = y;
    mat.e33 = z;
    return mat;
}

template<typename T>
Matrix4x4<T> Vector3<T>::ToMatrix4x4() const {
    Matrix4x4<T> mat;
    mat.e11 = x;
    mat.e22 = y;
    mat.e33 = z;
    mat.e44 = 1;
    return mat;
}

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
    T rad = angle * Constants<T>::PI / static_cast<T>(180.0);  // 각도를 라디안으로 변환
    T cosAngle = std::cos(rad);
    T sinAngle = std::sin(rad);
    return Vector3(x, y * cosAngle - z * sinAngle, y * sinAngle + z * cosAngle);
}

// Yaw 회전 (Y축 기준 회전)
template<typename T>
Vector3<T> Vector3<T>::Yaw(T angle) const {
    T rad = angle * Constants<T>::PI / static_cast<T>(180.0);  // 각도를 라디안으로 변환
    T cosAngle = std::cos(rad);
    T sinAngle = std::sin(rad);
    return Vector3(x * cosAngle + z * sinAngle, y, -x * sinAngle + z * cosAngle);
}

// Roll 회전 (Z축 기준 회전)
template<typename T>
Vector3<T> Vector3<T>::Roll(T angle) const {
    T rad = angle * Constants<T>::PI / static_cast<T>(180.0);  // 각도를 라디안으로 변환
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

// Matrix3x3와 Vector3의 곱셈
template<typename T>
Vector3<T> operator*(const Matrix3x3<T>& m, const Vector3<T>& v) {
    return Vector3<T>(
        m.e11 * v.x + m.e12 * v.y + m.e13 * v.z,
        m.e21 * v.x + m.e22 * v.y + m.e23 * v.z,
        m.e31 * v.x + m.e32 * v.y + m.e33 * v.z
    );
}

// 템플릿 명시적 인스턴스화 (필요한 경우 사용)
template class Vector3<float>;
template class Vector3<double>;
template Vector3<double> operator/(const Vector3<double>& u, double s);
template Vector3<double> operator*(const Vector3<double>& u, double s);
template Vector3<double> operator*(double s, const Vector3<double>& u);
template Vector3<double> operator*(const Matrix3x3<double>& m, const Vector3<double>& v);