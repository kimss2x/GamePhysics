#include "Matrix4x4.h"
#include "Vector4.h"
#include "Angle.h"

// 기본 생성자 정의
template<typename T>
Matrix4x4<T>::Matrix4x4(void) : 
    e11(0), e12(0), e13(0), e14(0), 
    e21(0), e22(0), e23(0), e24(0), 
    e31(0), e32(0), e33(0), e34(0), 
    e41(0), e42(0), e43(0), e44(0) 
{}

// 단위 행렬 생성
template<typename T>
Matrix4x4<T> Matrix4x4<T>::identity() {
    return Matrix4x4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

// 행렬 대각합 (Trace)
template<typename T>
T Matrix4x4<T>::trace() const {
    return e11 + e22 + e33 + e44;
}

// 크기 행렬 생성
template<typename T>
Matrix4x4<T> Matrix4x4<T>::scale(T sx, T sy, T sz, T sw) {
    return Matrix4x4(
        sx, 0,  0,  0,
        0,  sy, 0,  0,
        0,  0,  sz, 0,
        0,  0,  0,  sw
    );
}

// X축 기준 회전 행렬 생성 (Pitch)
template<typename T>
Matrix4x4<T> Matrix4x4<T>::rotationX(T angle) {
    T rad = DegToRad(angle);
    T cosA = std::cos(rad);
    T sinA = std::sin(rad);

    return Matrix4x4(
        1,  0,     0,    0,
        0,  cosA, -sinA, 0,
        0,  sinA,  cosA, 0,
        0,  0,     0,    1
    );
}

// Y축 기준 회전 행렬 생성 (Yaw)
template<typename T>
Matrix4x4<T> Matrix4x4<T>::rotationY(T angle) {
    T rad = DegToRad(angle);
    T cosA = std::cos(rad);
    T sinA = std::sin(rad);

    return Matrix4x4(
        cosA,  0, sinA, 0,
        0,     1, 0,    0,
        -sinA, 0, cosA, 0,
        0,     0, 0,    1
    );
}

// Z축 기준 회전 행렬 생성 (Roll)
template<typename T>
Matrix4x4<T> Matrix4x4<T>::rotationZ(T angle) {
    T rad = DegToRad(angle);
    T cosA = std::cos(rad);
    T sinA = std::sin(rad);

    return Matrix4x4(
        cosA, -sinA, 0, 0,
        sinA,  cosA, 0, 0,
        0,     0,    1, 0,
        0,     0,    0, 1
    );
}

// 매개변수가 있는 생성자 정의
template<typename T>
Matrix4x4<T>::Matrix4x4(
    T r1c1, T r1c2, T r1c3, T r1c4,
    T r2c1, T r2c2, T r2c3, T r2c4,
    T r3c1, T r3c2, T r3c3, T r3c4,
    T r4c1, T r4c2, T r4c3, T r4c4
) : e11(r1c1), e12(r1c2), e13(r1c3), e14(r1c4),
    e21(r2c1), e22(r2c2), e23(r2c3), e24(r2c4),
    e31(r3c1), e32(r3c2), e33(r3c3), e34(r3c4),
    e41(r4c1), e42(r4c2), e43(r4c3), e44(r4c4) {}

// 행렬식 계산
template<typename T>
T Matrix4x4<T>::determinant() const {
    // 4x4 행렬의 행렬식 계산
    return
        e11 * (e22 * (e33 * e44 - e34 * e43) -
               e23 * (e32 * e44 - e34 * e42) +
               e24 * (e32 * e43 - e33 * e42)) -
        e12 * (e21 * (e33 * e44 - e34 * e43) -
               e23 * (e31 * e44 - e34 * e41) +
               e24 * (e31 * e43 - e33 * e41)) +
        e13 * (e21 * (e32 * e44 - e34 * e42) -
               e22 * (e31 * e44 - e34 * e41) +
               e24 * (e31 * e42 - e32 * e41)) -
        e14 * (e21 * (e32 * e43 - e33 * e42) -
               e22 * (e31 * e43 - e33 * e41) +
               e23 * (e31 * e42 - e32 * e41));
}

// 전치 행렬 계산
template<typename T>
Matrix4x4<T> Matrix4x4<T>::transpose() const {
    return Matrix4x4(
        e11, e21, e31, e41,
        e12, e22, e32, e42,
        e13, e23, e33, e43,
        e14, e24, e34, e44
    );
}

// 역행렬 계산
template<typename T>
Matrix4x4<T> Matrix4x4<T>::inverse() const {
    T det = determinant();
    if (det == 0) {
        throw std::runtime_error("Matrix is not invertible");
    }
    T invDet = static_cast<T>(1.0) / det;

    // 4x4 행렬의 역행렬 계산
    return Matrix4x4(
        // 각 요소의 계산식은 생략되었으나, 여기서 계산해야 합니다.
    ) * invDet;
}

// 행렬 합: += 연산자
template<typename T>
Matrix4x4<T>& Matrix4x4<T>::operator+=(const Matrix4x4& m) {
    e11 += m.e11;
    e12 += m.e12;
    e13 += m.e13;
    e14 += m.e14;
    e21 += m.e21;
    e22 += m.e22;
    e23 += m.e23;
    e24 += m.e24;
    e31 += m.e31;
    e32 += m.e32;
    e33 += m.e33;
    e34 += m.e34;
    e41 += m.e41;
    e42 += m.e42;
    e43 += m.e43;
    e44 += m.e44;
    return *this;
}

// 행렬 뺄셈: -= 연산자
template<typename T>
Matrix4x4<T>& Matrix4x4<T>::operator-=(const Matrix4x4& m) {
    e11 -= m.e11;
    e12 -= m.e12;
    e13 -= m.e13;
    e14 -= m.e14;
    e21 -= m.e21;
    e22 -= m.e22;
    e23 -= m.e23;
    e24 -= m.e24;
    e31 -= m.e31;
    e32 -= m.e32;
    e33 -= m.e33;
    e34 -= m.e34;
    e41 -= m.e41;
    e42 -= m.e42;
    e43 -= m.e43;
    e44 -= m.e44;
    return *this;
}

// 스칼라 곱: *= 연산자
template<typename T>
Matrix4x4<T>& Matrix4x4<T>::operator*=(T s) {
    e11 *= s;
    e12 *= s;
    e13 *= s;
    e14 *= s;
    e21 *= s;
    e22 *= s;
    e23 *= s;
    e24 *= s;
    e31 *= s;
    e32 *= s;
    e33 *= s;
    e34 *= s;
    e41 *= s;
    e42 *= s;
    e43 *= s;
    e44 *= s;
    return *this;
}

// 스칼라 나눗셈: /= 연산자
template<typename T>
Matrix4x4<T>& Matrix4x4<T>::operator/=(T s) {
    e11 /= s;
    e12 /= s;
    e13 /= s;
    e14 /= s;
    e21 /= s;
    e22 /= s;
    e23 /= s;
    e24 /= s;
    e31 /= s;
    e32 /= s;
    e33 /= s;
    e34 /= s;
    e41 /= s;
    e42 /= s;
    e43 /= s;
    e44 /= s;
    return *this;
}

// 행렬 합: + 연산자
template<typename T>
Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4& m) const {
    return Matrix4x4(
        e11 + m.e11, e12 + m.e12, e13 + m.e13, e14 + m.e14,
        e21 + m.e21, e22 + m.e22, e23 + m.e23, e24 + m.e24,
        e31 + m.e31, e32 + m.e32, e33 + m.e33, e34 + m.e34,
        e41 + m.e41, e42 + m.e42, e43 + m.e43, e44 + m.e44
    );
}

