#pragma once

#include "lnpch.h"
#include "Panel.h"
#include "Lanna/Resources/Texture.h"

namespace Lanna {
	class AssetsPanel :public Panel
	{
	public:
		AssetsPanel();
		~AssetsPanel();

		void Draw() override;
		void DrawConfigurations();
		const char* ImportPopUp();

	private:
		std::filesystem::path m_CurrentDirectory;
		std::filesystem::path m_importDirectory;
		Texture* m_dirIcon;
		Texture* m_fileIcon;

		float padding = 16.0f;
		float thumbnailSize = 32.0f;
		float cellSize;
	};
}