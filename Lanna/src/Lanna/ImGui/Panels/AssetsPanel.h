#pragma once

#include "lnpch.h"
#include "Panel.h"
#include "Lanna/Resources/Texture.h"
#include "Lanna/Resources.h"

#define NEW_ASSETS_PANEL
#define ANI_UPDATE
typedef size_t ResourceId;

namespace Lanna {
	class AssetsPanel :public Panel
	{
	public:
		enum ResourceActions
		{
			IMPORT,
			SAVE,
			LOAD,
			NONE =-1
		};
		

		AssetsPanel();
		~AssetsPanel();

		void Draw() override;
		void DrawConfigurations();
		void AssetInspector();
		
		void ImportOptions(const char* file);
	private:

#ifdef ANI_UPDATE

		std::string mPath;


#endif // 

		Resources::ResourceType resImportType = Resources::ResourceType::LRT_LAST;
		Resources::ResourceType resFolder = Resources::ResourceType::LRT_LAST;
		ResourceId resId = -1;
		ResourceActions action = NONE;
		std::filesystem::path m_CurrentDirectory;
		std::filesystem::path m_importDirectory;
		Texture* m_dirIcon;
		Texture* m_fileIcon;
		
		const char* ResourcesName[4] = { "Texture", "Shaders", "Meshes", "Materials" };
		float padding = 16.0f;
		float thumbnailSize = 32.0f;
		float cellSize;
	};
}