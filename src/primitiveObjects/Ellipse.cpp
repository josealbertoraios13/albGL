//
// Created by jose_alberto on 23/09/2025.
//

#include "Ellipse.h"
#include <cmath>

#include "../Core/Application.h"

using namespace std;

Ellipse::Ellipse() {
    // --- Cria vértices unitários ---
    vertices.clear();
    vertices.push_back(0.0f); // centro x
    vertices.push_back(0.0f); // centro y
    vertices.push_back(0.0f); // centro z

    int segments = 180;
    float angleStep = 2.0f * M_PI / segments;

    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        float x = 0.5f * cos(angle);
        float y = 0.5f * sin(angle);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
    }

    SetName("newEllipse");

    // --- Agora inicializa o VAO/VBO ---
    Initialize();
}
void Ellipse::Render() const{
    // Renderiza os triângulos (3 componentes por vétice, dividido por 3 para número de  vétices)
    glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(vertices.size() / 3));
    glBindVertexArray(0);//Desvincula o VAO
}



