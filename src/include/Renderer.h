#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>

namespace Magma
{
	class Renderer
	{
		public:
			static void Init();
			static void Shutdown();

			static void BeginScene(const glm::mat4& viewProjection);
			static void EndScene();

			static void Submit(
				const std::shared_ptr<Model> model,
				const std::shared_ptr<ShaderProgram>& shader,
				const glm::mat4& transform = glm::mat4(1.0f)
			);
	};
}