#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "imgui.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl3.h>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include <glm/glm.hpp>
#include <iostream>
#include <filesystem>

#include "Window.h"

int main(int argc, char* argv[])
{

	Magma::Window window;
	if (!window.Init(1280, 720, "Magma Framework")) { return -1; }


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(window.GetSDLWindow(), window.GetGLContext());
    ImGui_ImplOpenGL3_Init("#version 130");

    // Loop
    bool running = true;
    while (running) {
		window.PollEvents(running);

        glViewport(0, 0, 1280, 720);
        glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Magma Settings");
        static float speed = 5.0f;
        ImGui::SliderFloat("Player Speed", &speed, 0.0f, 100.0f);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.SwapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    window.Shutdown();

    return 0;
}