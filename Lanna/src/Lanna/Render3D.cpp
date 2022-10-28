#include <lnpch.h>
#include "Render3D.h"

#include <Lanna/Application.h>
#include <Lanna/Window.h>

#include <glew.h>
#include <glm.hpp>

#include <imgui.h>
#include "Lanna/Input.h"
#include "Lanna/KeyCodes.h"
#include "Renderer/Framebuffer.h"

#include "Lanna/EntityManager.h"
#include "GameObject/GameObject.h"
#include "GameObject/Components/MeshComponent.h"
#include "GameObject/Components/CameraComponent.h"

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

		GameObject* camera=Lanna::Application::Get().GetEntityManager()->AddEmptyGameObject("camera");
		
		m_ActiveCamera = (CameraComponent*)camera->AddComponent(Component::Type::CAMERA);
		m_ActiveCamera->setPosition({ 0.0f,4.0f,0.0f });
		m_ActiveCamera->SetPerspective(45.0f, resolution.x / (float)resolution.y);
		m_ActiveCamera->LookAt({ 0.0f, 0.0f, 0.0f });

		m_Fbo = new Framebuffer();
		m_Fbo->Init(800, 600);
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

	}

	void Render3D::Close()
	{

	}
	void Render3D::RenderMesh(MeshComponent& mesh, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec4& color)
	{
		glViewport(0, 0, resolution.x, resolution.y);


		// bind buffer
		m_Fbo->Bind();
		/*glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo->fbo);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
		model = glm::rotate(model, rotation.x, glm::vec3(1.f, 0.0f, 0.0f));
		model = glm::rotate(model, rotation.y, glm::vec3(0.f, 1.0f, 0.0f));
		model = glm::rotate(model, rotation.z, glm::vec3(0.f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

		m_ColorShader->Use();

		m_ColorShader->setMat4("u_Model", model);
		m_ColorShader->setMat4("u_View", m_ActiveCamera->getView());
		m_ColorShader->setMat4("u_Proj", m_ActiveCamera->getProjection());
		m_ColorShader->setVec4("u_Color", glm::vec4(color.r, color.g, color.b, color.a));

		mesh.Render();


		// unbind buffer
		/*glBindFramebuffer(GL_FRAMEBUFFER, 0);*/
		m_Fbo->Unbind();

	}

}


