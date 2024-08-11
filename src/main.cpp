#include <iostream>
#include <fstream>
#include "Quaternion.h"
#include "Vector.h"
#include "Logging.h"

int main() {
    // 프로젝트명과 함수명을 지정하여 로그 파일 이름 생성
    std::string logFileName = createLogFileName("GamePhysics", "main");

    // 로그 파일을 연다
    std::ofstream logFile(logFileName);

    // 테스트 코드 실행
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);
    
    // 쿼터니언 출력
    printQuaternion(logFile, q1, "Quaternion 1");
    printQuaternion(logFile, q2, "Quaternion 2");
    
    // 쿼터니언 합
    Quaternion qSum = q1 + q2;
    printQuaternion(logFile, qSum, "Sum of Quaternions");
    
    // 쿼터니언 차
    Quaternion qDiff = q1 - q2;
    printQuaternion(logFile, qDiff, "Difference of Quaternions");
    
    // 쿼터니언 곱
    Quaternion qProd = q1 * q2;
    printQuaternion(logFile, qProd, "Product of Quaternions");
    
    // 스칼라 곱
    Quaternion qScaled = q1 * 2.0f;
    printQuaternion(logFile, qScaled, "Scaled Quaternion");
    
    // 스칼라 나눗셈
    Quaternion qInvScaled = q1 / 2.0f;
    printQuaternion(logFile, qInvScaled, "Inverse Scaled Quaternion");
    
    // 켤레
    Quaternion qConjugate = ~q1;
    printQuaternion(logFile, qConjugate, "Conjugate of Quaternion 1");
    
    // 회전 각도 및 축
    float angle = q1.QGetAngle();
    Vector axis = q1.QGetAxis();
    logAndPrint(logFile, "Angle of Quaternion 1: " + std::to_string(angle));
    printVector(logFile, axis, "Axis of Quaternion 1");
    
    // 벡터 회전
    Vector v(1.0f, 0.0f, 0.0f);
    Vector vRotated = q1.QRotate(v);
    printVector(logFile, vRotated, "Rotated Vector");
    
    // 쿼터니언 생성 from Axis-Angle
    Quaternion qFromAxisAngle = Quaternion::QVRotate(Vector(0.0f, 1.0f, 0.0f), 90.0f);
    printQuaternion(logFile, qFromAxisAngle, "Quaternion from Axis-Angle");
    
    // 쿼터니언 생성 from Euler Angles
    Quaternion qFromEuler = Quaternion::MakeQFromEulerAngles(45.0f, 45.0f, 45.0f);
    printQuaternion(logFile, qFromEuler, "Quaternion from Euler Angles");
    
    // 오일러 각도 from 쿼터니언
    Vector eulerAngles = qFromEuler.MakeEulerAnglesFromQ();
    logAndPrint(logFile, "Euler Angles from Quaternion: Pitch=" + std::to_string(eulerAngles.x) + ", Yaw=" + std::to_string(eulerAngles.y) + ", Roll=" + std::to_string(eulerAngles.z));
    
    logFile.close();
    return 0;
}
