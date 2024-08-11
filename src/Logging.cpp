#include "Logging.h"
#include <ctime>  // for std::time and std::localtime
#include <iomanip>  // for std::setprecision

void logPrint(std::ostream& outStream, const std::string& message) {
    outStream << message << std::endl;
}

void logAndPrint(std::ostream& outStream, const std::string& message) {
    logPrint(outStream, message);
    std::cout << message << std::endl;
}

std::string createLogFileName(const std::string& projectName, const std::string& functionName) {
    std::time_t t = std::time(nullptr);
    char date[100];
    std::strftime(date, sizeof(date), "%Y-%m-%d", std::localtime(&t));

    std::string logFileName = "log/" + projectName + "_" + date + "_" + functionName + "_log.txt";
    return logFileName;
}

template<typename T>
void printQuaternion(std::ostream& outStream, const Quaternion<T>& q, const std::string& name) {
    logAndPrint(outStream, name + ": (" + std::to_string(q.GetScalar()) + ", " + std::to_string(q.GetVector().x) + ", " + std::to_string(q.GetVector().y) + ", " + std::to_string(q.GetVector().z) + ")");
}

template<typename T>
void printVector3(std::ostream& outStream, const Vector3<T>& v, const std::string& name) {
    logAndPrint(outStream, name + ": (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")");
}

template<typename T>
void printVector4(std::ostream& outStream, const Vector4<T>& v, const std::string& name) {
    logAndPrint(outStream, name + ": (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ", " + std::to_string(v.w) + ")");
}

template<typename T>
void printMatrix3x3(std::ostream& outStream, const Matrix3x3<T>& m, const std::string& name) {
    logAndPrint(outStream, name + ":\n" +
                  std::to_string(m.e11) + " " + std::to_string(m.e12) + " " + std::to_string(m.e13) + "\n" +
                  std::to_string(m.e21) + " " + std::to_string(m.e22) + " " + std::to_string(m.e23) + "\n" +
                  std::to_string(m.e31) + " " + std::to_string(m.e32) + " " + std::to_string(m.e33));
}

template<typename T>
void printMatrix4x4(std::ostream& outStream, const Matrix4x4<T>& m, const std::string& name) {
    logAndPrint(outStream, name + ":\n" +
                  std::to_string(m.e11) + " " + std::to_string(m.e12) + " " + std::to_string(m.e13) + " " + std::to_string(m.e14) + "\n" +
                  std::to_string(m.e21) + " " + std::to_string(m.e22) + " " + std::to_string(m.e23) + " " + std::to_string(m.e24) + "\n" +
                  std::to_string(m.e31) + " " + std::to_string(m.e32) + " " + std::to_string(m.e33) + " " + std::to_string(m.e34) + "\n" +
                  std::to_string(m.e41) + " " + std::to_string(m.e42) + " " + std::to_string(m.e43) + " " + std::to_string(m.e44));
}

// 템플릿 인스턴스화
template void printQuaternion<float>(std::ostream& outStream, const Quaternion<float>& q, const std::string& name);
template void printQuaternion<double>(std::ostream& outStream, const Quaternion<double>& q, const std::string& name);

template void printVector3<float>(std::ostream& outStream, const Vector3<float>& v, const std::string& name);
template void printVector3<double>(std::ostream& outStream, const Vector3<double>& v, const std::string& name);

template void printVector4<float>(std::ostream& outStream, const Vector4<float>& v, const std::string& name);
template void printVector4<double>(std::ostream& outStream, const Vector4<double>& v, const std::string& name);

template void printMatrix3x3<float>(std::ostream& outStream, const Matrix3x3<float>& m, const std::string& name);
template void printMatrix3x3<double>(std::ostream& outStream, const Matrix3x3<double>& m, const std::string& name);

template void printMatrix4x4<float>(std::ostream& outStream, const Matrix4x4<float>& m, const std::string& name);
template void printMatrix4x4<double>(std::ostream& outStream, const Matrix4x4<double>& m, const std::string& name);
