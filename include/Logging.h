#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Quaternion.h"
#include "Vector.h"

// 로그 출력용 함수 (파일로만 출력)
void logPrint(std::ostream& outStream, const std::string& message);

// 콘솔과 파일에 동시에 출력하는 함수
void logAndPrint(std::ostream& outStream, const std::string& message);

// 로그 파일 이름 생성 함수
std::string createLogFileName(const std::string& projectName, const std::string& functionName);

// Quaternion과 Vector 출력용 함수
void printQuaternion(std::ostream& outStream, const Quaternion& q, const std::string& name);
void printVector(std::ostream& outStream, const Vector& v, const std::string& name);

#endif // LOGGER_H
