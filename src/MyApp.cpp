//
// Created by jose_alberto on 18/09/2025.
//
#include "MyApp.h"
#include "primitiveObjects/Mesh.h"
#include <imgui.h>
#include "Transform/Vector3.h"

float x, y, z;
float rx, ry, rz;
float sx = 1, sy = 1, sz = 1;


void MyApp::Start() {

}

void DebugMenu() {
    ImGui::SetNextWindowSize(ImVec2(300, 140));
    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoResize);
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("FPS: %.1f", io.Framerate);
    ImGui::End();
}

void InspectorMenu() {



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
}

void MyApp::Update(float deltaTime) {

    std::vector<float> triVerts = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    Mesh triangle(triVerts);
    triangle.transform.position = Vector3(x / 1000, y / 1000, z / 1000);
    triangle.transform.scale = Vector3(sx, sy, sz);
    triangle.transform.rotation = Vector3(rx, ry, rz);
    triangle.Draw();

    InspectorMenu();
    DebugMenu();
}
