#include "lnpch.h"
#include "GameScenePanel.h"
#include <Lanna/Application.h>
#include <Lanna/Render3D.h>
#include <imgui.h>
#include "Lanna/Resources/Texture.h"
#include "Lanna/Utilities/Time.h"

namespace Lanna {

	extern const std::filesystem::path s_AssetPath;

	GameScenePanel::GameScenePanel() : Panel("Game Scene")
	{
		active = true;
	}

	GameScenePanel::~GameScenePanel()
	{

	}

	void GameScenePanel::Draw()
	{
		ImGui::Begin(name, &active);

		// draw geometry

		DrawElements();


		ImGui::End();

	}

	void GameScenePanel::DrawElements()
	{
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		ImVec2 resolution = { 1920 , 1080 };
		ImVec2 scales = { viewportPanelSize.x / (float)resolution.x, viewportPanelSize.y / (float)resolution.y };

		float scale = scales.x < scales.y ? scales.x : scales.y;

		static bool grid = true;
		//LN_RENDERER.RenderGrid();

		ImVec2 isize = { resolution.x * scale, resolution.y * scale };
		ImTextureID tex = (ImTextureID)(intptr_t)LN_RENDERER.getColorBufferTexture();
		ImVec2 cpos = ImGui::GetCursorPos();
		cpos.x = (viewportPanelSize.x - isize.x) / 2;
		ImGui::SetCursorPos(cpos);

		ImGui::Image(tex, isize, ImVec2(0, 1), ImVec2(1, 0));
	}


}