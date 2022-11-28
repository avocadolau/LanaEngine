#pragma once
#include <lnpch.h>

#include <Lanna/Core.h>
#include <Lanna/Resources/Shader.h>
#include "GameObject/Components/MeshComponent.h"
#include "GameObject/Components/CameraComponent.h"
#include "GameObject/Components/MaterialComponent.h"
#include "Lanna/Resources/Framebuffer.h"
#include "Lanna/Resources/Texture.h"
#include "Lanna/Resources/Shader.h"
#include "Lanna/Resources.h"

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

		
		/*Shader* m_ColorShader;
		Shader* m_TexShader;
		Shader* m_GridShader;*/
		ResourceId m_ColorShader;
		ResourceId m_TexShader;
		ResourceId m_GridShader;

	public:

		Framebuffer m_Framebuffer;

	public:
		Render3D();
		~Render3D();


		void Init();
		void Update();
		void Draw();
		void Close();

		uint32_t gridShaderModelLoc;
		uint32_t gridShaderViewLoc;
		uint32_t gridShaderProjectionLoc;

		glm::mat4 GetPersProjection() { return m_ActiveCamera->getProjection(); }
		glm::mat4 GetView() { return m_ActiveCamera->getView(); }
		CameraComponent& GetActiveCamera() { return *m_ActiveCamera; }
		uint32_t getColorBufferTexture() { return m_Framebuffer.getColorBufferTexture(); }
		void RenderMeshColor(MeshComponent* mesh, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec4& color);
		void RenderMesh(MeshComponent* mesh, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, MaterialComponent* material, glm::vec4& color);
		void RenderGrid(Framebuffer* target = NULL, bool clear = false);
	};
}