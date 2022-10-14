#pragma once

#include <Lanna/Core.h>
#include <Lanna/Renderer/Shader.h>
#include <Lanna/Renderer/Camera.h>

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

		//----------------


		unsigned int VAO;
		float vertex[9] = { 0.3f, 0.21f, 0.f,
							0.34f, 0.215f, 0.f,
							0.32f,0.25f, 0.f };

		int indices[3] = { 0,1,2 };

		// ----------------------------------

		glm::mat4 m_PersProj;
		glm::mat4 m_View;

		int m_ColorShaderId;
		Shader* m_ColorShader;

		Camera* m_ActiveCamera;
	public:
		Render3D();
		~Render3D();


		void Init();
		void Draw();
		void Close();

		glm::mat4 GetPersProjection() { return m_ActiveCamera->getProjection(); }
		glm::mat4 GetView() { return m_ActiveCamera->getView(); }

	
	};
}