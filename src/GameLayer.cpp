#include "GameLayer.h"

using namespace Magma;

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