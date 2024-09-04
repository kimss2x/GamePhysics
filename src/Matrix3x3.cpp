#ifndef MATRIX3X3_CPP
#define MATRIX3X3_CPP

#include "Matrix3x3.h"
#include "Vector3.h"
#include "Angle.h"

// 기본 생성자 정의
template<typename T>
Matrix3x3<T>::Matrix3x3(void) : 
    e11(0), e12(0), e13(0), 
    e21(0), e22(0), e23(0), 
    e31(0), e32(0), e33(0) 
{}

// 단위 행렬 생성
template<typename T>
Matrix3x3<T> Matrix3x3<T>::identity() {
    return Matrix3x3(
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    );
}

// 행렬 대각합
template<typename T>
T Matrix3x3<T>::trace() const {
    return e11 + e22 + e33;
}

// 크기 행렬 생성
template<typename T>
Matrix3x3<T> Matrix3x3<T>::scale(T sx, T sy, T sz) {
    return Matrix3x3(
        sx, 0,  0,
        0,  sy, 0,
        0,  0,  sz
    );
}

// X축 기준 회전 행렬 생성 (Pitch)
template<typename T>
Matrix3x3<T> Matrix3x3<T>::rotationX(T angle) {
    T rad = Angle::degToRad(angle);
    T cosA = std::cos(rad);
    T sinA = std::sin(rad);

    return Matrix3x3(
        1,  0,     0,
        0,  cosA, -sinA,
        0,  sinA,  cosA
    );
}

// Y축 기준 회전 행렬 생성 (Yaw)
template<typename T>
Matrix3x3<T> Matrix3x3<T>::rotationY(T angle) {
    T rad = Angle::degToRad(angle);
    T cosA = std::cos(rad);
    T sinA = std::sin(rad);

    return Matrix3x3(
        cosA,  0, sinA,
        0,     1, 0,
        -sinA, 0, cosA
    );
}

// Z축 기준 회전 행렬 생성 (Roll)
template<typename T>
Matrix3x3<T> Matrix3x3<T>::rotationZ(T angle) {
    T rad = Angle::degToRad(angle);
    T cosA = std::cos(rad);
    T sinA = std::sin(rad);

    return Matrix3x3(
        cosA, -sinA, 0,
        sinA,  cosA, 0,
        0,     0,    1
    );
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::rotation(T pitch, T yaw, T roll, const std::string& order) {
    Matrix3x3<T> result = Matrix3x3<T>::identity(); // 기본값으로 단위 행렬

    for (char axis : order) {
        switch (axis) {
        case 'x': // X축 기준 회전 (Pitch)
            result = result * Matrix3x3<T>::rotationX(pitch);
            break;
        case 'y': // Y축 기준 회전 (Yaw)
            result = result * Matrix3x3<T>::rotationY(yaw);
            break;
        case 'z': // Z축 기준 회전 (Roll)
            result = result * Matrix3x3<T>::rotationZ(roll);
            break;
        default:
            throw std::invalid_argument("Invalid rotation axis");
        }
    }

    return result;
}


// 매개변수가 있는 생성자 정의
template<typename T>
Matrix3x3<T>::Matrix3x3(
    T r1c1, T r1c2, T r1c3,
    T r2c1, T r2c2, T r2c3,
    T r3c1, T r3c2, T r3c3
) : e11(r1c1), e12(r1c2), e13(r1c3),
    e21(r2c1), e22(r2c2), e23(r2c3),
    e31(r3c1), e32(r3c2), e33(r3c3) {}

// 행렬식
template<typename T>
T Matrix3x3<T>::determinant() const {
    return e11 * (e22 * e33 - e23 * e32) -
           e12 * (e21 * e33 - e23 * e31) +
           e13 * (e21 * e32 - e22 * e31);
}

// 전치 행렬
template<typename T>
Matrix3x3<T> Matrix3x3<T>::transpose() const {
    return Matrix3x3(
        e11, e21, e31,
        e12, e22, e32,
        e13, e23, e33
    );
}

// 역행렬
template<typename T>
Matrix3x3<T> Matrix3x3<T>::inverse() const {
    T det = determinant();
    if (det == 0) {
        throw std::runtime_error("Matrix is not invertible");
    }
    T invDet = static_cast<T>(1.0) / det;

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
template<typename T>
Matrix3x3<T>& Matrix3x3<T>::operator+=(const Matrix3x3& m) {
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
template<typename T>
Matrix3x3<T>& Matrix3x3<T>::operator-=(const Matrix3x3& m) {
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
template<typename T>
Matrix3x3<T>& Matrix3x3<T>::operator*=(T s) {
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
template<typename T>
Matrix3x3<T>& Matrix3x3<T>::operator/=(T s) {
    if (s == 0) {
        throw std::runtime_error("Division by zero in Matrix3x3::operator/=");
    }
    e11 /= s; e12 /= s; e13 /= s;
    e21 /= s; e22 /= s; e23 /= s;
    e31 /= s; e32 /= s; e33 /= s;
    return *this;
}

// 행렬 합: + 연산자
template<typename T>
Matrix3x3<T> Matrix3x3<T>::operator+(const Matrix3x3& m) const {
    return Matrix3x3(
        e11 + m.e11, e12 + m.e12, e13 + m.e13,
        e21 + m.e21, e22 + m.e22, e23 + m.e23,
        e31 + m.e31, e32 + m.e32, e33 + m.e33
    );
}

// 행렬 뺄셈: - 연산자
template<typename T>
Matrix3x3<T> Matrix3x3<T>::operator-(const Matrix3x3& m) const {
    return Matrix3x3(
        e11 - m.e11, e12 - m.e12, e13 - m.e13,
        e21 - m.e21, e22 - m.e22, e23 - m.e23,
        e31 - m.e31, e32 - m.e32, e33 - m.e33
    );
}

// 행렬 곱: * 연산자
template<typename T>
Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3& m) const {
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
template<typename T>
Matrix3x3<T> Matrix3x3<T>::operator*(T s) const {
    return Matrix3x3(
        e11 * s, e12 * s, e13 * s,
        e21 * s, e22 * s, e23 * s,
        e31 * s, e32 * s, e33 * s
    );
}

// 행렬과 벡터 간의 곱셈
template<typename T>
Vector3<T> operator*(const Matrix3x3<T>& m, const Vector3<T>& v) {
    return Vector3<T>(
        m.e11 * v.x + m.e12 * v.y + m.e13 * v.z,
        m.e21 * v.x + m.e22 * v.y + m.e23 * v.z,
        m.e31 * v.x + m.e32 * v.y + m.e33 * v.z
    );
}

// 벡터와 행렬 간의 곱셈
template<typename T>
Vector3<T> operator*(const Vector3<T>& v, const Matrix3x3<T>& m) {
    return Vector3<T>(
        v.x * m.e11 + v.y * m.e21 + v.z * m.e31,
        v.x * m.e12 + v.y * m.e22 + v.z * m.e32,
        v.x * m.e13 + v.y * m.e23 + v.z * m.e33
    );
}

// 스칼라 나눗셈: / 연산자
template<typename T>
Matrix3x3<T> Matrix3x3<T>::operator/(T s) const {
    if (s == 0) {
        throw std::runtime_error("Division by zero in Matrix3x3::operator/");
    }
    return Matrix3x3(
        e11 / s, e12 / s, e13 / s,
        e21 / s, e22 / s, e23 / s,
        e31 / s, e32 / s, e33 / s
    );
}

// 템플릿 명시적 인스턴스화 (필요한 경우 사용)
template class Matrix3x3<float>;
template class Matrix3x3<double>;

#endif // MATRIX3X3_CPP