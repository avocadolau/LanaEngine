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

		ImGui::TextWrapped("JUST SELECT RESOURCES that are inside Editor");

		if (ImGui::Button("Import"))
		{
			
			action = IMPORT;
			ImGui::OpenPopup("import selector");
			

			//path = FileDialog::OpenFile("Something (*.ln)\0*.ln\0");

			////path = FileDialog::OpenFile("");

			//

			
			
			
		}
		ImGui::SameLine();
		if (ImGui::Button("Load"))
		{
			path = FileDialog::OpenFile("");
			if (path != std::string())
			{
				LN_INFO(path.c_str());
				std::string ext = GetExtension(path.c_str());

				if (ext == ".lnmesh")
				{
					ResourceId id = LN_RESOURCES.PushEmptyResource(Resources::ResourceType::LRT_MESH);
					LN_RESOURCES.Load<Mesh>(id, path.c_str());
				}
				if (ext == ".lnmaterial")
				{
					ResourceId id = LN_RESOURCES.PushEmptyResource(Resources::ResourceType::LRT_MATERIAL);
					LN_RESOURCES.Load<Material>(id, path.c_str());
				}

				
			}
			
		}

		if (ImGui::BeginPopup("import selector"))
		{
			ImGui::Text("Import type");
			ImGui::Separator();
			if (ImGui::Selectable("Texture"))
			{
				resType = Resources::ResourceType::LRT_TEXTURE;
				path = FileDialog::OpenFile("Image (*.png)(*.bmp)(*jpg)(*dds)\0*.png\0*.bmp\0*.jpg\0*.dds\0");
			}
			if (ImGui::Selectable("Mesh"))
			{
				resType = Resources::ResourceType::LRT_MESH;
				path = FileDialog::OpenFile("Image (*.fbx)(*.FBX)(*dae)(*DAE)\0*.fbx\0*.FBX\0*.dae\0*.DAE\0");
			}
			ImGui::EndPopup();
		}



		if (path != std::string())
		{
			std::string folder = "Editor\\";
			std::string nPath = path.substr(path.find(folder) + 7, path.length());

			for (int i = 0; i < nPath.length(); i++)
			{
				if (nPath[i] == '\\')
					nPath[i] = '/';
			}

			LN_INFO(nPath.c_str());

			if (action == IMPORT)
			{
				switch (resType)
				{
				case Lanna::Resources::LRT_TEXTURE:	LN_RESOURCES.Import<Texture>(nPath.c_str());
					break;
				case Lanna::Resources::LRT_SHADER:
					break;
				case Lanna::Resources::LRT_MESH:	LN_RESOURCES.Import<Mesh>(nPath.c_str());
					break;
				case Lanna::Resources::LRT_MATERIAL:
					break;
				case Lanna::Resources::LRT_LAST:
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
			if (ImGui::Button("Load"))
			{
				
			}
			ImGui::SameLine();
			if (ImGui::Button("Close"))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}
		return nullptr;
	}
}