#ifndef LOGGING_H
#define LOGGING_H

#include <iostream>
#include <string>
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

// 로그 출력용 함수 (파일로만 출력)
void logPrint(std::ostream& outStream, const std::string& message);

// 콘솔과 파일에 동시에 출력하는 함수
void logAndPrint(std::ostream& outStream, const std::string& message);

// 로그 파일 이름 생성 함수
std::string createLogFileName(const std::string& projectName, const std::string& functionName);

// Quaternion과 Vector, Matrix 출력용 함수 템플릿
template<typename T>
void printQuaternion(std::ostream& outStream, const Quaternion<T>& q, const std::string& name);

template<typename T>
void printVector3(std::ostream& outStream, const Vector3<T>& v, const std::string& name);

template<typename T>
void printVector4(std::ostream& outStream, const Vector4<T>& v, const std::string& name);

template<typename T>
void printMatrix3x3(std::ostream& outStream, const Matrix3x3<T>& m, const std::string& name);

template<typename T>
void printMatrix4x4(std::ostream& outStream, const Matrix4x4<T>& m, const std::string& name);

#endif // LOGGING_H
