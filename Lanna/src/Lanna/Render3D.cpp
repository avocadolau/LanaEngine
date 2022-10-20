#include <lnpch.h>
#include "Render3D.h"

#include <Lanna/Application.h>
#include <Lanna/Window.h>
#include <Lanna/Renderer/Mesh.h>

#include <glm.hpp>

#include "glad/glad.h"

#include <imgui.h>
#include "Lanna/Input.h"
#include "Lanna/KeyCodes.h"

namespace Lanna {

	Render3D::Render3D()
	{
	}
	Render3D::~Render3D()
	{
	}

	void Render3D::Init()
	{
		Lanna::Window& window = Lanna::Application::Get().GetWindow();
		resolution = { window.GetHeight(), window.GetHeight() };


		m_ColorShader = new Shader("resources/shaders/model_color");
		m_ActiveCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f),-90,0);
		m_ActiveCamera->SetPerspective(45.0f, resolution.x / (float)resolution.y);

		m_exampleMesh = new Mesh();
		m_exampleMesh->LoadFromFile("");
		
	}


	void Render3D::Draw()
	{
		if (m_ActiveCamera)
		{
			ImGuiIO& io = ImGui::GetIO();

			if (Lanna::Input::IsKeyPressed(LN_KEY_A))
				m_ActiveCamera->ProcessKeyboard(Camera_Movement::FREE_LOOK_LEFT, io.DeltaTime);
			if (Lanna::Input::IsKeyPressed(LN_KEY_D))
				m_ActiveCamera->ProcessKeyboard(Camera_Movement::FREE_LOOK_RIGHT, io.DeltaTime);
			if (Lanna::Input::IsKeyPressed(LN_KEY_W))
				m_ActiveCamera->ProcessKeyboard(Camera_Movement::FREE_LOOK_UP, io.DeltaTime);
			if (Lanna::Input::IsKeyPressed(LN_KEY_S))
				m_ActiveCamera->ProcessKeyboard(Camera_Movement::FREE_LOOK_DOWN, io.DeltaTime);

				
		}


		m_exampleMesh->Render();
	}

	void Render3D::Close()
	{

	}
	void Render3D::RenderMesh(Mesh& mesh, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec4& color)
	{
		glViewport(0, 0, resolution.x, resolution.y);


		// bind buffer
		glBindFramebuffer(GL_FRAMEBUFFER, mesh.GetBuffer());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
		model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

		m_ColorShader->Use();

		m_ColorShader->setMat4("u_Model", model);
		m_ColorShader->setMat4("u_View", m_ActiveCamera->getView());
		m_ColorShader->setMat4("u_Proj", m_ActiveCamera->getProjection());
		m_ColorShader->setVec4("u_Color", glm::vec4(color.r, color.g, color.b, color.a));

		mesh.Render();


		// unbind buffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


	}

}


