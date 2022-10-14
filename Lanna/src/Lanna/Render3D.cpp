#include <lnpch.h>
#include "Render3D.h"

#include <Lanna/Application.h>
#include <Lanna/Window.h>

#include <glm.hpp>

#include "glad/glad.h"

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
		glm::vec2  resolution = { window.GetHeight(), window.GetHeight() };


		m_ColorShader = new Shader("resources/shaders/model_color");


		// esto va a la mesh
		

		
		unsigned int buffer;

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);   // 9* sizeof(float)

		unsigned int ibo;	// index buffer data

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);   // 9* sizeof(float)



		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(float) * 3, (const void*)0);		// 0, num vertex,	espacio entre vertices, offset start

		

	}


	void Render3D::Draw()
	{
		
		glClear(GL_COLOR_BUFFER_BIT);		// limpia la pantalla
		//glDrawArrays(GL_TRIANGLES, 0, 3);	// first intex, num of vertex

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);			// 6 the number of indices 
		
	}

	void Render3D::Close()
	{

	}
}


