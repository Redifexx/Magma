#include "GameLayer.h"

#include "Model.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Texture.h"
#include <filesystem>

using namespace Magma;

void GameLayer::OnAttach()
{
	// Game initialization logic goes here
	m_Models.push_back(new Model("resources/models/elephant.fbx"));

	std::string vertpath = "resources/shaders/basic.vert";
	std::string fragpath = "resources/shaders/basic.frag";

	#ifdef MAGMA_ROOT_DIR
		vertpath = std::string(MAGMA_ROOT_DIR) + vertpath;
		fragpath = std::string(MAGMA_ROOT_DIR) + fragpath;
	#endif

	Shader vertexShader(vertpath, GL_VERTEX_SHADER);
	Shader fragmentShader(fragpath, GL_FRAGMENT_SHADER);

	m_ShaderProgram = new ShaderProgram();

	m_ShaderProgram->AttachShader(vertexShader);
	m_ShaderProgram->AttachShader(fragmentShader);
	if (!m_ShaderProgram->Link())
	{
		std::cerr << "Failed to link shader program!" << std::endl;
		return;
	}

	m_Texture = new Texture("resources/textures/elephant.jpg");
	m_Texture->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	m_Texture->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	m_ModelMatrix = glm::mat4(1.0f);
	m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, -3.0f, 0.0f));
	m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(50.0f, 50.0f, 50.0f));
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	m_Camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
	m_Camera->SetPerspective(true);

	m_ShaderProgram->Use();

	m_ShaderProgram->SetUniform("u_Model", m_ModelMatrix);
	m_ShaderProgram->SetUniform("u_ViewProjection", m_Camera->GetViewProjectionMatrix());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture->GetID());
	m_ShaderProgram->SetUniform("u_Texture", 0);

	// Input
	Magma::Input::Init();
}

void GameLayer::OnUpdate(float dt)
{
	// Game update logic goes here


	// Basic Input

	if (Magma::Input::IsKeyHeld(SDL_SCANCODE_W))
	{
		m_Camera->SetPosition(m_Camera->GetPosition() + m_Camera->GetFront() * 5.0f * dt);
	}

	if (Magma::Input::IsKeyHeld(SDL_SCANCODE_S))
	{
		m_Camera->SetPosition(m_Camera->GetPosition() + m_Camera->GetFront() * -5.0f * dt);
	}

	if (Magma::Input::IsKeyHeld(SDL_SCANCODE_A))
	{
		m_Camera->SetPosition(m_Camera->GetPosition() + m_Camera->GetRight() * -5.0f * dt);
	}

	if (Magma::Input::IsKeyHeld(SDL_SCANCODE_D))
	{
		m_Camera->SetPosition(m_Camera->GetPosition() + m_Camera->GetRight() * 5.0f * dt);
	}

	if (Magma::Input::IsKeyHeld(SDL_SCANCODE_E))
	{
		m_Camera->SetPosition(m_Camera->GetPosition() + m_Camera->GetUp() * 5.0f * dt);
	}

	if (Magma::Input::IsKeyHeld(SDL_SCANCODE_Q))
	{
		m_Camera->SetPosition(m_Camera->GetPosition() + m_Camera->GetUp() * -5.0f * dt);
	}

	if (SDL_GetWindowRelativeMouseMode(m_Window))
	{
		float mouseX = Magma::Input::GetMouseDelta().x;
		float mouseY = Magma::Input::GetMouseDelta().y;

		float camYaw = m_Camera->GetYaw() + mouseX * 0.1f;
		float camPitch = m_Camera->GetPitch() - mouseY * 0.1f;
		camPitch = glm::clamp(camPitch, -89.0f, 89.0f);
		m_Camera->SetYaw(camYaw);
		m_Camera->SetPitch(camPitch);
		m_Camera->UpdateCameraVectors();
	}

	// Render Logic

	m_ShaderProgram->Use();

	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(20.0f * dt), glm::vec3(0.0f, 0.0f, 1.0f));

	m_ShaderProgram->SetUniform("u_Model", m_ModelMatrix);
	m_ShaderProgram->SetUniform("u_ViewProjection", m_Camera->GetViewProjectionMatrix());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture->GetID());
	m_ShaderProgram->SetUniform("u_Texture", 0);

	for (Model* model : m_Models)
	{
		model->Draw();
	}

	Magma::Input::Update();
}

void GameLayer::OnDetach()
{
	// Game cleanup logic goes here

	for (Model* model : m_Models)
	{
		delete model;
	}
	m_Models.clear();
	delete m_ShaderProgram;
	delete m_Camera;
	delete m_Texture;
}

void GameLayer::OnImGuiRender()
{
	// Game ImGui rendering goes here

	ImGui::Begin("Magma Debug Menu");
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();
}

void GameLayer::OnResize(int width, int height)
{
	if (height == 0) height = 1;
	m_Camera->SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
}