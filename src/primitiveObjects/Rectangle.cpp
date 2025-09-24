//
// Created by jose_alberto on 23/09/2025.
//

#include "Rectangle.h"

Rectangle::Rectangle() : Mesh({-0.5f, 0.5f, 0.0f,
                               0.5f, 0.5f, 0.0f,
                              -0.5f, -0.5f, 0.0f,
                               0.5f, 0.5f, 0.0f,
                              -0.5f, -0.5f, 0.0f,
                               0.5f, -0.5f, 0.0f}) {
    SetName("newRectangle");
}

void Rectangle::SetName(const string &_name) {
    this->name = _name;
}

string Rectangle::GetName() {
    return this->name;
}

