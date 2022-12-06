#include <lnpch.h>
#include "Render3D.h"

#include <Lanna/Application.h>
#include <Lanna/Window.h>

#include <glew.h>
#include <glm.hpp>

#include <imgui.h>
#include "Lanna/Input.h"
#include "Lanna/KeyCodes.h"
#include "Resources/Framebuffer.h"

#include "Lanna/EntityManager.h"
#include "GameObject/GameObject.h"
#include "GameObject/Components/MeshComponent.h"
#include "GameObject/Components/CameraComponent.h"
#include "GameObject/Components/MaterialComponent.h"

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

		m_ColorShader = LN_RESOURCES.Import<Shader>("resources/shaders/model_color");
		m_TexShader = LN_RESOURCES.Import<Shader>("resources/shaders/model_texture");
		m_GridShader = LN_RESOURCES.Import<Shader>("resourses/shaders/grid");

		GameObject* camera=LN_ENTITY_MAN->AddEmptyGameObject("camera");
		camera->canDelete = false;
		m_ActiveCamera = (CameraComponent*)camera->AddComponent(Component::Type::CAMERA);
		m_ActiveCamera->SetPerspective(45.0f, resolution.x / (float)resolution.y);
		m_ActiveCamera->setPosition({ 0.0f,1.0f,5.0f });
		m_ActiveCamera->LookAt({ 0.0f, 0.0f, 0.0f });

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

	}

	void Render3D::Update()
	{
		ImGuiIO& io = ImGui::GetIO();

		m_ActiveCamera->m_Framebuffer.Clear();

		//RenderGrid();
	}


	void Render3D::Draw()
	{
		/*if (m_ActiveCamera)
		{
			ImGuiIO& io = ImGui::GetIO();

			if (Lanna::Input::IsKeyPressed(LN_KEY_RIGHT_ALT))
			{
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
		*/
	}

	void Render3D::Close()
	{

	}
	void Render3D::RenderMeshColor(Mesh* mesh, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec4& color, bool clear)
	{
		glViewport(0, 0, resolution.x, resolution.y);

		// bind buffer
		m_ActiveCamera->m_Framebuffer.Bind(clear);


		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
		model = glm::rotate(model, rotation.x, glm::vec3(1.f, 0.0f, 0.0f));
		model = glm::rotate(model, rotation.y, glm::vec3(0.f, 1.0f, 0.0f));
		model = glm::rotate(model, rotation.z, glm::vec3(0.f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

		Shader* colorShaderRef = LN_RESOURCES.GetResourceById<Shader>(m_ColorShader);
		colorShaderRef->Use();

		colorShaderRef->setMat4("u_Model", model);
		colorShaderRef->setMat4("u_View", m_ActiveCamera->getView());
		colorShaderRef->setMat4("u_Proj", m_ActiveCamera->getProjection());
		colorShaderRef->setVec4("u_Color", glm::vec4(color.r, color.g, color.b, color.a));

		mesh->Render();

		// unbind buffer
		m_ActiveCamera->m_Framebuffer.Unbind();
	}
	void Render3D::RenderMesh(Mesh* mesh, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, Material* material, glm::vec4& color, bool clear)
	{
		if (material)
		{
			if (material->IsColor())
			{
				RenderMeshColor(mesh, position, rotation, scale, material->GetColor(), clear);
				return;
			}
			else if (material->IsTexture() == false)
			{
				RenderMeshColor(mesh, position, rotation, scale, color, clear);
				return;
			}
		}
		else
		{
			RenderMeshColor(mesh, position, rotation, scale, color, clear);
			return;
		}

		glViewport(0, 0, resolution.x, resolution.y);

		// bind buffer
		m_ActiveCamera->m_Framebuffer.Bind(clear);
	

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
		model = glm::rotate(model, rotation.x, glm::vec3(1.f, 0.0f, 0.0f));
		model = glm::rotate(model, rotation.y, glm::vec3(0.f, 1.0f, 0.0f));
		model = glm::rotate(model, rotation.z, glm::vec3(0.f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

		Shader* texShaderRef = LN_RESOURCES.GetResourceById<Shader>(m_TexShader);
		texShaderRef->Use();
		glBindVertexArray(mesh->vao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material->GetTexture()->GetTextureId());

		texShaderRef->setMat4("u_Model", model);
		texShaderRef->setMat4("u_View", m_ActiveCamera->getView());
		texShaderRef->setMat4("u_Proj", m_ActiveCamera->getProjection());

		mesh->Render();
		glBindTexture(GL_TEXTURE_2D, 0);

		// unbind buffer
		m_ActiveCamera->m_Framebuffer.Unbind();

	}

	void Render3D::RenderGrid(Framebuffer* target, bool clear)
	{
		if (!target) target = &m_ActiveCamera->m_Framebuffer;
		glViewport(0, 0, target->width, target->height);

		target->Bind(clear);
		glColor3f(1.0f, 1.0f, 1.0f);
		glLineWidth(1.0f);

		glBegin(GL_LINES);

		float d = 200.0f;

		for (float i = -d; i <= d; i += 1.0f)
		{
			glVertex3f(i, 0.0f, -d);
			glVertex3f(i, 0.0f, d);
			glVertex3f(-d, 0.0f, i);
			glVertex3f(d, 0.0f, i);
		}

		glEnd();

		target->Unbind();
	}

}


