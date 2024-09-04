#ifndef ANGLE_CPP
#define ANGLE_CPP

#include "Angle.h"
#include "Constants.h"

namespace Angle {

    template<typename T>
    T degToRad(T deg) {
        return deg * Constants<T>::PI / static_cast<T>(180.0);
    }

    template<typename T>
    T radToDeg(T rad) {
        return rad * static_cast<T>(180.0) / Constants<T>::PI;
    }

    // 템플릿 인스턴스화
    template float degToRad<float>(float deg);
    template double degToRad<double>(double deg);

    template float radToDeg<float>(float rad);
    template double radToDeg<double>(double rad);

} // namespace Angle

#endif // ANGLE_CPP