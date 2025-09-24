//
// Created by jose_alberto on 19/09/2025.
//

#ifndef ALBGL_MESH_H
#define ALBGL_MESH_H

#pragma once

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <glm/fwd.hpp>
#include <glm/vec4.hpp>

#include "../Transform/Transform.h"

using namespace glm;

class Mesh {
    public:
        std::vector<float> vertices; //Lista de vétices no formato (x, y, z)
        GLuint VAO; // Identificadores do Vertex Array Object e vertex Buffer Object
        GLuint VBO;
        GLuint shaderProgram; // Identificador do programa de shader
        Transform transform; // Objeto de transformação (posição, rotação, escala)
        glm::vec4 color;

        Mesh();

        //Construtor: inicializa o mesh com vértices fornecidos
        explicit Mesh(const std::vector<float>& verts);

        // Libera dados da memória evitando o memory leaks
        virtual ~Mesh();

        //Desenha o mesh na tela aplicando as transformações
        void Draw() const;

        void SetColor(const glm::vec4& _color);
        void Initialize();

    protected:
        virtual void Render() const;
        void DefineProjection() const;
        //Configura os buffers de vétices (VBO) e o vertex array (VAO)
        void SetupMesh();

        // Compila e linka os shaders vertex e fragment
        void SetupShader();

    private:
        mat4 Model() const;

        // Verifica erros de compilação/liking de shaders
        static void CheckCompileErrors(GLuint shader, const std::string &type);

};


#endif //ALBGL_MESH_H