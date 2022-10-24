#include "lnpch.h"
#include "HierarchyPanel.h"
#include <list>
#include <algorithm>

#include "Lanna/Application.h"
#include "Lanna/EntityManager.h"
#include "Lanna/GameObject/GameObject.h"

HierarchyPanel::HierarchyPanel(): Panel("SceneObjects")
{

}

HierarchyPanel::~HierarchyPanel()
{

}

void HierarchyPanel::Draw()
{
	std::vector<GameObject*> entities = *Lanna::Application::Get().GetEntityManager()->GetEntityList();

	ImGui::Begin("Scene Game Objects", &active);

    static int selected = 0;
    {


        for (int i = 0; i < entities.size(); i++)
        {
            if (ImGui::Selectable(entities.at(i)->m_Name, selected == i))
                selected = i;
        }

        Lanna::Application::Get().GetEntityManager()->SetActiveEntity(selected);



        //ImGui::Separator();


        //static const char* item_names[] = { "Item One", "Item Two", "Item Three", "Item Four", "Item Five" };
        //for (int n = 0; n < IM_ARRAYSIZE(item_names); n++)
        //{
        //    const char* item = item_names[n];
        //    ImGui::Selectable(item);

        //    if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
        //    {
        //        int n_next = n + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
        //        if (n_next >= 0 && n_next < IM_ARRAYSIZE(item_names))
        //        {
        //            item_names[n] = item_names[n_next];
        //            item_names[n_next] = item;
        //            ImGui::ResetMouseDragDelta();
        //        }
        //    }

        //}
        //ImGui::Separator();

        //for (int i = 0; i < entities.size(); i++)
        //{
        //    if (ImGui::Selectable(entities.at(i)->m_Name))
        //    {
        //        selected = i;

        //    }

        //    if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
        //    {
        //        int n_next = i + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
        //        if (n_next >= 0 && n_next < entities.size())
        //        {
        //            //std::iter_swap(entities.at(i), entities.at(n_next));
        //            //std::swap(entities.at(i), entities.at(n_next));

        //            ImGui::ResetMouseDragDelta();
        //        }
        //    }

        //    Lanna::Application::Get().GetEntityManager()->SetActiveEntity(selected);
        //}
    }
	ImGui::End();	
}
