#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

void init_imgui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void render_imgui() {
    ImGui::NewFrame();

    ImGui::Begin("Visualisation des Structures de Données");

    // Ajoute des widgets pour afficher les données, comme des tables, des arbres, etc.
    ImGui::Text("Voici un exemple de visualisation d'une pile");

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Erreur lors de l'initialisation de GLFW!" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Visualizer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Erreur lors de la création de la fenêtre GLFW!" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Erreur lors du chargement d'OpenGL!" << std::endl;
        return -1;
    }

    init_imgui(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        render_imgui();

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
