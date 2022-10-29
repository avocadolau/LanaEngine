#include "lnpch.h"
#include "ScenePanel.h"
#include <Lanna/Application.h>
#include <Lanna/Render3D.h>
#include <imgui.h>

ScenePanel::ScenePanel(): Panel("Scene")
{
	active = true;
	m_Shadings.push_back(new ShadingView("Default", true));
	m_Shadings.push_back(new ShadingView("Wireframe", true));
	m_Shadings.push_back(new ShadingView("Stil WIP T_T", true));


}

ScenePanel::~ScenePanel()
{

	m_Shadings.clear();
}

void ScenePanel::Draw()
{
	ImGui::Begin(name, &active, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Shading"))
		{
			for (auto c : m_Shadings)
			{
				if (ImGui::MenuItem(c->name, "", &c->active))
				{
					LN_INFO("{0}, {1}", c->name, c->active);
				}
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}


	// draw geometry
	
	DrawElements();

	ImGui::End();

}

void ScenePanel::DrawElements()
{
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	ImVec2 resolution = { 1920 , 1080 };
	ImVec2 scales = { viewportPanelSize.x / (float)resolution.x, viewportPanelSize.y / (float)resolution.y };

	float scale = scales.x < scales.y ? scales.x : scales.y;

	ImVec2 isize = { resolution.x * scale, resolution.y * scale };
	ImTextureID tex = (ImTextureID)(intptr_t)Lanna::Application::Get().GetRenderer().getColorBufferTexture();
	ImVec2 cpos = ImGui::GetCursorPos();
	cpos.x = (viewportPanelSize.x - isize.x) / 2;
	ImGui::SetCursorPos(cpos);

	ImGui::Image(tex, isize, ImVec2(0, 1), ImVec2(1, 0));
}
