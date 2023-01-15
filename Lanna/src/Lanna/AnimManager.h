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

#include "Resources/Mesh.h"

namespace Lanna
{
	class LANNA_API AnimManager
	{
	public:
		Mesh* boneMesh = nullptr;
		bool renderBones = true;

	public:
		AnimManager();
		~AnimManager();


		void Init();
		void Update();
		void Render();

	};
}