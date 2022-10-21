#include "lnpch.h"
#include "CameraComponent.h"
#include "Lanna/GameObject/Component.h"

#include <imgui.h>

CameraComponent::CameraComponent(): Component(Component::Type::CAMERA)
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Use()
{
}

void CameraComponent::ImGuiDraw()
{
	if (ImGui::CollapsingHeader("Camera"))
	{

	}
}
