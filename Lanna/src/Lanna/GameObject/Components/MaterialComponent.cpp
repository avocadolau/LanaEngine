#include "lnpch.h"
#include "MaterialComponent.h"
#include "Lanna/GameObject/Component.h"

#include <imgui.h>

MaterialComponent::MaterialComponent() : Component(Component::Type::MATERIAL)
{

}
MaterialComponent::~MaterialComponent()
{

}

void MaterialComponent::Use()
{
}

void MaterialComponent::ImGuiDraw()
{

	if (ImGui::CollapsingHeader("Material"))
	{

	}

}