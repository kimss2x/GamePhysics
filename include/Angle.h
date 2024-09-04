#ifndef ANGLE_H
#define ANGLE_H

#include <iostream>
#include "Constants.h"

namespace Angle {

    // 각도를 라디안으로 변환
    template<typename T>
    T degToRad(T deg);
    // 라디안을 각도로 변환
    template<typename T>
    T radToDeg(T rad);

} // namespace Angle

#endif // ANGLE_H
