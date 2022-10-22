#include "lnpch.h"
#include "HierarchyPanel.h"
#include <list>

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

        /*for (GameObject* comps : entities)
        {
            if (ImGui::Selectable(comps->m_Name, selected == i))
                selected = i;
            i++;
        }*/

        for (int i = 0; i < entities.size(); i++)
        {
            if (ImGui::Selectable(entities.at(i)->m_Name, selected == i))
                selected = i;
        }

        Lanna::Application::Get().GetEntityManager()->SetActiveEntity(selected);
    }


	ImGui::End();	
}
