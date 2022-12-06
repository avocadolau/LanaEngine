#include "lnpch.h"
#include "HierarchyPanel.h"
#include <list>
#include <algorithm>

#include "Lanna/Application.h"
#include "Lanna/EntityManager.h"
#include "Lanna/GameObject/GameObject.h"

namespace Lanna {
    HierarchyPanel::HierarchyPanel() : Panel("SceneObjects")
    {
        active = true;
    }

    HierarchyPanel::~HierarchyPanel()
    {

    }

    void HierarchyPanel::Draw()
    {
        std::vector<GameObject*> entities = *LN_ENTITY_MAN->GetEntityList();

        ImGui::Begin("Scene Game Objects", &active);

        if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(0)) {
            if (ImGui::BeginPopup("options uwu"))
            {

                ImGui::EndPopup();
            }
        }

        if (selected.size() == 0)
        {
            selected.push_back(0);
            selected.push_back(-1);
            selected.push_back(-1);
            selected.push_back(-1);
        }

        GameObject* selection;
        for (int i = 0; i < entities.size(); i++)
        {
            if (ImGui::Selectable(entities.at(i)->m_Name.c_str(), selected[0] == i&&root==0))
            {
                
            }
            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            {
                ImGui::OpenPopup("options");
                hovered = entities.at(i);
            }
            if (ImGui::IsItemClicked() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                for (int j : selected)
                {
                    j = -1;
                }
                selected[0] = i;
                root = 0;

            }
            if (selected[0] == i)
            {
                EntityChildren(entities.at(i), 1);

            }
            
        }
        
        PopMenu(hovered);

        LN_ENTITY_MAN->SetActiveEntity(&selected, root);
        
        ImGui::End();
    }
    void HierarchyPanel::PopMenu(GameObject* hover)
    {
        if (ImGui::BeginPopup("options"))
        {

            ImGui::Text(hover->m_Name.c_str());
            if (ImGui::Selectable("Add new entity"))
            {
                hover->AddEmptyChild();
            }
            if (ImGui::Selectable("Delete selected"))
            {
                if (hover->m_Parent)
                {
                    GameObject* del = hover;
                    hover->m_Parent->DestroyChild(del);
                    if (selected.at(root) == 0)
                    {
                        root--;
                    }
                    selected.at(root)--;
                }

                else
                {
                    LN_ENTITY_MAN->DestroyGameObject(hover);
                }
            }
            if (hover->m_Parent)
            {
                if (ImGui::Selectable("Unchild"))
                {
                    GameObject* del = hover;
                    hover->m_Parent->DelChild(del);
                    if (selected.at(root) == 0)
                    {
                        root--;
                    }
                    selected.at(root)--;

                }
            }
            
            ImGui::EndPopup();
        }
    }
    void HierarchyPanel::UpdateEntry(GameObject* entity)
    {

    }
    void HierarchyPanel::EntityChildren(GameObject* entity, int n)
    {
        if (selected.size() <= n)
            selected.push_back(-1);
        for (int i = 0; i < entity->m_Children.size(); i++)
        {
            std::string name;
            for (int i = 0; i < n; i++)name.append(" ");
            name.append("-");
            name.append(entity->m_Children.at(i)->m_Name);
            if (ImGui::Selectable(name.c_str(), selected[n] == i&& root==n))
            {

            }
            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            {
                ImGui::OpenPopup("options");
                hovered = entity->m_Children.at(i);
            }
            if (ImGui::IsItemClicked() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                selected[n] = i;
                for (int j = n + 1; j < selected.size(); j++)
                    selected[j] = -1;
                root = n;

            }
            if (selected[n] == i)
            {
                EntityChildren(entity->m_Children.at(i), n + 1);
            }

        }
    }
}