// 행렬 뺄셈: - 연산자
template<typename T>
Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4& m) const {
    return Matrix4x4(
        e11 - m.e11, e12 - m.e12, e13 - m.e13, e14 - m.e14,
        e21 - m.e21, e22 - m.e22, e23 - m.e23, e24 - m.e24,
        e31 - m.e31, e32 - m.e32, e33 - m.e33, e34 - m.e34,
        e41 - m.e41, e42 - m.e42, e43 - m.e43, e44 - m.e44
    );
}

// 행렬 곱: * 연산자
template<typename T>
Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4& m) const {
    return Matrix4x4(
        e11 * m.e11 + e12 * m.e21 + e13 * m.e31 + e14 * m.e41,
        e11 * m.e12 + e12 * m.e22 + e13 * m.e32 + e14 * m.e42,
        e11 * m.e13 + e12 * m.e23 + e13 * m.e33 + e14 * m.e43,
        e11 * m.e14 + e12 * m.e24 + e13 * m.e34 + e14 * m.e44,
        e21 * m.e11 + e22 * m.e21 + e23 * m.e31 + e24 * m.e41,
        e21 * m.e12 + e22 * m.e22 + e23 * m.e32 + e24 * m.e42,
        e21 * m.e13 + e22 * m.e23 + e23 * m.e33 + e24 * m.e43,
        e21 * m.e14 + e22 * m.e24 + e23 * m.e34 + e24 * m.e44,
        e31 * m.e11 + e32 * m.e21 + e33 * m.e31 + e34 * m.e41,
        e31 * m.e12 + e32 * m.e22 + e33 * m.e32 + e34 * m.e42,
        e31 * m.e13 + e32 * m.e23 + e33 * m.e33 + e34 * m.e43,
        e31 * m.e14 + e32 * m.e24 + e33 * m.e34 + e34 * m.e44,
        e41 * m.e11 + e42 * m.e21 + e43 * m.e31 + e44 * m.e41,
        e41 * m.e12 + e42 * m.e22 + e43 * m.e32 + e44 * m.e42,
        e41 * m.e13 + e42 * m.e23 + e43 * m.e33 + e44 * m.e43,
        e41 * m.e14 + e42 * m.e24 + e43 * m.e34 + e44 * m.e44
    );
}

