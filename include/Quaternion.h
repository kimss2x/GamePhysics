#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector4.h"

template<typename T>
class Quaternion {
public:
    T n;
    Vector3<T> v;

    // 기본 생성자
    Quaternion(void);

    // 매개변수가 있는 생성자
    Quaternion(T e0, T e1, T e2, T e3);

    // 크기 계산
    T Magnitude(void) const;

    // 벡터 부분 반환
    Vector3<T> GetVector(void) const;

    // 스칼라 부분 반환
    T GetScalar(void) const;

    // 쿼터니언 합: += 연산자
    Quaternion& operator+=(const Quaternion& q);

    // 쿼터니언 뺄셈: -= 연산자
    Quaternion& operator-=(const Quaternion& q);

    // 쿼터니언 곱: *= 연산자
    Quaternion& operator*=(T s);

    // 쿼터니언 나눗셈: /= 연산자
    Quaternion& operator/=(T s);

    // 켤레: ~ 연산자
    Quaternion operator~(void) const;

    // 쿼터니언 합: + 연산자
    friend Quaternion operator+(const Quaternion& q1, const Quaternion& q2) {
        return Quaternion(
            q1.n + q2.n,
            q1.v.x + q2.v.x,
            q1.v.y + q2.v.y,
            q1.v.z + q2.v.z
        );
    }

    // 쿼터니언 뺄셈: - 연산자
    friend Quaternion operator-(const Quaternion& q1, const Quaternion& q2) {
        return Quaternion(
            q1.n - q2.n,
            q1.v.x - q2.v.x,
            q1.v.y - q2.v.y,
            q1.v.z - q2.v.z
        );
    }

    // 쿼터니언 곱: * 연산자
    friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
        T new_n = q1.n * q2.n - q1.v.x * q2.v.x - q1.v.y * q2.v.y - q1.v.z * q2.v.z;
        Vector3<T> new_v(
            q1.n * q2.v.x + q1.v.x * q2.n + q1.v.y * q2.v.z - q1.v.z * q2.v.y,
            q1.n * q2.v.y - q1.v.x * q2.v.z + q1.v.y * q2.n + q1.v.z * q2.v.x,
            q1.n * q2.v.z + q1.v.x * q2.v.y - q1.v.y * q2.v.x + q1.v.z * q2.n
        );
        return Quaternion(new_n, new_v.x, new_v.y, new_v.z);
    }

    // 스칼라 곱: * 연산자
    friend Quaternion operator*(const Quaternion& q, T s) {
        return Quaternion(q.n * s, q.v.x * s, q.v.y * s, q.v.z * s);
    }

    friend Quaternion operator*(T s, const Quaternion& q) {
        return Quaternion(q.n * s, q.v.x * s, q.v.y * s, q.v.z * s);
    }

    // 벡터 곱: * 연산자
    friend Quaternion operator*(const Quaternion& q, const Vector3<T>& v) {
        return Quaternion(
            -(q.v.x * v.x + q.v.y * v.y + q.v.z * v.z),
            q.n * v.x + q.v.y * v.z - q.v.z * v.y,
            q.n * v.y + q.v.z * v.x - q.v.x * v.z,
            q.n * v.z + q.v.x * v.y - q.v.y * v.x
        );
    }

    friend Quaternion operator*(const Vector3<T>& v, const Quaternion& q) {
        return Quaternion(
            -(q.v.x * v.x + q.v.y * v.y + q.v.z * v.z),
            q.n * v.x + q.v.y * v.z - q.v.z * v.y,
            q.n * v.y + q.v.z * v.x - q.v.x * v.z,
            q.n * v.z + q.v.x * v.y - q.v.y * v.x
        );
    }

    // 스칼라 나눗셈: / 연산자
    friend Quaternion operator/(const Quaternion& q, T s) {
        return Quaternion(q.n / s, q.v.x / s, q.v.y / s, q.v.z / s);
    }

    // QGetAngle: 회전 각도 반환
    T QGetAngle(void) const;

    // QGetAxis: 회전 축 반환
    Vector3<T> QGetAxis(void) const;

    // QRotate: 벡터 회전
    Vector3<T> QRotate(const Vector3<T>& v) const;

    // QVRotate: 벡터를 사용하여 쿼터니언 회전
    static Quaternion QVRotate(const Vector3<T>& axis, T angle);

    // MakeQFromEulerAngles: 오일러 각도로부터 쿼터니언 생성
    static Quaternion MakeQFromEulerAngles(T pitch, T yaw, T roll);

    // MakeEulerAnglesFromQ: 쿼터니언으로부터 오일러 각도 반환
    Vector3<T> MakeEulerAnglesFromQ(void) const;

    // 회전 순서에 따른 회전 적용
    Quaternion ApplyRotationOrder(const std::string& order, const Vector3<T>& angles) const;

    template<typename T>
    Quaternion(const Vector4<T>& v) : n(v.w), v(v.x, v.y, v.z) {}

};

#include "Quaternion.cpp"

#endif // QUATERNION_H
