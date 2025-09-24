//
// Created by jose_alberto on 19/09/2025.
//

#include "../MyApp.h"
#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Mesh::Mesh() : VAO(0), VBO(0), shaderProgram(0), color(1, 1, 1, 1){
    SetupMesh(); // Configura buffers OpenGl
    SetupShader(); // Compila e linka shaders
};

Mesh::Mesh(const std::vector<float> &verts) : vertices(verts), VAO(0), VBO(0), shaderProgram(0), color(1, 1, 1, 1){
    SetupMesh(); // Configura buffers OpenGl
    SetupShader(); // Compila e linka shaders
}

Mesh::~Mesh() {
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (shaderProgram) glDeleteProgram(shaderProgram);
}

void Mesh::DefineProjection() const{
    float aspect = static_cast<float>(Application::width) / static_cast<float>(Application::height);
    glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);

    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Mesh::Draw() const {
    //Ativa o programa de shader
    glUseProgram(shaderProgram);

    DefineProjection();

    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");

    GLint colorLoc = glGetUniformLocation(shaderProgram, "uColor");
    glUniform4fv(colorLoc, 1, &color[0]);

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(Model()));
    glBindVertexArray(VAO);//Vincula o VAO do mesh

    Render();
}

void Mesh::Render() const{
    // Renderiza os triângulos (3 componentes por vétice, dividido por 3 para número de  vétices)
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size() / 3));
    glBindVertexArray(0);//Desvincula o VAO
}

mat4 Mesh::Model() const{
    mat4 model = glm::mat4(1.0f); // Matriz identidade

    model = translate(model, glm::vec3(transform.position.x, transform.position.y, transform.position.z));
    model = rotate(model, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
    model = scale(model, glm::vec3(transform.scale.x, transform.scale.y, transform.scale.z));

    return model;
}

void Mesh::SetColor(const glm::vec4 &_color) {
    this->color = _color;
}

void Mesh::Initialize() {
    SetupMesh();
    SetupShader();
}


void Mesh::SetupMesh() {

    //Gera VAO e VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO); // Vincula VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// Vincula VBO

    //Envia dados dos vétices para GPU
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);

    //Define layout dos atibrutos de vétices
    //Atributo 0: 3 componentes (x, y, z) do tipo float, sem normalização
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0); //Habilita o atributo 0

    // Limpa bindings (boas práticas)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Mesh::SetupShader() {
    const char* vertexShaderSource = R"(
                #version 330 core
                layout(location = 0) in vec3 aPos; // Atributo de vértice (posição)
                uniform mat4 model; // matriz de tranformação
                uniform mat4 projection;
                void main(){
                    gl_Position = projection * model * vec4(aPos, 1.0);
                }
            )";

    //Shader fragment: define cor fixa branca
    const char* fragmentShaderSource = R"(
                #version 330 core
                out vec4 FragColor; // Cor de saída
                uniform vec4 uColor;
                void main(){
                    FragColor = uColor; //Branco opaco
                }
            )";

    //Compila vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    CheckCompileErrors(vertexShader, "VERTEX"); //Verifica Erros

    // Compila fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    CheckCompileErrors(fragmentShader, "FRAGMENT"); // Veridica erros

    // Cria programa de shader e linka os shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    CheckCompileErrors(shaderProgram, "PROGRAM"); // Verifica erros de linking

    // Limpa shaders intermédiarios (já linkados no programa)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Mesh::CheckCompileErrors(GLuint shader, const std::string& type ) {
    GLint success;
    char infoLog[512]; // Buffer para mensagens de erro

    if (type != "PROGRAM") {
        // Verifica a compilação do shader
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << infoLog << std::endl;
        }
    }else {
        // Verifica linking do programa
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 512, nullptr, infoLog);
            std::cout << infoLog << std::endl;
        }
    }
}
