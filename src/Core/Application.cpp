//
// Created by jose_alberto on 18/09/2025.
//

//Application.cpp
#include "Application.h"

// Inclui headers do ImGui
#include <imgui.h>
#include <list>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include "../primitiveObjects/Mesh.h"

#include <GL/glew.h>

using namespace std;

list<Mesh*> Application::m_Meshes;
int Application::width = 800;   // valor inicial padrão
int Application::height = 600;

Application::Application() = default;

Application::~Application() {
    Shutdown();
}

int Application::Run() {

    //1. Inicialização
    if (!Initialize()) {
        SDL_Log("Falha na inicialização");
        return -1;
    }

    //2. Chama o Start() uma vez, para setup inicial do usuário
    Start();

    //3. Loop principal
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;

    while (m_Running) {
        last = now;

        // Calcula o deltaTime em segundos
        m_DeltaTime = static_cast<float>(static_cast<double>(now - last) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency()));

        //Fase de Processamento
        ProcessEvents(); // Processa Input SDL_Event

        //Fase de Renderização
        BeginFrame(); //Limpa o buffer, inicia frame ImGui

        //Para o editor (ImGui)
        HierarchyMenu(m_Meshes);
        DebugMenu();
        //Fase de Atualização
        // Chama o Update() definido pelo usuário,passando o deltaTime
        Update(m_DeltaTime);

        EndFrame();// Renderiza ImGui, swap buffers
    }

    //4. Limpeza
    Shutdown();
    return 0;
}

void Application::setWindowSize(int _width, int _height) {
    width = _width;
    height = _height;
}


bool Application::Initialize() {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return false;
    }

    // Configurações de contexto OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Configuração da janela
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    //Cria a janela
    m_Window = SDL_CreateWindow
    ("AlbGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (m_Window == nullptr) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        return false;
    }

    // Cria contexto OpenGL
    m_GLContext = SDL_GL_CreateContext(m_Window);
    SDL_GL_MakeCurrent(m_Window, m_GLContext);
    SDL_GL_SetSwapInterval(1); // Ativa V-Sync

    // Initialize Glew (ou outro carregador de funções OpenGL)
    glewExperimental = GL_TRUE;

    //Inicializa o grew
    GLenum glewInitResult = glewInit();

    if (glewInitResult != GLEW_OK) {
        SDL_Log("Falha ao inicializar GLEW: %s", glewGetErrorString(glewInitResult));
        return false;
    }

    // Limpa qualquer erro do OpenGL que possa ter ocorrido durante a inicialização do GLEW
    // (isso é normal devido ao glewExperimental)
    glGetError();
    // ***********************************************

    // Verifica se a versão do OpenGL está OK
    SDL_Log("GLEW %s inicializado com sucesso", glewGetString(GLEW_VERSION));
    SDL_Log("OpenGL %s", glGetString(GL_VERSION));
    SDL_Log("GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    SDL_Log("Vendor: %s", glGetString(GL_VENDOR));
    SDL_Log("Renderer: %s", glGetString(GL_RENDERER));

    // Verifica se temos suporte para OpenGL 3.3+
    int major_version, minor_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    glGetIntegerv(GL_MINOR_VERSION, &minor_version);

    if (major_version < 3 || (major_version == 3 && minor_version < 3))
    {
        SDL_Log("OpenGL 3.3+ não suportado. Seu driver suporta apenas %d.%d", major_version, minor_version);
        return false;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_ImGuiIO = &ImGui::GetIO();
    m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls

    // Setup Plataform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(m_Window, m_GLContext);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Configura estilo do ImGui (opcional)
    ImGui::StyleColorsDark();

    // Mensagem de sucesso
    SDL_Log("Aplicação inicializada com sucesso!!");
    SDL_Log("OpenGL %s, GLSL %s", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    return true;
}

void Application::Shutdown() const{
    //Limpa ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // Limpa SDL
    if (m_GLContext)
        SDL_GL_DeleteContext(m_GLContext);
    if (m_Window)
        SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Application::ProcessEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        //Processa eventos para o ImGui
        ImGui_ImplSDL2_ProcessEvent(&event);

        // Processa eventos para a aplicação
        switch (event.type) {
            case SDL_QUIT:
                m_Running = false;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_Window)) {
                    m_Running = false;
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    m_Running = false;
                }
                break;
            default:
                break;
        }
    }
}

