#pragma once

#include "Layer.h"
#include <SDL3/SDL.h>
#include "imgui.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl3.h>

namespace Magma
{
	// This is where the main loop game logic should go
	class GameLayer : public Layer
	{
		public:

			void OnAttach() override;
			void OnUpdate(float dt) override;
			void OnImGuiRender() override;
	};
}