// 스칼라 곱: * 연산자
template<typename T>
Matrix4x4<T> Matrix4x4<T>::operator*(T s) const {
    return Matrix4x4(
        e11 * s, e12 * s, e13 * s, e14 * s,
        e21 * s, e22 * s, e23 * s, e24 * s,
        e31 * s, e32 * s, e33 * s, e34 * s,
        e41 * s, e42 * s, e43 * s, e44 * s
    );
}

// 행렬과 벡터4 간의 곱셈
template<typename T>
Vector4<T> operator*(const Matrix4x4<T>& m, const Vector4<T>& v) {
    return Vector4<T>(
        m.e11 * v.x + m.e12 * v.y + m.e13 * v.z + m.e14 * v.w,
        m.e21 * v.x + m.e22 * v.y + m.e23 * v.z + m.e24 * v.w,
        m.e31 * v.x + m.e32 * v.y + m.e33 * v.z + m.e34 * v.w,
        m.e41 * v.x + m.e42 * v.y + m.e43 * v.z + m.e44 * v.w
    );
}

// 벡터4와 행렬 간의 곱셈
template<typename T>
Vector4<T> operator*(const Vector4<T>& v, const Matrix4x4<T>& m) {
    return Vector4<T>(
        v.x * m.e11 + v.y * m.e21 + v.z * m.e31 + v.w * m.e41,
        v.x * m.e12 + v.y * m.e22 + v.z * m.e32 + v.w * m.e42,
        v.x * m.e13 + v.y * m.e23 + v.z * m.e33 + v.w * m.e43,
        v.x * m.e14 + v.y * m.e24 + v.z * m.e34 + v.w * m.e44
    );
}

// 스칼라 나눗셈: / 연산자
template<typename T>
Matrix4x4<T> Matrix4x4<T>::operator/(T s) const {
    return Matrix4x4(
        e11 / s, e12 / s, e13 / s, e14 / s,
        e21 / s, e22 / s, e23 / s, e24 / s,
        e31 / s, e32 / s, e33 / s, e34 / s,
        e41 / s, e42 / s, e43 / s, e44 / s
    );
}

// 템플릿 명시적 인스턴스화 (필요한 경우 사용)
template class Matrix4x4<float>;
template class Matrix4x4<double>;
