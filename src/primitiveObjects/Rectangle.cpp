//
// Created by jose_alberto on 23/09/2025.
//

#include "Rectangle.h"

#include "../Core/Application.h"

Rectangle::Rectangle() : Mesh({-0.5f, 0.5f, 0.0f,
                               0.5f, 0.5f, 0.0f,
                              -0.5f, -0.5f, 0.0f,
                               0.5f, 0.5f, 0.0f,
                              -0.5f, -0.5f, 0.0f,
                               0.5f, -0.5f, 0.0f}) {
    SetName("newRectangle");
}

