//
// Created by jose_alberto on 18/09/2025.
//
#include "MyApp.h"
#include <imgui.h>
#include <GL/glew.h>
#include <iostream>

void MyApp::Start() {
    // 1. Vertices do triângulo
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // 2. Criar VAO/VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 3. Shader mínimo
    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0, 1.0, 1.0, 1.0); // branco
        }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Erro Vertex Shader:\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Erro Fragment Shader:\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Erro Shader Program:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void DebugMenu() {
    ImGui::SetNextWindowSize(ImVec2(300, 140));
    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoResize);
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("FPS: %.1f", io.Framerate);
    ImGui::End();
}

void InspectorMenu() {
    float value = 0;
    ImGui::SetNextWindowSize(ImVec2(300, 600));
    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoResize);
    ImGui::LabelText("", "Transform: ");
    ImGui::LabelText("Positions:", "");
    ImGui::LabelText("", "X: ");
    ImGui::SameLine();
    ImGui::InputFloat("##X:", &value);
    ImGui::LabelText("", "Y: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Y:", &value);
    ImGui::LabelText("", "Z: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Z:", &value);

    ImGui::End();
}

void MyApp::Update(float deltaTime) {

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    InspectorMenu();
    DebugMenu();
}
