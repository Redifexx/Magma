#include "GameLayer.h"

#include "Model.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include <filesystem>

using namespace Magma;

void GameLayer::OnAttach()
{
	// Game initialization logic goes here
	Model cube("resources/models/fundamental_cube.fbx");
}

void GameLayer::OnUpdate(float dt)
{
	// Game update logic goes here


}

void GameLayer::OnImGuiRender()
{
	// Game ImGui rendering goes here

	ImGui::Begin("Magma Debug Menu");
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();
}