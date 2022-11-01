#include "lnpch.h"

#include "imgui.h"
#include "Panel.h"
#include "AssetsPanel.h"
#include "Lanna/Renderer/Texture.h"

namespace Lanna {

	extern const std::filesystem::path s_AssetPath = "resources";

	AssetsPanel::AssetsPanel() :Panel("Assets"), m_CurrentDirectory(s_AssetPath)
	{
		m_dirIcon = new Texture();
		m_dirIcon->Init("resources/icons/ContentBrowser/DirectoryIcon.png");
		m_fileIcon = new Texture();
		m_fileIcon->Init("resources/icons/ContentBrowser/FileIcon.png");
	}

	AssetsPanel::~AssetsPanel()
	{

	}

	void AssetsPanel::Draw()
	{
		ImGui::Begin(name, &active);

		if (m_CurrentDirectory != std::filesystem::path(s_AssetPath))
		{
			if (ImGui::Button("<-"))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		static float padding = 16.0f;
		static float thumbnailSize = 128.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntry.path();
			auto relativePath = std::filesystem::relative(path, s_AssetPath);
			std::string filenameString = relativePath.filename().string();

			ImGui::PushID(filenameString.c_str());
			Texture* icon = directoryEntry.is_directory() ? m_dirIcon : m_fileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)m_fileIcon->GetTextureId(), {thumbnailSize, thumbnailSize}, {0, 1}, {1, 0});
			
			if (ImGui::BeginDragDropSource())
			{
				const wchar_t* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();
			}

			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directoryEntry.is_directory())
				{
					m_CurrentDirectory /= path.filename();
				}
			}
			ImGui::TextWrapped(filenameString.c_str());

			ImGui::NextColumn();
			ImGui::PopID();
		}
		ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);
		ImGui::End();
	}
}