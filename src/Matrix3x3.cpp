#include "Matrix3x3.h"
#include <stdexcept>  

// 기본 생성자 정의
Matrix3x3::Matrix3x3(void) {
    e11 = 0;
    e12 = 0;
    e13 = 0;
    e21 = 0;
    e22 = 0;
    e23 = 0;
    e31 = 0;
    e32 = 0;
    e33 = 0;
}

// 매개변수가 있는 생성자 정의
Matrix3x3::Matrix3x3(
    float r1c1, float r1c2, float r1c3,
    float r2c1, float r2c2, float r2c3,
    float r3c1, float r3c2, float r3c3
) {
    e11 = r1c1;
    e12 = r1c2;
    e13 = r1c3;
    e21 = r2c1;
    e22 = r2c2;
    e23 = r2c3;
    e31 = r3c1;
    e32 = r3c2;
    e33 = r3c3;
}

// 행렬식
float Matrix3x3::determinant() const {
    return e11 * (e22 * e33 - e23 * e32) -
           e12 * (e21 * e33 - e23 * e31) +
           e13 * (e21 * e32 - e22 * e31);
}

// 전치 행렬
Matrix3x3 Matrix3x3::transpose() const {
    return Matrix3x3(
        e11, e21, e31,
        e12, e22, e32,
        e13, e23, e33
    );
}

// 역행렬
Matrix3x3 Matrix3x3::inverse() const {
    float det = determinant();
    if (det == 0) {
        throw std::runtime_error("Matrix is not invertible");
    }
    float invDet = 1.0f / det;

    return Matrix3x3(
        (e22 * e33 - e23 * e32) * invDet,
        (e13 * e32 - e12 * e33) * invDet,
        (e12 * e23 - e13 * e22) * invDet,
        (e23 * e31 - e21 * e33) * invDet,
        (e11 * e33 - e13 * e31) * invDet,
        (e13 * e21 - e11 * e23) * invDet,
        (e21 * e32 - e22 * e31) * invDet,
        (e12 * e31 - e11 * e32) * invDet,
        (e11 * e22 - e12 * e21) * invDet
    );
}

// 행렬 합: += 연산자
Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& m) {
    e11 += m.e11;
    e12 += m.e12;
    e13 += m.e13;
    e21 += m.e21;
    e22 += m.e22;
    e23 += m.e23;
    e31 += m.e31;
    e32 += m.e32;
    e33 += m.e33;
    return *this;
}

// 행렬 뺄셈: -= 연산자
Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& m) {
    e11 -= m.e11;
    e12 -= m.e12;
    e13 -= m.e13;
    e21 -= m.e21;
    e22 -= m.e22;
    e23 -= m.e23;
    e31 -= m.e31;
    e32 -= m.e32;
    e33 -= m.e33;
    return *this;
}

// 스칼라 곱: *= 연산자
Matrix3x3& Matrix3x3::operator*=(float s) {
    e11 *= s;
    e12 *= s;
    e13 *= s;
    e21 *= s;
    e22 *= s;
    e23 *= s;
    e31 *= s;
    e32 *= s;
    e33 *= s;
    return *this;
}

// 스칼라 나눗셈: /= 연산자
Matrix3x3& Matrix3x3::operator/=(float s) {
    e11 /= s;
    e12 /= s;
    e13 /= s;
    e21 /= s;
    e22 /= s;
    e23 /= s;
    e31 /= s;
    e32 /= s;
    e33 /= s;
    return *this;
}

// 행렬 합: + 연산자
Matrix3x3 Matrix3x3::operator+(const Matrix3x3& m) const {
    return Matrix3x3(
        e11 + m.e11, e12 + m.e12, e13 + m.e13,
        e21 + m.e21, e22 + m.e22, e23 + m.e23,
        e31 + m.e31, e32 + m.e32, e33 + m.e33
    );
}

// 행렬 뺄셈: - 연산자
Matrix3x3 Matrix3x3::operator-(const Matrix3x3& m) const {
    return Matrix3x3(
        e11 - m.e11, e12 - m.e12, e13 - m.e13,
        e21 - m.e21, e22 - m.e22, e23 - m.e23,
        e31 - m.e31, e32 - m.e32, e33 - m.e33
    );
}

// 행렬 곱: * 연산자
Matrix3x3 Matrix3x3::operator*(const Matrix3x3& m) const {
    return Matrix3x3(
        e11 * m.e11 + e12 * m.e21 + e13 * m.e31,
        e11 * m.e12 + e12 * m.e22 + e13 * m.e32,
        e11 * m.e13 + e12 * m.e23 + e13 * m.e33,
        e21 * m.e11 + e22 * m.e21 + e23 * m.e31,
        e21 * m.e12 + e22 * m.e22 + e23 * m.e32,
        e21 * m.e13 + e22 * m.e23 + e23 * m.e33,
        e31 * m.e11 + e32 * m.e21 + e33 * m.e31,
        e31 * m.e12 + e32 * m.e22 + e33 * m.e32,
        e31 * m.e13 + e32 * m.e23 + e33 * m.e33
    );
}

// 스칼라 곱: * 연산자
Matrix3x3 Matrix3x3::operator*(float s) const {
    return Matrix3x3(
        e11 * s, e12 * s, e13 * s,
        e21 * s, e22 * s, e23 * s,
        e31 * s, e32 * s, e33 * s
    );
}

// 스칼라 나눗셈: / 연산자
Matrix3x3 Matrix3x3::operator/(float s) const {
    return Matrix3x3(
        e11 / s, e12 / s, e13 / s,
        e21 / s, e22 / s, e23 / s,
        e31 / s, e32 / s, e33 / s
    );
}
