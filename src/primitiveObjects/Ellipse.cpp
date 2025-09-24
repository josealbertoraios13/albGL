//
// Created by jose_alberto on 23/09/2025.
//

#include "Ellipse.h"
#include <cmath>

using namespace std;

Ellipse::Ellipse() {
    vector<float> verts;
    //Center
    verts.push_back(0.0f);
    verts.push_back(0.0f);
    verts.push_back(0.0f);

    int segments = 180;
    float angleStep = 0;
    angleStep = static_cast<float>(2.0f * M_PI / segments);

    for (int i = 0; i <= segments; i++) {
        float angle = static_cast<float>(i) * angleStep;
        float x = this->transform.scale.x / 2 * cos(angle);
        float y = this->transform.scale.y / 2 * sin(angle);

        verts.push_back(x);
        verts.push_back(y);
        verts.push_back(0.0f);
    }

    this->vertices = verts;

    SetName("newEllipse");

    Initialize();
}

void Ellipse::SetName(const string &_name) {
    this->name = _name;
}

string Ellipse::GetName() {
    return this->name;
}

void Ellipse::Render() const{
    // Renderiza os triângulos (3 componentes por vétice, dividido por 3 para número de  vétices)
    glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(vertices.size() / 3));
    glBindVertexArray(0);//Desvincula o VAO
}



