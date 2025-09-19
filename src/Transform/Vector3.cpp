//
// Created by jose_alberto on 19/09/2025.
//

#include "Vector3.h"
#include <cmath>

Vector3::Vector3(float X, float Y, float Z) : x(X), y(Y), z(Z){}

Vector3 Vector3::operator+(const Vector3 &other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(const float scale) const {
    return Vector3(x * scale, y * scale, z * scale);
}

Vector3 &Vector3::operator+=(const Vector3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vector3 Vector3::rotateZ(float angleDegress) const {
    float rad = angleDegress * 3.14159265359f / 180.0f;
    float cosTheta = std::cos(rad);
    float sinTheta = std::sin(rad);

    return Vector3(
        x * cosTheta - y * sinTheta,
        y * cosTheta + x * sinTheta,
        z
    );
}
