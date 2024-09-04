#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>
#include "Angle.h"

template<typename T> class Vector4;     // 포워드 선언 
template<typename T> class Matrix3x3;   // 포워드 선언 
template<typename T> class Matrix4x4;   // 포워드 선언 
template<typename T> class Quaternion;  // 포워드 선언 

template<typename T>
class Vector3 {
public:
    T x, y, z;

    Vector3(void);
    Vector3(T xi, T yi, T zi);

    // Vector3를 Vector4로 변환
    Vector4<T> toVector4(T w = 1) const;

    // Vector3를 회전 축으로 하는 Quaternion으로 변환
    Quaternion<T> toQuaternion(T angle) const;

    // Vector3를 대각 행렬로 변환
    Matrix3x3<T> toMatrix3x3() const;

    // Vector3를 대각 행렬로 변환
    Matrix4x4<T> toMatrix4x4() const;

    T magnitude(void) const;
    void normalize(void);
    void reverse(void);

    Vector3& operator+=(const Vector3& u);
    Vector3& operator-=(const Vector3& u);
    Vector3& operator*=(T s);
    Vector3& operator/=(T s);

    Vector3 operator-(void) const;

    // Pitch, Yaw, Roll 회전 메서드
    Vector3 pitch(T angle) const; // X축 기준 회전
    Vector3 yaw(T angle) const;   // Y축 기준 회전
    Vector3 roll(T angle) const;  // Z축 기준 회전

    // 회전 순서에 따른 회전 적용
    Vector3 rotation(T pitch, T yaw, T roll, const std::string& order = "xyz") const;

    template<typename T>
    friend Vector3<T> operator*(const Matrix3x3<T>& m, const Vector3<T>& v);

    // 벡터의 성분을 출력
    friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

// 템플릿 함수들의 정의
template<typename T>
Vector3<T> operator+(const Vector3<T>& u, const Vector3<T>& v);

template<typename T>
Vector3<T> operator-(const Vector3<T>& u, const Vector3<T>& v);

template<typename T>
Vector3<T> operator^(const Vector3<T>& u, const Vector3<T>& v);  // 외적

template<typename T>
T operator*(const Vector3<T>& u, const Vector3<T>& v);  // 내적

template<typename T>
Vector3<T> operator*(const Vector3<T>& u, T s);

template<typename T>
Vector3<T> operator*(T s, const Vector3<T>& u);

template<typename T>
Vector3<T> operator/(const Vector3<T>& u, T s);

template<typename T>
T scalarTripleProduct(const Vector3<T>& u, const Vector3<T>& v, const Vector3<T>& w);  // 스칼라 삼중곱

template<typename T>
Vector3<T> vectorTripleProduct(const Vector3<T>& u, const Vector3<T>& v, const Vector3<T>& w);  // 벡터 삼중곱

#endif // VECTOR3_H
