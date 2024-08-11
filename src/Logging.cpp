#include <ctime>
#include "Logging.h"

void logPrint(std::ostream& outStream, const std::string& message) {
    outStream << message << std::endl;
}

void logAndPrint(std::ostream& outStream, const std::string& message) {
    // 파일로 출력
    logPrint(outStream, message);
    // 콘솔에도 출력
    std::cout << message << std::endl;
}

void printQuaternion(std::ostream& outStream, const Quaternion& q, const std::string& name) {
    logAndPrint(outStream, name + ": (" + std::to_string(q.n) + ", " + std::to_string(q.v.x) + ", " + std::to_string(q.v.y) + ", " + std::to_string(q.v.z) + ")");
}

void printVector(std::ostream& outStream, const Vector& v, const std::string& name) {
    logAndPrint(outStream, name + ": (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")");
}

std::string createLogFileName(const std::string& projectName, const std::string& functionName) {
    // 현재 날짜와 시간을 얻기 위한 변수
    std::time_t t = std::time(nullptr);
    char date[100];
    std::strftime(date, sizeof(date), "%Y-%m-%d", std::localtime(&t));

    // 로그 파일의 이름을 생성
    std::string logFileName = "log/" + projectName + "_" + date + "_" + functionName + "_log.txt";
    return logFileName;
}
