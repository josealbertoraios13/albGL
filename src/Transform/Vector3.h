//
// Created by jose_alberto on 19/09/2025.
//

#ifndef ALBGL_VECTOR3_H
#define ALBGL_VECTOR3_H
#pragma once

class Vector3 {
    public:
        float x, y, z;
    Vector3(float X = 0.0f, float Y = 0.0f, float Z = 0.0f);

    Vector3 operator+(const Vector3& other) const;

    Vector3 operator-(const Vector3& other) const;

    Vector3 operator*(const float scale) const;

    Vector3& operator+=(const Vector3& other);

    Vector3 rotateZ(float angleDegress) const;
};


#endif //ALBGL_VECTOR3_H