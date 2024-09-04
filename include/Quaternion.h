#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <limits>  // numeric_limits 사용을 위한 헤더 추가
#include "Angle.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

// 사원수 클래스 정의
template<typename T>
class Quaternion {
public:
    T n;  // 스칼라 부분
    Vector3<T> v;  // 벡터 부분

    // 기본 생성자
    Quaternion(void);

    // 매개변수가 있는 생성자
    Quaternion(T e0, T e1, T e2, T e3);

    // 크기 계산
    T magnitude(void) const;

    // 정규화
    void normalize(void);

    // Vector4에서 변환되는 생성자
    explicit Quaternion(const Vector4<T>& vec);

    // Vector4로 변환 메서드
    Vector4<T> toVector4() const;

    // 사원수를 3x3 회전 메트릭스로 변환
    Matrix3x3<T> toMatrix3x3() const;

    // 사원수를 4x4 회전 메트릭스로 변환
    Matrix4x4<T> toMatrix4x4() const;

    // 각속도에서 쿼터니언 생성
    static Quaternion fromAngularVelocity(const Vector3<T>& angularVelocity, T deltaTime);

    // QGetAngle: 회전 각도 반환
    T qGetAngle(void) const;

    // QGetAxis: 회전 축 반환
    Vector3<T> qGetAxis(void) const;

    // QRotate: 벡터 회전
    Vector3<T> qRotate(const Vector3<T>& v) const;

    // 벡터 부분 반환
    Vector3<T> getVector(void) const;

    // 스칼라 부분 반환
    T getScalar(void) const;

    // 연산자 오버로드
    Quaternion& operator+=(const Quaternion& q);
    Quaternion& operator-=(const Quaternion& q);
    Quaternion& operator*=(T s);
    Quaternion& operator/=(T s);

    // 켤레: ~ 연산자
    Quaternion operator~(void) const;

    // 쿼터니언 회전 생성
    static Quaternion qVRotate(const Vector3<T>& axis, T angle);

    // 오일러 각도로부터 쿼터니언 생성
    static Quaternion makeQFromEulerAngles(T pitch, T yaw, T roll);

    // 쿼터니언으로부터 오일러 각도 생성
    Vector3<T> makeEulerAnglesFromQ(void) const;

    // 회전 순서 적용
    Quaternion applyRotationOrder(const std::string& order, const Vector3<T>& angles) const;
};

// 템플릿 친구 함수 선언 (클래스 외부에서 템플릿으로 선언)
template<typename T>
Quaternion<T> operator+(const Quaternion<T>& q1, const Quaternion<T>& q2);

template<typename T>
Quaternion<T> operator-(const Quaternion<T>& q1, const Quaternion<T>& q2);

template<typename T>
Quaternion<T> operator*(const Quaternion<T>& q1, const Quaternion<T>& q2);

template<typename T>
Quaternion<T> operator*(const Quaternion<T>& q, T s);

template<typename T>
Quaternion<T> operator*(T s, const Quaternion<T>& q);

template<typename T>
Quaternion<T> operator/(const Quaternion<T>& q, T s);

template<typename T>
Quaternion<T> operator/(const Quaternion<T>& q1, const Quaternion<T>& q2);

template<typename T>
Vector3<T> operator*(const Matrix3x3<T>& m, const Quaternion<T>& q);

template<typename T>
Vector4<T> operator*(const Matrix4x4<T>& m, const Quaternion<T>& q);

#include "Quaternion.tpp"  // 템플릿 메서드 구현을 포함한 파일

#endif // QUATERNION_H