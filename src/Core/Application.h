//
// Created by jose_alberto on 18/09/2025.
//

#ifndef ALBGL_APPLICATION_H
#define ALBGL_APPLICATION_H

#pragma once

#include <list>
#include <SDL.h>
#include "../primitiveObjects/Mesh.h"

using namespace std;

struct ImGuiIO;

class Application {
    public:
        static list<Mesh*> m_Meshes;
        static int width;
        static int height;
        Application();
        virtual ~Application();

        // Inicializa todos os sistemas e retorna o loop principal
        // Retorna o código de saída do programa
        int Run();

        //Para ser implementado pelo usuário
        virtual void Start(){};
        virtual void Update(float deltaTime){};

        // Métodos de utilidades para acessar dados da aplicação
        SDL_Window* GetWindow() const {return m_Window; }
        float GetTime() const {return m_Time; }

        static void setWindowSize(int _width, int _height);

        //Para o editor
        static void HierarchyMenu(const list<Mesh*> &objects, bool enable = true);
        static void InspectorMenu(Mesh &obj, bool enable = true);
        static void DebugMenu(bool enable = true);

    private:
        // Métodos internos para inicialização e limpeza
        bool Initialize();
        void Shutdown() const;

        // Métodos do loop principal
        void ProcessEvents();
        static void BeginFrame();
        void EndFrame() const;

    private:
        // Estado da aplicação
        bool m_Running = true;
        float m_Time = 0.0f;
        float m_DeltaTime = 0.0f;

        // Handles do SDL e OpenGL
        SDL_Window* m_Window = nullptr;
        SDL_GLContext m_GLContext = nullptr;

        // Contexto do ImGui
        ImGuiIO* m_ImGuiIO = nullptr;
};


#endif //ALBGL_APPLICATION_H