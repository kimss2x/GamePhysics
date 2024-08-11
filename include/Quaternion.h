#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"

class Quaternion {
public:
    float n;
    Vector v;

    // 기본 생성자
    Quaternion(void);

    // 매개변수가 있는 생성자
    Quaternion(float e0, float e1, float e2, float e3);

    // 크기 계산
    float Magnitude(void) const;

    // 벡터 부분 반환
    Vector GetVector(void) const;

    // 스칼라 부분 반환
    float GetScalar(void) const;

    // 쿼터니언 합: += 연산자
    Quaternion& operator+=(const Quaternion& q);

    // 쿼터니언 뺄셈: -= 연산자
    Quaternion& operator-=(const Quaternion& q);

    // 쿼터니언 곱: *= 연산자
    Quaternion& operator*=(float s);

    // 쿼터니언 나눗셈: /= 연산자
    Quaternion& operator/=(float s);

    // 켤레: ~ 연산자
    Quaternion operator~(void) const;

    // 쿼터니언 합: + 연산자
    friend Quaternion operator+(const Quaternion& q1, const Quaternion& q2);

    // 쿼터니언 뺄셈: - 연산자
    friend Quaternion operator-(const Quaternion& q1, const Quaternion& q2);

    // 쿼터니언 곱: * 연산자
    friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

    // 스칼라 곱: * 연산자
    friend Quaternion operator*(const Quaternion& q, float s);
    friend Quaternion operator*(float s, const Quaternion& q);

    // 벡터 곱: * 연산자
    friend Quaternion operator*(const Quaternion& q, const Vector& v);
    friend Quaternion operator*(const Vector& v, const Quaternion& q);

    // 스칼라 나눗셈: / 연산자
    friend Quaternion operator/(const Quaternion& q, float s);

    // QGetAngle: 회전 각도 반환
    float QGetAngle(void) const;

    // QGetAxis: 회전 축 반환
    Vector QGetAxis(void) const;

    // QRotate: 벡터를 회전
    Vector QRotate(const Vector& v) const;

    // QVRotate: 벡터를 사용하여 쿼터니언 회전
    static Quaternion QVRotate(const Vector& axis, float angle);

    // MakeQFromEulerAngles: 오일러 각도로부터 쿼터니언 생성
    static Quaternion MakeQFromEulerAngles(float pitch, float yaw, float roll);

    // MakeEulerAnglesFromQ: 쿼터니언으로부터 오일러 각도 반환
    Vector MakeEulerAnglesFromQ(void) const;
};

// 각도 변환 함수: DegToRad, RadToDeg
float DegToRad(float deg);
float RadToDeg(float rad);

#endif // QUATERNION_H
