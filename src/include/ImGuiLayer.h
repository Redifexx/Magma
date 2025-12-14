#pragma once

#include "Layer.h"
#include "imgui.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl3.h>

namespace Magma
{
	class ImGuiLayer : public Layer
	{
		public:
			ImGuiLayer();

			void OnAttach() override;
			void OnDetach() override;
			void Init(SDL_Window* window, SDL_GLContext* glContext); // passing window + context
			void Begin(); // begin & end frame
			void End();
	};
}