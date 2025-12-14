#include "GameLayer.h"

using namespace Magma;

void GameLayer::OnUpdate(float dt)
{
	// Game update logic goes here
}

void GameLayer::OnImGuiRender()
{
	// Game ImGui rendering goes here

	ImGui::Begin("Magma Settings");
	static float speed = 5.0f;
	ImGui::SliderFloat("Player Speed", &speed, 0.0f, 100.0f);
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();
}