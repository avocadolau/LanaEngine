#pragma once

#include "lnpch.h"
#include "Panel.h"
#include "Lanna/Resources/Texture.h"
#include "Lanna/Resources.h"

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
		const char* ImportPopUp();

	private:
		Resources::ResourceType resType = Resources::ResourceType::LRT_LAST;
		ResourceActions action = NONE;
		std::filesystem::path m_CurrentDirectory;
		std::filesystem::path m_importDirectory;
		Texture* m_dirIcon;
		Texture* m_fileIcon;

		float padding = 16.0f;
		float thumbnailSize = 32.0f;
		float cellSize;
	};
}