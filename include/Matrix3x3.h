#ifndef MATRIX3X3_H
#define MATRIX3X3_H

class Matrix3x3 {
public:
    // 원소 eij: i → 행, j → 열
    float e11, e12, e13, e21, e22, e23, e31, e32, e33;

    // 기본 생성자
    Matrix3x3(void);

    // 매개변수가 있는 생성자
    Matrix3x3(
        float r1c1, float r1c2, float r1c3,
        float r2c1, float r2c2, float r2c3,
        float r3c1, float r3c2, float r3c3
    );

    // 행렬식
    float determinant() const;

    // 전치 행렬
    Matrix3x3 transpose() const;

    // 역행렬
    Matrix3x3 inverse() const;

    // 행렬 합: += 연산자
    Matrix3x3& operator+=(const Matrix3x3& m);

    // 행렬 뺄셈: -= 연산자
    Matrix3x3& operator-=(const Matrix3x3& m);

    // 스칼라 곱: *= 연산자
    Matrix3x3& operator*=(float s);

    // 스칼라 나눗셈: /= 연산자
    Matrix3x3& operator/=(float s);

    // 행렬 합: + 연산자
    Matrix3x3 operator+(const Matrix3x3& m) const;

    // 행렬 뺄셈: - 연산자
    Matrix3x3 operator-(const Matrix3x3& m) const;

    // 행렬 곱: * 연산자
    Matrix3x3 operator*(const Matrix3x3& m) const;

    // 스칼라 곱: * 연산자
    Matrix3x3 operator*(float s) const;

    // 스칼라 나눗셈: / 연산자
    Matrix3x3 operator/(float s) const;
};

#endif // MATRIX3X3_H
