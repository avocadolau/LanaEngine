#pragma once
#include "Panel.h"
#include "lnpch.h"
#include "Lanna/Resources/Texture.h"

namespace Lanna {

	class GameScenePanel : public Panel
	{
	public:
		GameScenePanel();
		~GameScenePanel();

		void Draw() override;
		void DrawElements();

	};

}