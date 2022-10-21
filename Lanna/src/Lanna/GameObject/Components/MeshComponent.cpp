#include "lnpch.h"
#include "MeshComponent.h"
#include "Lanna/GameObject/Component.h"

#include <imgui.h>
MeshComponent::MeshComponent() : Component(Component::Type::MESH)
{

}
MeshComponent::~MeshComponent()
{

}

void MeshComponent::Use()
{
}

void MeshComponent::ImGuiDraw()
{
	if (ImGui::CollapsingHeader("Mesh"))
	{

	}


}