//
// Created by jose_alberto on 18/09/2025.
//
#include "MyApp.h"
#include "primitiveObjects/Mesh.h"
#include <imgui.h>
#include <glm/vec3.hpp>

#include "primitiveObjects/Ellipse.h"
#include "primitiveObjects/Rectangle.h"
#include "primitiveObjects/Triangle.h"

Triangle* triangle;
Rectangle* rectangle;
Ellipse* circle;
Vector3 position;

void MyApp::Start() {
    triangle = new Triangle();
    triangle->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    triangle->transform.scale = Vector3(0.5f, 0.5f, 0.5f);
    rectangle = new Rectangle();
    rectangle->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    rectangle->transform.scale = Vector3(0.5f, 0.5f, 0.5f);
    circle = new Ellipse();
    circle->SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    circle->transform.scale = Vector3(0.5f, 0.5f, 0.5f);
}

void DebugMenu() {
    ImGui::SetNextWindowSize(ImVec2(300, 140));
    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoResize);
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("FPS: %.1f", io.Framerate);
    ImGui::End();
}

/*void InspectorMenu() {
    ImGui::SetNextWindowSize(ImVec2(300, 600));
    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoResize);
    ImGui::LabelText("", "Transform: ");
    ImGui::LabelText("Position:", "");
    ImGui::LabelText("", "X: ");
    ImGui::SameLine();
    ImGui::InputFloat("##X:", &x);
    ImGui::SliderFloat("##x", &x, -2000.0f, 2000.0f);
    ImGui::LabelText("", "Y: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Y:", &y);
    ImGui::SliderFloat("##y", &y, -2000.0f, 2000.0f);
    ImGui::LabelText("", "Z: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Z:", &z);
    ImGui::SliderFloat("##z", &z, -2000.0f, 2000.0f);

    ImGui::LabelText("Rotation:", "");
    ImGui::LabelText("", "rX: ");
    ImGui::SameLine();
    ImGui::InputFloat("##rX:", &rx);
    ImGui::LabelText("", "rY: ");
    ImGui::SameLine();
    ImGui::InputFloat("##rY:", &ry);
    ImGui::LabelText("", "rZ: ");
    ImGui::SameLine();
    ImGui::InputFloat("##rZ:", &rz);
    ImGui::SliderFloat("##rz", &rz, -360.0f, 360.0f);

    ImGui::LabelText("Scales:", "");
    ImGui::LabelText("", "Width: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Width:", &sx);
    ImGui::SliderFloat("##Width", &sx, -10.0f, 10.0f);
    ImGui::LabelText("", "Height: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Height:", &sy);
    ImGui::SliderFloat("##Height", &sy, -10.0f, 10.0f);
    ImGui::LabelText("", "Forward: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Forward:", &sz);

    ImGui::End();
}*/

void MyApp::Update(float deltaTime) {
    triangle->Draw();
    rectangle->Draw();
    circle->Draw();
    rectangle->transform.position = Vector3(0.8f, 0.0f, 0.0f);
    circle->transform.position = Vector3(-0.8f, 0.0f, 0.0f);
    DebugMenu();
}
