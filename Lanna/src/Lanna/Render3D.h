#pragma once
#include <lnpch.h>

#include <Lanna/Core.h>
#include <Lanna/Renderer/Shader.h>
#include "GameObject/Components/MeshComponent.h"
#include "GameObject/Components/CameraComponent.h"
#include "Lanna/Renderer/Framebuffer.h"
#include "Lanna/Renderer/Texture.h"
#include "Lanna/Renderer/Shader.h"

#include <glm.hpp>

namespace Lanna
{
	class LANNA_API Render3D
	{
	private:

		CameraComponent* m_ActiveCamera;
		glm::mat4 m_PersProj;
		glm::mat4 m_View;
		glm::vec2  resolution;

		int m_ColorShaderId;

		Shader* m_ColorShader;

	public:

		Framebuffer m_Framebuffer;

	public:
		Render3D();
		~Render3D();


		void Init();
		void Update();
		void Draw();
		void Close();

		glm::mat4 GetPersProjection() { return m_ActiveCamera->getProjection(); }
		glm::mat4 GetView() { return m_ActiveCamera->getView(); }
		CameraComponent& GetActiveCamera() { return *m_ActiveCamera; }
		uint32_t getColorBufferTexture() { return m_Framebuffer.getColorBufferTexture(); }
		void RenderMesh(MeshComponent& mesh, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec4& color);
	private:
	};
}