#include "Angle.h"
#include "Constants.h"

template<typename T>
T DegToRad(T deg) {
    return deg * Constants<T>::PI / static_cast<T>(180.0);
}

template<typename T>
T RadToDeg(T rad) {
    return rad * static_cast<T>(180.0) / Constants<T>::PI;
}

// 템플릿 인스턴스화
template float DegToRad<float>(float deg);
template double DegToRad<double>(double deg);

template float RadToDeg<float>(float rad);
template double RadToDeg<double>(double rad);
