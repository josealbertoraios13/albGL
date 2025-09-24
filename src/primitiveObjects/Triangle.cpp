//
// Created by jose_alberto on 22/09/2025.
//

#include "Triangle.h"

Triangle::Triangle() : Mesh({-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f}){
    SetName("newTriangle");
}

void Triangle::SetName(const std::string &_name) {
    this->name = _name;
}

string Triangle::GetName() {
    return this->name;
}





