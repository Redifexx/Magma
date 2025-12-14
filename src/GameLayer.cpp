#include "GameLayer.h"

#include "Model.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include <filesystem>

using namespace Magma;

void GameLayer::OnAttach()
{
	// Game initialization logic goes here
	m_Models.push_back(new Model("resources/models/fundamental_cube.fbx"));
	Shader vertexShader("resources/shaders/basic.vert", GL_VERTEX_SHADER);
	Shader fragmentShader("resources/shaders/basic.frag", GL_FRAGMENT_SHADER);

	m_ShaderProgram = new ShaderProgram();

	m_ShaderProgram->AttachShader(vertexShader);
	m_ShaderProgram->AttachShader(fragmentShader);
	if (!m_ShaderProgram->Link())
	{
		std::cerr << "Failed to link shader program!" << std::endl;
		return;
	}

	glm::mat4 model = glm::mat4(1.0f);


	// 1. SETUP VARIABLES
	float fov = 90.0f;                      // Field of View (in degrees)
	float aspectRatio = 1280.0f / 720.0f;   // Screen Width / Height
	float nearPlane = 0.1f;                 // Closest things you can see
	float farPlane = 100.0f;                // Furthest things you can see

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);  // Camera is 3 units back
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Looking at center
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);     // "Up" is positive Y

	// 2. CREATE MATRICES
	// Projection: Handles the 3D perspective (things get smaller far away)
	// IMPORTANT: glm::perspective expects RADIANS, so wrap fov in glm::radians()
	glm::mat4 projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

	// View: Handles the Camera position/rotation
	glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

	// 3. COMBINE (Result = Projection * View)
	// Order matters! It applies Right-to-Left (View happens first, then Projection)
	glm::mat4 viewProjection = projection * view;


	m_CameraMatrix = viewProjection;

	m_ShaderProgram->Use();

	m_ShaderProgram->SetUniform("u_Model", model);
	m_ShaderProgram->SetUniform("u_ViewProjection", m_CameraMatrix);
}

void GameLayer::OnUpdate(float dt)
{
	// Game update logic goes here

	m_ShaderProgram->Use();
	for (Model* model : m_Models)
	{
		model->Draw();
	}
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
}

void GameLayer::OnImGuiRender()
{
	// Game ImGui rendering goes here

	ImGui::Begin("Magma Debug Menu");
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();
}