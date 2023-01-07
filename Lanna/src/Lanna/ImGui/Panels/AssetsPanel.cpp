#include "lnpch.h"

#include "imgui.h"
#include "Panel.h"
#include "AssetsPanel.h"
#include "Lanna/Application.h"
#include "Lanna/Resources/Texture.h"
#include "Lanna/Utilities/FileDialog.h"
#include "Lanna/Resources.h"


#include <Windows.h>

#ifdef ANI_UPDATE

namespace Lanna {
	extern const std::filesystem::path s_AssetPath = "resources";
	AssetsPanel::AssetsPanel() :Panel("Resources"), m_CurrentDirectory(s_AssetPath)
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
		
		static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;

		
		if (ImGui::BeginTable("table", 2, flags))
		{
			ImGui::TableNextColumn();

			ImGui::Text("Thumbnail Size");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 32, 128);

			ImGui::Text("Padding");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			ImGui::SliderFloat("Padding", &padding, thumbnailSize / 2, thumbnailSize);


			ImGui::TextWrapped("JUST SELECT RESOURCES that are inside Editor");


			if (ImGui::Button("Import"))
			{
				action = IMPORT;
				mPath = FileDialog::OpenFile("");
			}

			if (mPath != std::string())
			{
				std::string folder = "Editor\\";
				std::string nPath = mPath.substr(mPath.find(folder) + 7, mPath.length());

				for (int i = 0; i < nPath.length(); i++)
				{
					if (nPath[i] == '\\')
						nPath[i] = '/';
				}
				mPath = nPath;
				//ImGui::OpenPopup("Import options");
				ImportOptions(nullptr);
			}


			// COMPROBRA EXTENSION
			// Import configuration segun la extension
			

			//----------------------------------------------------------------------
			
			ImGui::TableNextColumn();
			// all resources
			ImGui::TextWrapped("resources");


			ImGui::EndTable();
		}


		ImGui::End();
	}

	void AssetsPanel::ImportOptions(const char* file)
	{
		if (file != nullptr) mPath = file;
		FileType fileType = CheckExtension(GetExtension(mPath.c_str()));

		/*switch (fileType)
		{
		case LFT_Error:				ImGui::OpenPopup("Error FileType");			break;
		case LFT_Texture:			LN_RESOURCES.Import<Texture>(mPath.c_str());						break;
		case LFT_FBX:				ImGui::OpenPopup("FBX OPTIONS");			break;
		case LFT_Material:			LN_RESOURCES.Import<Material>(mPath.c_str());						break;
		case LFT_Mesh:				LN_RESOURCES.Import<Mesh>(mPath.c_str());							break;
		case LFT_Skeleton:			ImGui::OpenPopup("SKELLETON OPTIONS");		break;
		case LFT_Animation:			ImGui::OpenPopup("ANIMATION OPTIONS");		break;
		case LFT_Files_Max:			break;
		default:
			break;
		}*/


		if (ImGui::BeginPopup("Error FileType"))
		{
			ImGui::Text("Wrong file type");
			mPath = std::string();
			if (ImGui::Button("OK")) ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}

		if (ImGui::BeginPopup("FBX OPTIONS"))
		{
			ImGui::EndPopup();
		}
	}


}

#else

namespace Lanna {

	extern const std::filesystem::path s_AssetPath = "resources";
	//extern const std::filesystem::path s_AssetPath = "C:/";

	AssetsPanel::AssetsPanel() :Panel("Resources"), m_CurrentDirectory(s_AssetPath)
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

#ifndef NEW_ASSETS_PANEL

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
#else
		if (resFolder == Resources::ResourceType::LRT_LAST)
		{
			ImGui::Text("Select a folder");
		}
		else
		{
			//const char* ResourcesName[4] = { "Texture", "Shaders", "Meshes", "Materials" };
			if (ImGui::Button("<-"))
			{

				resFolder = Resources::ResourceType::LRT_LAST;
				resId = -1;
			}
			ImGui::SameLine();
			if (resFolder!= Resources::ResourceType::LRT_LAST)
				ImGui::Text(ResourcesName[resFolder]);
		}

		cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		Texture* icon;

		if (resFolder == Resources::ResourceType::LRT_LAST)
		{
			//const char* ResourcesName[4] = { "Texture", "Shaders", "Meshes", "Materials" };
			ImGui::Columns(columnCount, 0, false);
			
			for (int i = 0; i < (int)Resources::ResourceType::LRT_LAST; i++)
			{
				ImGui::PushID(i);
				if (ImGui::ImageButton((ImTextureID)m_dirIcon->GetTextureId(), { thumbnailSize, thumbnailSize }, { 1, 0 }, { 0, 1 }))
				{
					resFolder = (Resources::ResourceType)i;
				}
				ImGui::TextWrapped(ResourcesName[i]);
				ImGui::PopID();
				ImGui::NextColumn();
			}
		}
		else
		{
			ImGui::Columns(columnCount, 0, false);
			for (int i = 0; i < LN_RESOURCES.GetList(resFolder)->size(); i++)
			{
				ImGui::PushID(i);
				if (ImGui::ImageButton((ImTextureID)m_fileIcon->GetTextureId(), { thumbnailSize, thumbnailSize }))
				{
					resId = i;
				}
				const char* text = LN_RESOURCES.GetList(resFolder)->at(i)->filePath.c_str();
				ImGui::TextWrapped(GetFileName(text).c_str());
				ImGui::PopID();
				ImGui::NextColumn();
			}
		}

		
#endif // !NEW_ASSETS_PANEL
		ImGui::End();
		DrawConfigurations();
		//AssetInspector();
	}

	void AssetsPanel::DrawConfigurations()
	{
		ImGui::Begin("Assets Configuration", &active);
		std::string path;

		/*ImGui::Text("Asset viewer");
	
		
		ImGui::Separator();*/

		ImGui::TextWrapped("JUST SELECT RESOURCES that are inside Editor");

		if (ImGui::Button("Import"))
		{
			action = IMPORT;
			ImGui::OpenPopup("import selector");
		}

		if (ImGui::BeginPopup("import selector"))
		{
			ImGui::Text("Import type");
			ImGui::Separator();
			if (ImGui::Selectable("Texture"))
			{
				resImportType = Resources::ResourceType::LRT_TEXTURE;
				path = FileDialog::OpenFile("");
				//path = FileDialog::OpenFile("Image (*.png)(*.bmp)(*.jpg)(*.dds)\0*.png\0*.bmp\0*.jpg\0*.dds\0");
			}
			if (ImGui::Selectable("Material"))
			{
				resImportType = Resources::ResourceType::LRT_TEXTURE;
				path = FileDialog::OpenFile("");
				//path = FileDialog::OpenFile("Material (*.png)(*.bmp)(*.jpg)(*.dds)(*.lnmaterial)\0*.png\0*.bmp\0*.jpg\0*.dds\0.lnmaterial\0");
			}
			if (ImGui::Selectable("Mesh"))
			{
				resImportType = Resources::ResourceType::LRT_MESH;
				path = FileDialog::OpenFile("");
				//path = FileDialog::OpenFile("Mesh (*.fbx)(*.FBX)(*.dae)(*.DAE)(*.lnmesh)(*.LNMESH)\0*.fbx\0*.FBX\0*.dae\0*.DAE\0*.lnmesh\0*.LNMESH\0");
			}
			/*if (ImGui::Selectable("Shader"))
			{
				resType = Resources::ResourceType::LRT_SHADER;
				path = FileDialog::OpenFile("Shader (*.vs)(*.fs)(*lnshader)\0*.vs\0*.fs\0*.lnshader\0");
			}*/
			if (ImGui::Selectable("Animation"))
			{
				resImportType = Resources::ResourceType::LRT_ANIMATION;
				path = FileDialog::OpenFile("");
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

			//LN_INFO(nPath.c_str());

			if (action == IMPORT)
			{
				switch (resImportType)
				{
				case Lanna::Resources::LRT_TEXTURE:		LN_RESOURCES.Import<Texture>(nPath.c_str());
					break;
				case Lanna::Resources::LRT_SHADER:		LN_RESOURCES.Import<Texture>(nPath.c_str());
					break;
				case Lanna::Resources::LRT_MESH:		LN_RESOURCES.Import<Mesh>(nPath.c_str());
					break;
				case Lanna::Resources::LRT_MATERIAL:	LN_RESOURCES.Import<Material>(nPath.c_str());
					break;
				case Lanna::Resources::LRT_ANIMATION:
					// 


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

		//ImportPopUp();

		AssetInspector();

		ImGui::End();
	}
	//const char* AssetsPanel::ImportPopUp()
	//{
	//	if (ImGui::BeginPopupModal("Import", NULL, ImGuiWindowFlags_MenuBar))
	//	{
	//		bool changes_happened = false;

	//		if (ImGui::BeginMenuBar())
	//		{
	//			
	//			//std::string textBar= m_importDirectory.string();
	//			ImGui::Text(m_importDirectory.string().c_str());

	//			ImGui::EndMenuBar();
	//		}
	//		//------------------------------------------------
	//		

	//		//---------------------------------------------
	//		if (ImGui::Button("Import")) {
	//			// importation stuff
	//			ImGui::CloseCurrentPopup();
	//		}
	//		if (ImGui::Button("Load"))
	//		{
	//			
	//		}
	//		ImGui::SameLine();
	//		if (ImGui::Button("Close"))
	//			ImGui::CloseCurrentPopup();
	//		ImGui::EndPopup();
	//	}
	//	return nullptr;
	//}
	void AssetsPanel::AssetInspector()
	{
		if (resId != -1)
		{
			std::string path=std::string();
			ImGui::Separator();
			//const char* ResourcesName[4] = { "Texture", "Shaders", "Meshes", "Materials" };
			ImGui::Text("AssetType: ");
			ImGui::SameLine();
			ImGui::Text(ResourcesName[resFolder]);

			ImGui::Text("Path: ");
			const char* text = LN_RESOURCES.GetList(resFolder)->at(resId)->filePath.c_str();
			ImGui::TextWrapped(text);
			if (ImGui::SmallButton("Save"))
			{
				if (resFolder == Resources::ResourceType::LRT_MATERIAL)		LN_RESOURCES.Save<Material>(resId);
				if (resFolder == Resources::ResourceType::LRT_MESH)			LN_RESOURCES.Save<Mesh>(resId);
				/*if (resFolder == Resources::ResourceType::LRT_SHADER)		LN_RESOURCES.Save<Shader>(resId);
				if (resFolder == Resources::ResourceType::LRT_TEXTURE)		LN_RESOURCES.Save<Texture>(resId);*/
			}
			if (ImGui::SmallButton("Load"))
			{
				path = FileDialog::OpenFile("");
			}
			/*if (ImGui::SmallButton("Delete"))
			{

			}*/
			if (path != std::string())
			{
				std::string folder = "Editor\\";
				std::string nPath = path.substr(path.find(folder) + 7, path.length());

				for (int i = 0; i < nPath.length(); i++)
				{
					if (nPath[i] == '\\')
						nPath[i] = '/';
				}

				//LN_INFO(nPath.c_str());
				if (resFolder == Resources::ResourceType::LRT_MATERIAL)		LN_RESOURCES.Load<Material>(resId, nPath.c_str());
				if (resFolder == Resources::ResourceType::LRT_MESH)		LN_RESOURCES.Load<Mesh>(resId, nPath.c_str());
			}

		}
		
		
	}
	
}

#endif // ANI_UPDATE