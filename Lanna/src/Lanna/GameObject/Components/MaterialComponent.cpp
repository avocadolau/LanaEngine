#include "lnpch.h"
#include "MaterialComponent.h"
#include "Lanna/GameObject/Component.h"

#include <imgui.h>
#include <glew.h>
#include <glm.hpp>

namespace Lanna
{
	extern const std::filesystem::path s_AssetPath;

	MaterialComponent::MaterialComponent() : Component(Component::Type::MATERIAL)
	{
		m_Type=NONE;
	}
	MaterialComponent::MaterialComponent(glm::vec4 color) : Component(Component::Type::MATERIAL), m_Type(COLOR), m_Color(color)
	{

	}
	MaterialComponent::MaterialComponent(const char* file) : Component(Component::Type::MATERIAL), m_Type(TEXTURE)
	{
		m_TexPath = file;
		if (!m_TexPath.empty())
		{
			m_texture = new Texture();
			m_texture->Init(file);
			m_texid = m_texture->GetTextureId();
			m_TexSize = m_texture->GetSize();
		}
	}

	MaterialComponent::~MaterialComponent()
	{

	}

	void MaterialComponent::setTexture(const char* file)
	{
		m_Type = TEXTURE;
		m_TexPath = file;
		/*if (m_texture!=nullptr)
			delete m_texture;*/
		m_texture = new Texture();
		m_texture->Init(file);
		m_texid = m_texture->GetTextureId();
		m_TexSize = m_texture->GetSize();
	}

	void MaterialComponent::Use()
	{
	}

	void MaterialComponent::ImGuiDraw()
	{

		if (ImGui::TreeNode("Material"))
		{
			if (m_Type == COLOR)
			{
				ImGui::Text("Texture path:");
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
			}
			else if (m_Type == TEXTURE)
			{
				ImGui::Text("Texture path:");
				ImGui::Text(m_TexPath.c_str());
				ImGui::Image((ImTextureID)(intptr_t)m_texture->GetTextureId(), { 64, 64 });
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

					setTexture(texpath.string().c_str());

				}
				ImGui::EndDragDropTarget();
			}

			ImGui::TreePop();
		}

	}
}