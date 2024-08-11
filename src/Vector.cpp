#include "Vector.h"
#include "Constants.h"
#include <cmath>

// 생성자
Vector::Vector(void) : x(0), y(0), z(0) {}

// 생성자
Vector::Vector(float xi, float yi, float zi) : x(xi), y(yi), z(zi) {}

// 벡터의 크기 계산
float Vector::Magnitude(void) const {
    return std::sqrt(x * x + y * y + z * z);
}

// 벡터를 정규화
void Vector::Normalize(void) {
    float m = Magnitude();
    if (m <= TOLERANCE) m = 1.0f;
    x /= m;
    y /= m;
    z /= m;
    
    if (std::fabs(x) < TOLERANCE) x = 0.0f;
    if (std::fabs(y) < TOLERANCE) y = 0.0f;
    if (std::fabs(z) < TOLERANCE) z = 0.0f;
}

// 벡터의 방향을 반대로
void Vector::Reverse(void) {
    x = -x;
    y = -y;
    z = -z;
}

// 벡터 덧셈 대입 연산자
Vector& Vector::operator+=(const Vector& u) {
    x += u.x;
    y += u.y;
    z += u.z;
    return *this;
}

// 벡터 뺄셈 대입 연산자
Vector& Vector::operator-=(const Vector& u) {
    x -= u.x;
    y -= u.y;
    z -= u.z;
    return *this;
}

// 스칼라 곱셈 대입 연산자
Vector& Vector::operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

// 스칼라 나눗셈 대입 연산자
Vector& Vector::operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

// 음수 벡터 연산자
Vector Vector::operator-(void) const {
    return Vector(-x, -y, -z);
}

// 벡터 덧셈 연산자
Vector operator+(const Vector& u, const Vector& v) {
    return Vector(u.x + v.x, u.y + v.y, u.z + v.z);
}

// 벡터 뺄셈 연산자
Vector operator-(const Vector& u, const Vector& v) {
    return Vector(u.x - v.x, u.y - v.y, u.z - v.z);
}

// 외적
Vector operator^(const Vector& u, const Vector& v) {
    return Vector(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

// 내적
float operator*(const Vector& u, const Vector& v) {
    return (u.x * v.x + u.y * v.y + u.z * v.z);
}

// 스칼라 곱셈 연산자
Vector operator*(const Vector& u, float s) {
    return Vector(u.x * s, u.y * s, u.z * s);
}

Vector operator*(float s, const Vector& u) {
    return Vector(u.x * s, u.y * s, u.z * s);
}

// 스칼라 나눗셈 연산자
Vector operator/(const Vector& u, float s) {
    return Vector(u.x / s, u.y / s, u.z / s);
}

// 스칼라 삼중곱
float ScalarTripleProduct(const Vector& u, const Vector& v, const Vector& w) {
    return float(u * (v ^ w));  // (u dot (v cross w))
}

// 벡터 삼중곱
Vector VectorTripleProduct(const Vector& u, const Vector& v, const Vector& w) {
    return u ^ (v ^ w);  // u cross (v cross w)
}
