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

#include  <memory>

#include "../Transform/Transform.h"

using namespace glm;
using namespace std;

class Mesh {
    public:
        std::vector<float> vertices; //Lista de vétices no formato (x, y, z)
        GLuint VAO; // Identificadores do Vertex Array Object e vertex Buffer Object
        GLuint VBO;
        GLuint shaderProgram; // Identificador do programa de shader
        Transform transform; // Objeto de transformação (posição, rotação, escala)
        glm::vec4 color;
        vector<shared_ptr<Mesh>> children;

        Mesh();

        //Construtor: inicializa o mesh com vértices fornecidos
        explicit Mesh(const std::vector<float>& verts);

        // Libera dados da memória evitando o memory leaks
        virtual ~Mesh();

        //Desenha o mesh na tela aplicando as transformações
        void Draw() const;
        void DrawWithParent(const glm::mat4 &parentModel) const;

        void SetColor(const vec4& _color);

        void SetName(const string &_name);
        string GetName() const;

        void AddChild(const shared_ptr<Mesh> &child);
        void RemoveChild(const shared_ptr<Mesh> &child);

        void Initialize();

    protected:
        string name;

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