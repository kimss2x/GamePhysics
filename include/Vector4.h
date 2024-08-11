#ifndef VECTOR4_H
#define VECTOR4_H

#include <cmath>
#include <iostream>
#include "Angle.h"

template<typename T> class Vector3;     // 포워드 선언 
template<typename T> class Matrix4x4;   // 포워드 선언 
template<typename T> class Quaternion;  // 포워드 선언 

template<typename T>
class Vector4 {
public:
    T x, y, z, w;

    Vector4(void);
    Vector4(T xi, T yi, T zi, T wi);

    T Magnitude(void) const;
    void Normalize(void);
    void Reverse(void);

    Vector4& operator+=(const Vector4& u);
    Vector4& operator-=(const Vector4& u);
    Vector4& operator*=(T s);
    Vector4& operator/=(T s);

    Vector4 operator-(void) const;

    // Vector4 to Vector3 변환
    Vector3<T> ToVector3() const;

    // Vector4 to Quaternion 변환
    Quaternion<T> ToQuaternion() const;

    // Vector4를 대각 행렬로 변환
    Matrix4x4<T> ToMatrix4x4() const;
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
T ScalarTripleProduct(const Vector4<T>& u, const Vector4<T>& v, const Vector4<T>& w);  // 스칼라 삼중곱

template<typename T>
Vector4<T> VectorTripleProduct(const Vector4<T>& u, const Vector4<T>& v, const Vector4<T>& w);  // 벡터 삼중곱

#endif // VECTOR4_H
