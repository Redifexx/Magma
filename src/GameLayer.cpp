#include "GameLayer.h"

#include "Model.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include <filesystem>

using namespace Magma;

void GameLayer::OnAttach()
{
	// Game initialization logic goes here
	m_Models.push_back(new Model("resources/models/monke.fbx"));

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

	m_Model = glm::mat4(1.0f);
	m_Model = glm::rotate(m_Model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	m_Camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
	m_Camera->SetAspectRatio(1280.0f / 720.0f);

	m_ShaderProgram->Use();

	m_ShaderProgram->SetUniform("u_Model", m_Model);
	m_ShaderProgram->SetUniform("u_ViewProjection", m_Camera->GetViewProjectionMatrix());
}

void GameLayer::OnUpdate(float dt)
{
	// Game update logic goes here

	m_ShaderProgram->Use();

	m_Model = glm::rotate(m_Model, glm::radians(2.0f * dt), glm::vec3(0.0f, 0.0f, 1.0f));

	m_ShaderProgram->SetUniform("u_Model", m_Model);
	m_ShaderProgram->SetUniform("u_ViewProjection", m_Camera->GetViewProjectionMatrix());

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
	delete m_Camera;
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