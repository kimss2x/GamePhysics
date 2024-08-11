#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include <stdexcept>  // 예외 처리를 위해 필요

// 기본 생성자
template<typename T>
Vector4<T>::Vector4(void) : x(0), y(0), z(0), w(0) {}

// 매개변수가 있는 생성자
template<typename T>
Vector4<T>::Vector4(T xi, T yi, T zi, T wi) : x(xi), y(yi), z(zi), w(wi) {}

// Vector4를 대각 행렬로 변환
template<typename T>
Matrix4x4<T> Vector4<T>::ToMatrix4x4() const {
    Matrix4x4<T> mat;
    mat.e11 = x;
    mat.e22 = y;
    mat.e33 = z;
    mat.e44 = w;
    return mat;
}


// 벡터의 크기(길이)를 계산
template<typename T>
T Vector4<T>::Magnitude(void) const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

// 벡터를 정규화
template<typename T>
void Vector4<T>::Normalize(void) {
    T m = Magnitude();
    if (m > static_cast<T>(1e-6)) {
        x /= m;
        y /= m;
        z /= m;
        w /= m;
    }
}

// 벡터의 방향을 반대로
template<typename T>
void Vector4<T>::Reverse(void) {
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

// Vector4 to Vector3 변환
template<typename T>
Vector3<T> Vector4<T>::ToVector3() const {
    if (w != 0) {
        return Vector3<T>(x / w, y / w, z / w);
    }
    return Vector3<T>(x, y, z);
}

// Vector4 to Quaternion 변환
template<typename T>
Quaternion<T> Vector4<T>::ToQuaternion() const {
    return Quaternion<T>(w, x, y, z);
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
    return Vector4<T>(u.x / s, u.y / s, u.z / s, u.w / s);
}

// 스칼라 삼중곱
template<typename T>
T ScalarTripleProduct(const Vector4<T>& u, const Vector4<T>& v, const Vector4<T>& w) {
    return u * (v ^ w);  // (u dot (v cross w))
}

// 벡터 삼중곱
template<typename T>
Vector4<T> VectorTripleProduct(const Vector4<T>& u, const Vector4<T>& v, const Vector4<T>& w) {
    return u ^ (v ^ w);  // u cross (v cross w)
}

// Matrix4x4와 Vector4의 곱셈
template<typename T>
Vector4<T> operator*(const Matrix4x4<T>& m, const Vector4<T>& v) {
    return Vector4<T>(
        m.e11 * v.x + m.e12 * v.y + m.e13 * v.z + m.e14 * v.w,
        m.e21 * v.x + m.e22 * v.y + m.e23 * v.z + m.e24 * v.w,
        m.e31 * v.x + m.e32 * v.y + m.e33 * v.z + m.e34 * v.w,
        m.e41 * v.x + m.e42 * v.y + m.e43 * v.z + m.e44 * v.w
    );
}

// 템플릿 명시적 인스턴스화 (필요한 경우 사용)
template Vector4<double> operator/(const Vector4<double>& u, double s);
template Vector4<double> operator*(const Vector4<double>& u, double s);
template Vector4<double> operator*(double s, const Vector4<double>& u);
template Vector4<double> operator*(const Matrix4x4<double>& m, const Vector4<double>& v);
