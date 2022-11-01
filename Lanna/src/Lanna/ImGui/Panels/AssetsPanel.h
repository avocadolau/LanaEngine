#pragma once

#include "lnpch.h"
#include "Panel.h"
#include "Lanna/Renderer/Texture.h"

namespace Lanna {
	class AssetsPanel :public Panel
	{
	public:
		AssetsPanel();
		~AssetsPanel();

		void Draw() override;

	private:
		std::filesystem::path m_CurrentDirectory;
		Texture* m_dirIcon;
		Texture* m_fileIcon;
	};
}