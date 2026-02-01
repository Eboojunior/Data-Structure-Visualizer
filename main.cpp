#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"
#include <stack>

void init_imgui(SDL_Window* window, SDL_GLContext gl_context) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void render_imgui() {
    ImGui::NewFrame();

    ImGui::Begin("Data Structure Visualizer");

    // Visualisation de la pile
    static std::stack<int> stack;
    if (ImGui::Button("Push to Stack")) {
        stack.push(rand() % 100); // Ajouter un nombre aléatoire
    }

    ImGui::Text("Stack: ");
    std::stack<int> temp_stack = stack; // Copie de la pile pour l'affichage
    while (!temp_stack.empty()) {
        ImGui::Text("%d", temp_stack.top());
        temp_stack.pop();
    }

    // Visualisation du tableau
    static int arr[5] = {1, 2, 3, 4, 5};
    ImGui::Text("Array: ");
    ImGui::Columns(2);
    ImGui::Text("Index");
    ImGui::NextColumn();
    ImGui::Text("Value");
    ImGui::NextColumn();
    for (int i = 0; i < 5; ++i) {
        ImGui::Text("%d", i);
        ImGui::NextColumn();
        ImGui::Text("%d", arr[i]);
        ImGui::NextColumn();
    }
    ImGui::Columns(1);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("DataStructureVisualizer",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          1280, 720, SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Initialisation de ImGui
    init_imgui(window, gl_context);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            ImGui_ImplSDL3_ProcessEvent(&event);
        }

        // Rendu OpenGL
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        render_imgui();

        SDL_GL_SwapWindow(window);
    }

    // Nettoyage
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
