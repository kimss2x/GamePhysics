#include "Angle.h"
#include <cmath> // M_PI를 사용하기 위해 필요

template<typename T>
T DegToRad(T deg) {
    return deg * static_cast<T>(M_PI) / static_cast<T>(180.0);
}

template<typename T>
T RadToDeg(T rad) {
    return rad * static_cast<T>(180.0) / static_cast<T>(M_PI);
}

// 템플릿의 특성상, 구현 파일에서 템플릿 함수를 명시적으로 인스턴스화하는 것이 필요할 수 있습니다.
template float DegToRad<float>(float deg);
template double DegToRad<double>(double deg);

template float RadToDeg<float>(float rad);
template double RadToDeg<double>(double rad);
