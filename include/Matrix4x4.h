#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Vector4.h"
#include <stdexcept>

template<typename T>
class Matrix4x4 {
public:
    // 원소 eij: i → 행, j → 열
    T e11, e12, e13, e14;
    T e21, e22, e23, e24;
    T e31, e32, e33, e34;
    T e41, e42, e43, e44;

    // 기본 생성자
    Matrix4x4(void);

    // 매개변수가 있는 생성자
    Matrix4x4(T r1c1, T r1c2, T r1c3, T r1c4,
              T r2c1, T r2c2, T r2c3, T r2c4,
              T r3c1, T r3c2, T r3c3, T r3c4,
              T r4c1, T r4c2, T r4c3, T r4c4);

    // 단위 행렬 생성
    static Matrix4x4 identity();

    // 행렬 대각합 (Trace)
    T trace() const;

    // 크기 행렬 생성
    static Matrix4x4 scale(T sx, T sy, T sz, T sw);

    // 회전 행렬 생성
    static Matrix4x4 rotationX(T angle);    // Pitch
    static Matrix4x4 rotationY(T angle);    // Yaw
    static Matrix4x4 rotationZ(T angle);    // Roll

    // 행렬식 계산
    T determinant() const;

    // 전치 행렬 계산
    Matrix4x4 transpose() const;

    // 역행렬 계산
    Matrix4x4 inverse() const;

    // 연산자 오버로드
    Matrix4x4& operator+=(const Matrix4x4& m);
    Matrix4x4& operator-=(const Matrix4x4& m);
    Matrix4x4& operator*=(T s);
    Matrix4x4& operator/=(T s);

    Matrix4x4 operator+(const Matrix4x4& m) const;
    Matrix4x4 operator-(const Matrix4x4& m) const;
    Matrix4x4 operator*(const Matrix4x4& m) const;
    Matrix4x4 operator*(T s) const;
    Matrix4x4 operator/(T s) const;

    // 행렬과 벡터4 간의 곱셈
    template<typename U>
    friend Vector4<U> operator*(const Matrix4x4<U>& m, const Vector4<U>& v);

    // 벡터4와 행렬 간의 곱셈
    template<typename U>
    friend Vector4<U> operator*(const Vector4<U>& v, const Matrix4x4<U>& m);
};

// 템플릿 정의를 포함하기 위해 필요한 cpp 파일 포함
#include "Matrix4x4.cpp"

#endif // MATRIX4X4_H
