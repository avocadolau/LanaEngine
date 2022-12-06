#include "lnpch.h"

#include "imgui.h"
#include "Panel.h"
#include "AssetsPanel.h"
#include "Lanna/Application.h"
#include "Lanna/Resources/Texture.h"
#include "Lanna/Utilities/FileDialog.h"
#include "Lanna/Resources.h"

#include <Windows.h>

namespace Lanna {

	extern const std::filesystem::path s_AssetPath = "resources";
	//extern const std::filesystem::path s_AssetPath = "C:/";

	AssetsPanel::AssetsPanel() :Panel("Assets"), m_CurrentDirectory(s_AssetPath)
	{
		m_dirIcon = new Texture();
		m_dirIcon->Init("resources/icons/ContentBrowser/DirectoryIcon.png");
		m_fileIcon = new Texture();
		m_fileIcon->Init("resources/icons/ContentBrowser/FileIcon.png");
		active = true;
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
			ImGui::SameLine();
			std::string text = m_CurrentDirectory.string();
			ImGui::Text(text.c_str());
		}

		cellSize = thumbnailSize + padding;

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
			Texture* icon;
			if (directoryEntry.is_directory()) icon = m_dirIcon;
			else icon = m_fileIcon;
			//Texture* icon = directoryEntry.is_directory() ? m_dirIcon : m_fileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)icon->GetTextureId(), {thumbnailSize, thumbnailSize}, {1, 0}, {0, 1});
			
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

		ImGui::End();
		DrawConfigurations();
	}

	void AssetsPanel::DrawConfigurations()
	{
		ImGui::Begin("Assets Configuration", &active);
		std::string path;

		if (ImGui::Button("Import"))
		{
			//path = FileDialog::OpenFile("Something (*.ln)\0*.ln\0");
			
			path = FileDialog::OpenFile("");

			if (path!= std::string())
			{
				LN_INFO(path.c_str());
				FileType type = CheckExtension(GetExtension(path.c_str()));
				switch (type)
				{
				case LFT_Error:
					break;
				case LFT_Texture:		LN_RESOURCES.Import<Texture>(path.c_str());
					break;
				case LFT_Object:
					break;
				case LFT_FBX:			LN_RESOURCES.Import<Mesh>(path.c_str());
					break;
				case LFT_Material:
					break;
				case LFT_Mesh:
					break;
				case LFT_Bilboad:
					break;
				case LFT_Skeleton:
					break;
				case LFT_Animation:
					break;
				case LFT_Files_Max:
					break;
				default:
					break;
				}
			}
			
			
		}

		ImGui::Text("Thumbnail Size");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 32, 128);

		ImGui::Text("Padding");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::SliderFloat("Padding", &padding, thumbnailSize/2, thumbnailSize);

		ImportPopUp();

		ImGui::End();
	}
	const char* AssetsPanel::ImportPopUp()
	{
		if (ImGui::BeginPopupModal("Import", NULL, ImGuiWindowFlags_MenuBar))
		{
			bool changes_happened = false;

			if (ImGui::BeginMenuBar())
			{
				
				//std::string textBar= m_importDirectory.string();
				ImGui::Text(m_importDirectory.string().c_str());

				ImGui::EndMenuBar();
			}
			//------------------------------------------------
			

			//---------------------------------------------
			if (ImGui::Button("Import")) {
				// importation stuff
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Close"))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}
		return nullptr;
	}
}