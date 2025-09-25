//
// Created by jose_alberto on 18/09/2025.
//
#include "MyApp.h"
#include "primitiveObjects/Mesh.h"
#include <glm/vec3.hpp>

#include "primitiveObjects/Ellipse.h"
#include "primitiveObjects/Rectangle.h"
#include "primitiveObjects/Triangle.h"

#include <memory> // necessário para std::shared_ptr

std::shared_ptr<Triangle> triangle;
std::shared_ptr<Rectangle> rectangle;
std::shared_ptr<Rectangle> post;
std::shared_ptr<Ellipse> circle;

void MyApp::Start() {
    rectangle = std::make_shared<Rectangle>();
    rectangle->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.f));
    rectangle->transform.scale = Vector3(0.5f, 0.5f, 0.5f);

    post = std::make_shared<Rectangle>();
    post->SetName("rec2");
    post->SetColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.f));
    post->transform.scale = Vector3(0.25f, 1.0f, 0.5f);
    post->transform.position = Vector3(0.0f, 1000.0f, 0.0f);

    triangle = std::make_shared<Triangle>();
    triangle->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.f));
    triangle->transform.position = Vector3(0.0f, 1150.0f, 0);

    circle = std::make_shared<Ellipse>();
    circle->SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.f));
    circle->transform.position = Vector3(0.0f, -1150.0f, 0.0f);

    rectangle->AddChild(triangle);
    rectangle->AddChild(circle);
    triangle->AddChild(post);
}


void MyApp::Update(float deltaTime) {
    rectangle->Draw();
}
