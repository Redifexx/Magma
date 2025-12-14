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
#include "LayerStack.h"
#include "ImGuiLayer.h"
#include "GameLayer.h"

int main(int argc, char* argv[])
{
    // Window Creation
	Magma::Window window;
	if (!window.Init(1280, 720, "Magma Framework")) { return -1; }
	window.SetVSync(0);

    // Layers
	Magma::LayerStack layerStack;

	Magma::ImGuiLayer* imGuiLayer = new Magma::ImGuiLayer(window.GetSDLWindow(), window.GetGLContext());
	layerStack.PushLayer(imGuiLayer);

	Magma::GameLayer* gameLayer = new Magma::GameLayer();
	layerStack.PushLayer(gameLayer);

    // Main Loop
    bool isRunning = true;
    while (isRunning) {
		window.PollEvents(isRunning);

        int w_, h_;
		window.GetWindowSize(w_, h_);
        glViewport(0, 0, w_, h_);
        glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
        glDisable(GL_CULL_FACE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Game Logic
        for (Magma::Layer* layer : layerStack)
        {
			layer->OnUpdate(0.016f); // eventually pass real delta time
        }

		// ImGui Rendering
		imGuiLayer->Begin();
        for (Magma::Layer* layer : layerStack)
        {
			layer->OnImGuiRender();
        }
		imGuiLayer->End();

        window.SwapBuffers();
    }

    window.Shutdown();

    return 0;
}