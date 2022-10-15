#pragma once
#include <lnpch.h>

#include <Lanna/Core.h>
#include <Lanna/Renderer/Shader.h>
#include <Lanna/Renderer/Camera.h>
#include <Lanna/Renderer/Mesh.h>


#include <glm.hpp>

#include "glad/glad.h"
namespace Lanna
{
	class LANNA_API Render3D
	{
	private:
		int m_ShaderProgram;
		unsigned int fragmentShader;
		unsigned int vertexShader;

		Camera* m_ActiveCamera;
		glm::mat4 m_PersProj;
		glm::mat4 m_View;
		glm::vec2  resolution;

		int m_ColorShaderId;

		Shader* m_ColorShader;

		Mesh* m_exampleMesh;

	public:
		Render3D();
		~Render3D();


		void Init();
		void Draw();
		void Close();

		glm::mat4 GetPersProjection() { return m_ActiveCamera->getProjection(); }
		glm::mat4 GetView() { return m_ActiveCamera->getView(); }

		void RenderMesh(Mesh& mesh, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec4& color);
	};
}