void Application::BeginFrame() {
    // Limpa o buffer de cor e profundidade
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Cor de fundo
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Inicia um novo frame de ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void Application::EndFrame() const{
    // Renderiza ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //Troca os buffers (Double buffering)
    SDL_GL_SwapWindow(m_Window);
}


//ImGui

void Application::HierarchyMenu(const list<Mesh*> &objects,  bool enable) {
    ImGui::SetNextWindowSize(ImVec2(300, 600));
    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoResize);

    if (ImGui::TreeNode("Cena")) {
        static Mesh* selected = nullptr;

        for (auto* obj: objects) {

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

            if (selected == obj) {
                flags |= ImGuiTreeNodeFlags_Selected;
            }

            ImGui::TreeNodeEx(obj->GetName().c_str(), flags);

            if (ImGui::IsItemClicked()) {
                selected = (selected == obj) ? nullptr : obj;
            }
        }

        ImGui::TreePop();

        if (selected) {
            InspectorMenu(*selected); // chama uma única vez
        }
    }

    // Mostrar o inspector APENAS para o selecionado


    ImGui::End();
}

void Application::InspectorMenu(Mesh &obj, bool enable) {
    ImGui::SetNextWindowSize(ImVec2(300, 600));
    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoResize);
    ImGui::Text("To %s", obj.GetName().c_str());
    ImGui::LabelText("", "Transform: ");
    ImGui::LabelText("Position:", "");
    ImGui::LabelText("", "X: ");
    ImGui::SameLine();
    ImGui::InputFloat("##X:", &obj.transform.position.x);
    ImGui::SliderFloat("##x", &obj.transform.position.x, -2000.0f, 2000.0f);
    ImGui::LabelText("", "Y: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Y:", &obj.transform.position.y);
    ImGui::SliderFloat("##y", &obj.transform.position.y, -2000.0f, 2000.0f);
    ImGui::LabelText("", "Z: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Z:", &obj.transform.position.z);
    ImGui::SliderFloat("##z", &obj.transform.position.z, -2000.0f, 2000.0f);

    ImGui::LabelText("Rotation:", "");
    ImGui::LabelText("", "rX: ");
    ImGui::SameLine();
    ImGui::InputFloat("##rX:", &obj.transform.rotation.x);
    ImGui::LabelText("", "rY: ");
    ImGui::SameLine();
    ImGui::InputFloat("##rY:", &obj.transform.rotation.y);
    ImGui::LabelText("", "rZ: ");
    ImGui::SameLine();
    ImGui::InputFloat("##rZ:", &obj.transform.rotation.z);
    ImGui::SliderFloat("##rz", &obj.transform.rotation.z, -360.0f, 360.0f);

    ImGui::LabelText("Scales:", "");
    ImGui::LabelText("", "Width: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Width:", &obj.transform.scale.x);
    ImGui::SliderFloat("##Width", &obj.transform.scale.x, -10.0f, 10.0f);
    ImGui::LabelText("", "Height: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Height:", &obj.transform.scale.y);
    ImGui::SliderFloat("##Height", &obj.transform.scale.y, -10.0f, 10.0f);
    ImGui::LabelText("", "Forward: ");
    ImGui::SameLine();
    ImGui::InputFloat("##Forward:", &obj.transform.rotation.z);

    ImGui::End();
}

void Application::DebugMenu(bool enable) {
    if (enable == false) {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(300, 140));
    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoResize);
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("FPS: %.1f", io.Framerate);
    ImGui::End();
}





