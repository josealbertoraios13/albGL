//
// Created by jose_alberto on 19/09/2025.
//

#ifndef ALBGL_MESH_H
#define ALBGL_MESH_H

#pragma once

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include "../Transform/Transform.h"

class Mesh {
    public:
        std::vector<float> vertices; //Lista de vétices no formato (x, y, z)
        GLuint VAO; // Identificadores do Vertex Array Object e vertex Buffer Object
        GLuint VBO;
        GLuint shaderProgram; // Identificador do programa de shader
        Transform transform; // Objeto de transformação (posição, rotação, escala)

        //Construtor: inicializa o mesh com vértices fornecidos
        Mesh(const std::vector<float>& verts);

        // Libera dados da memória evitando o memory leaks
        ~Mesh();

        //Desenha o mesh na tela aplicando as transformações
        void Draw() const;

    private:
        void DefineProjection() const;
        //Configura os buffers de vétices (VBO) e o vertex array (VAO)
        void SetupMesh();

        // Compila e linka os shaders vertex e fragment
        void SetupShader();

        // Verifica erros de compilação/liking de shaders
        static void CheckCompileErrors(GLuint shader, const std::string &type);

};


#endif //ALBGL_MESH_H