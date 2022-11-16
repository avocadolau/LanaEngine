#include "lnpch.h"
#include "ScenePanel.h"
#include <Lanna/Application.h>
#include <Lanna/Render3D.h>
#include <imgui.h>

namespace Lanna {

	extern const std::filesystem::path s_AssetPath;

	ScenePanel::ScenePanel() : Panel("Scene")
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
						_LN_INFO("{0}, {1}", c->name, c->active);
					}
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}


		// draw geometry

		DrawElements();

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			{
				const wchar_t* path = (const wchar_t*)payload->Data;
				ImportFBX(std::filesystem::path(s_AssetPath) / path);
			}
			ImGui::EndDragDropTarget();
		}

		ImGui::End();

	}

	void ScenePanel::DrawElements()
	{
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		ImVec2 resolution = { 1920 , 1080 };
		ImVec2 scales = { viewportPanelSize.x / (float)resolution.x, viewportPanelSize.y / (float)resolution.y };

		float scale = scales.x < scales.y ? scales.x : scales.y;

		static bool grid = true;
		Lanna::Application::Get().GetRenderer().RenderGrid();

		ImVec2 isize = { resolution.x * scale, resolution.y * scale };
		ImTextureID tex = (ImTextureID)(intptr_t)Lanna::Application::Get().GetRenderer().getColorBufferTexture();
		ImVec2 cpos = ImGui::GetCursorPos();
		cpos.x = (viewportPanelSize.x - isize.x) / 2;
		ImGui::SetCursorPos(cpos);

		ImGui::Image(tex, isize, ImVec2(0, 1), ImVec2(1, 0));
	}
	void ScenePanel::ImportFBX(const std::filesystem::path& path)
	{	
		GameObject* newFBX = Lanna::Application::Get().GetEntityManager()->AddEmptyGameObject(path.filename().string().c_str());
		newFBX->AddComponent(Component::Type::MESH);
		newFBX->m_Mesh->LoadFromFile(path.string().c_str());
	}
}