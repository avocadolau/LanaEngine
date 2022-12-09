#include "lnpch.h"
#include "Lanna/Core.h"
#include "ScenePanel.h"
#include <Lanna/Application.h>
#include "Lanna/EntityManager.h"
#include <Lanna/Render3D.h>
#include <imgui.h>
#include "Lanna/Resources/Texture.h"
#include "Lanna/Utilities/Time.h"
#include "Lanna/Input.h"
#include "Lanna/KeyCodes.h"
#include <glew.h>
#include <glm.hpp>

#include "Lanna/Utilities/Maths/Math.h"

namespace Lanna {

	extern const std::filesystem::path s_AssetPath;

	ScenePanel::ScenePanel() : Panel("Scene")
	{
		active = true;
		m_Shadings.push_back(new ShadingView("Default", true));
		m_Shadings.push_back(new ShadingView("Wireframe", true));
		m_Shadings.push_back(new ShadingView("Stil WIP T_T", true));

		/*m_IconPlay = new Texture();
		m_IconPlay->Init("resources/icons/PlayButton.png");
		m_IconStop = new Texture();
		m_IconStop->Init("resources/icons/StopButton.png");*/
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
		//LN_RENDERER.RenderGrid();

		ImVec2 isize = { resolution.x * scale, resolution.y * scale };
		ImTextureID tex = (ImTextureID)(intptr_t)LN_RENDERER.getColorBufferTexture();
		ImVec2 cpos = ImGui::GetCursorPos();
		cpos.x = (viewportPanelSize.x - isize.x) / 2;
		ImGui::SetCursorPos(cpos);

		if (Lanna::Input::IsMouseButtonPressed(0))//&& !ImGuizmo::IsUsing())
		{
			glm::vec3 out_dir;
			glm::vec3 out_origin;

			ImVec2 mpos = ImGui::GetMousePos();
			ImVec2 cspos = ImGui::GetCursorScreenPos();

			ImVec2 rpos = { mpos.x - cspos.x, mpos.y - cspos.y };
			CLAMP(rpos.x, 0.0f, isize.x);
			CLAMP(rpos.y, 0.0f, isize.y);

			Lanna::Vector2f v2f = { rpos.x / (float)isize.x, rpos.y / (float)isize.y };
			rpos.y -= isize.y;
			rpos.y = glm::abs(rpos.y);

			CameraComponent* m_Camera = &LN_RENDERER.GetActiveCamera();
			Lanna::Math::ScreenPosToWorldRay(rpos.x, rpos.y, isize.x, isize.y, m_Camera->getView(), m_Camera->getProjection(), out_origin, out_dir);
			float minDist = FLT_MAX;
			int id = -1;
			for (size_t i = 0; i < LN_ENTITY_MAN->GetEntityList()->size(); i++)
			{
				if (!LN_ENTITY_MAN->GetEntityList()->at(i)->m_Mesh)
					continue;
				if (LN_ENTITY_MAN->GetEntityList()->at(i)->m_Mesh->m_MeshID == -1)
					continue;
				Lanna::Mesh* model = Lanna::Resources::GetResourceById<Mesh>(LN_ENTITY_MAN->GetEntityList()->at(i)->m_Mesh->m_MeshID);
				Lanna::TransformComponent* trs = LN_ENTITY_MAN->GetEntityList()->at(i)->m_Transform;
				glm::mat4 transform(1.0f);
				glm::vec3 scale = glm::vec3(trs->w_Scl.x, trs->w_Scl.y, trs->w_Scl.z);
				transform = glm::translate(transform, glm::vec3(trs->w_Pos.x, trs->w_Pos.y, trs->w_Pos.z));
				transform = glm::rotate(transform, trs->w_Rot.x, { 1,0,0 });
				transform = glm::rotate(transform, trs->w_Rot.y, { 0,1,0 });
				transform = glm::rotate(transform, trs->w_Rot.z, { 0,0,1 });
				transform = glm::scale(transform, scale);
				float intersectDist = 0.0f;
				if (Lanna::Math::TestRayOBBIntersection(
					out_origin,
					out_dir,
					model->aabb.getMin() * scale,
					model->aabb.getMax() * scale,
					transform,
					intersectDist
				))
				{
					if (i == 0)
					{
						minDist = intersectDist;
						id = i;
					}
					else if (intersectDist < minDist)
					{
						minDist = intersectDist;
						id = i;
					}
				}
			}
			if (id >= 0)
				LN_ENTITY_MAN->SetActiveEntity(LN_ENTITY_MAN->GetEntityList()->at(id));

		}



		ImGui::Image(tex, isize, ImVec2(0, 1), ImVec2(1, 0));

	}
	void ScenePanel::ImportFBX(const std::filesystem::path& path)
	{	
		GameObject* newFBX = LN_ENTITY_MAN->AddEmptyGameObject(path.filename().string().c_str());
		newFBX->AddComponent(Component::Type::MESH);
		newFBX->m_Mesh->LoadFromFile(path.string().c_str());
	}
	//
	//void ScenePanel::OnScenePlay()
	//{
	//}
	//
	//void ScenePanel::OnSceneStop()
	//{
	//}
}