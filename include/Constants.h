#ifndef CONSTANTS_H
#define CONSTANTS_H

template<typename T>
struct Constants {
    static constexpr T PI = static_cast<T>(3.14159265358979323846);
    static constexpr T EULER = static_cast<T>(2.71828182845904523536);
    static constexpr T GRAVITY = static_cast<T>(9.80665);
    static constexpr T LIGHT_SPEED = static_cast<T>(299792458.0);
    static constexpr T TOLERANCE = static_cast<T>(1e-6);
};

#endif // CONSTANTS_H
