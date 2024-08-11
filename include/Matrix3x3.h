#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include "Vector3.h"
#include <stdexcept>

template<typename T>
class Matrix3x3 {
public:
    // 원소 eij: i → 행, j → 열
    T e11, e12, e13; 
    T e21, e22, e23;
    T e31, e32, e33;

    // 기본 생성자
    Matrix3x3(void);

    // 매개변수가 있는 생성자
    Matrix3x3(
        T r1c1, T r1c2, T r1c3,
        T r2c1, T r2c2, T r2c3,
        T r3c1, T r3c2, T r3c3
    );

    // 단위 행렬 생성
    static Matrix3x3 identity();

    // 행렬 대각합 (Trace)
    T trace() const;

    // 크기 행렬 생성
    static Matrix3x3 scale(T sx, T sy, T sz);

    // 회전 행렬 생성
    static Matrix3x3 rotationX(T angle);    // Pitch
    static Matrix3x3 rotationY(T angle);    // Yaw
    static Matrix3x3 rotationZ(T angle);    // Roll

    // 행렬식
    T determinant() const;

    // 전치 행렬
    Matrix3x3 transpose() const;

    // 역행렬
    Matrix3x3 inverse() const;

    // 연산자 오버로드
    Matrix3x3& operator+=(const Matrix3x3& m);
    Matrix3x3& operator-=(const Matrix3x3& m);
    Matrix3x3& operator*=(T s);
    Matrix3x3& operator/=(T s);

    Matrix3x3 operator+(const Matrix3x3& m) const;
    Matrix3x3 operator-(const Matrix3x3& m) const;
    Matrix3x3 operator*(const Matrix3x3& m) const;
    Matrix3x3 operator*(T s) const;
    Matrix3x3 operator/(T s) const;

    // 행렬과 벡터 간의 곱셈
    template<typename U>
    friend Vector3<U> operator*(const Matrix3x3<U>& m, const Vector3<U>& v);

    // 벡터와 행렬 간의 곱셈
    template<typename U>
    friend Vector3<U> operator*(const Vector3<U>& v, const Matrix3x3<U>& m);
};

#include "Matrix3x3.cpp" // 템플릿 클래스의 정의를 포함

#endif // MATRIX3X3_H
