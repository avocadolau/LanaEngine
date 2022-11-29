#include "lnpch.h"
#include "MaterialComponent.h"
#include "Lanna/GameObject/Component.h"
#include "Lanna/Application.h"
#include "Lanna/Resources.h"

#include <imgui.h>
#include <glew.h>
#include <glm.hpp>

namespace Lanna
{
	extern const std::filesystem::path s_AssetPath;

	MaterialComponent::MaterialComponent() : Component(Component::Type::MATERIAL)
	{
		m_MaterialID = LN_RESOURCES.Import<Material>("null");
		LN_RESOURCES.GetResourceById<Material>(m_MaterialID)->setColor(glm::vec4(0.0f,0.0f,0.0f,0.0f));
	}
	MaterialComponent::MaterialComponent(glm::vec4 color) : Component(Component::Type::MATERIAL)
	{
		m_MaterialID = LN_RESOURCES.Import<Material>("null");
		LN_RESOURCES.GetResourceById<Material>(m_MaterialID)->setColor(color);

	}
	MaterialComponent::MaterialComponent(const char* file) : Component(Component::Type::MATERIAL)
	{
		m_MaterialID = LN_RESOURCES.Import<Material>(file);
		//LN_RESOURCES.GetResourceById<Material>(m_MaterialID)->setTexture(file);
	}

	MaterialComponent::~MaterialComponent()
	{

	}

	unsigned int MaterialComponent::getTextureID()
	{
		return LN_RESOURCES.GetResourceById<Material>(m_MaterialID)->GetTexture()->GetTextureId();
	}

	Material* MaterialComponent::getMaterial()
	{
		return LN_RESOURCES.GetResourceById<Material>(m_MaterialID);
	}

	void MaterialComponent::setTexture(const char* file)
	{
		LN_RESOURCES.GetResourceById<Material>(m_MaterialID)->setTexture(file);
	}

	void MaterialComponent::setColor(glm::vec4 color)
	{
		LN_RESOURCES.GetResourceById<Material>(m_MaterialID)->setColor(color);

	}

	void MaterialComponent::Use()
	{
	}

	void MaterialComponent::ImGuiDraw()
	{

		if (ImGui::TreeNode("Material"))
		{
			Material* m_Mat = LN_RESOURCES.GetResourceById<Material>(m_MaterialID);

			if (m_Mat)
			{
				if (m_Mat->IsColor())
				{
					glm::vec4 m_Color = m_Mat->GetColor();
					ImGui::Text("Difuse color");
					ImGui::Text("r: ");
					ImGui::SameLine();
					ImGui::Text(std::to_string(m_Color.r).c_str());
					ImGui::Text("g: ");
					ImGui::SameLine();
					ImGui::Text(std::to_string(m_Color.g).c_str());
					ImGui::Text("b: ");
					ImGui::SameLine();
					ImGui::Text(std::to_string(m_Color.b).c_str());
					ImGui::Text("a: ");
					ImGui::SameLine();
					ImGui::Text(std::to_string(m_Color.a).c_str());

					bool changed = false;
					float r = m_Color.r;
					float g = m_Color.g;
					float b = m_Color.b;
					float a = m_Color.a;
					ImGui::Text("Position");
					ImGui::Text("r");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(-FLT_MIN);
					if (ImGui::DragFloat("r", &r, 0.01f, 0.0f, 1.0f))
						changed=true;
					ImGui::Text("g");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(-FLT_MIN);
					if (ImGui::DragFloat("g", &g, 0.01f, 0.0f, 1.0f))
						changed = true;
					ImGui::Text("b");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(-FLT_MIN);
					if (ImGui::DragFloat("b", &b, 0.01f, 0.0f, 1.0f))
						changed = true;
					/*ImGui::Text("a");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(-FLT_MIN);
					if (ImGui::DragFloat("a", &a, 0.01f, 0.0f, 1.0f))
						changed = true;*/
					if (changed)
						m_Mat->setColor(glm::vec4(r, g, b, a));
				}
				else if (m_Mat->IsTexture())
				{
					std::string path = m_Mat->GetTexturePath().c_str();
					if (path != "null")
					{
						ImGui::Text("Texture path:");
						ImGui::Text(path.c_str()); // m_TexPath.c_str());
						ImGui::Image((ImTextureID)(intptr_t)m_Mat->GetTexture()->GetTextureId(), { 64, 64 });
					}

				}
				else
				{
					ImGui::Text("no material");
				}
			}
			else
			{
				ImGui::Text("no material");
			}
			/*static int selectedMat = -1;
			const char* names[] = { "material 1", "material 2", "material 3", "material 4", "material 5" };

			if (ImGui::Button("Select.."))
				ImGui::OpenPopup("my_select_popup");
			ImGui::SameLine();
			ImGui::TextUnformatted(selectedMat == -1 ? "<None>" : names[selectedMat]);
			if (ImGui::BeginPopup("my_select_popup"))
			{
				ImGui::Text("Assets");
				ImGui::Separator();
				for (int i = 0; i < IM_ARRAYSIZE(names); i++)
					if (ImGui::Selectable(names[i]))
						selectedMat = i;
				if (ImGui::Selectable("<None>"))
					selectedMat = -1;
				ImGui::EndPopup();
			}*/
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
				{
					const wchar_t* path = (const wchar_t*)payload->Data;
					std::filesystem::path& texpath = std::filesystem::path(s_AssetPath) / path;

					//setTexture(texpath.string().c_str());

					//setTexture(texpath.string().c_str());

				}
				ImGui::EndDragDropTarget();
			}

			ImGui::TreePop();
		}

	}
}