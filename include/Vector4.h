#ifndef VECTOR4_H
#define VECTOR4_H

#include <cmath>
#include <iostream>
#include "Angle.h"

template<typename T> class Vector3;     // 포워드 선언 
template<typename T> class Matrix3x3;   // 포워드 선언 
template<typename T> class Matrix4x4;   // 포워드 선언 
template<typename T> class Quaternion;  // 포워드 선언 

template<typename T>
class Vector4 {
public:
    T x, y, z, w;

    Vector4(void);
    Vector4(T xi, T yi, T zi, T wi);

    // Vector4 to Vector3 변환
    Vector3<T> toVector3() const;

    // Vector4 to Quaternion 변환
    Quaternion<T> toQuaternion() const;

    // Vector4를 대각 행렬로 변환
    Matrix3x3<T> toMatrix3x3() const;

    // Vector4를 대각 행렬로 변환
    Matrix4x4<T> toMatrix4x4() const;

    T magnitude(void) const;
    void normalize(void);
    void reverse(void);

    Vector4& operator+=(const Vector4& u);
    Vector4& operator-=(const Vector4& u);
    Vector4& operator*=(T s);
    Vector4& operator/=(T s);

    Vector4 operator-(void) const;

    // Pitch, Yaw, Roll 회전 메서드
    Vector4 pitch(T angle) const; // X축 기준 회전
    Vector4 yaw(T angle) const;   // Y축 기준 회전
    Vector4 roll(T angle) const;  // Z축 기준 회전

    // 회전 순서에 따른 회전 적용
    Vector4 rotation(T pitch, T yaw, T roll, const std::string& order = "xyz") const;

    template<typename T>
    friend Vector4<T> operator*(const Matrix4x4<T>& m, const Vector4<T>& v);

    // 벡터의 성분을 출력
    friend std::ostream& operator<<(std::ostream& os, const Vector4& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
        return os;
    }
};

// 템플릿 함수들의 정의
template<typename T>
Vector4<T> operator+(const Vector4<T>& u, const Vector4<T>& v);

template<typename T>
Vector4<T> operator-(const Vector4<T>& u, const Vector4<T>& v);

template<typename T>
Vector4<T> operator^(const Vector4<T>& u, const Vector4<T>& v);  // 외적

template<typename T>
T operator*(const Vector4<T>& u, const Vector4<T>& v);  // 내적

template<typename T>
Vector4<T> operator*(const Vector4<T>& u, T s);

template<typename T>
Vector4<T> operator*(T s, const Vector4<T>& u);

template<typename T>
Vector4<T> operator/(const Vector4<T>& u, T s);

template<typename T>
T scalarTripleProduct(const Vector4<T>& u, const Vector4<T>& v, const Vector4<T>& w);  // 스칼라 삼중곱

template<typename T>
Vector4<T> vectorTripleProduct(const Vector4<T>& u, const Vector4<T>& v, const Vector4<T>& w);  // 벡터 삼중곱

#endif // VECTOR4_H
