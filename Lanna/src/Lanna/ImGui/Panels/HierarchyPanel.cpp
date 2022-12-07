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
        selected = &LN_ENTITY_MAN->selected;
    }

    HierarchyPanel::~HierarchyPanel()
    {

    }

    void HierarchyPanel::Draw()
    {
        bool changed = false;
        std::vector<GameObject*> entities = *LN_ENTITY_MAN->GetEntityList();

        ImGui::Begin("Scene Game Objects", &active);

        if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(0)) {
            if (ImGui::BeginPopup("options uwu"))
            {

                ImGui::EndPopup();
            }
        }

        if (selected->size() == 0)
        {
            selected->push_back(0);
            selected->push_back(-1);
            selected->push_back(-1);
            selected->push_back(-1);
        }

        for (int i = 0; i < entities.size(); i++)
        {
            if (ImGui::Selectable(entities.at(i)->m_Name.c_str(), selected->at(0) == i && LN_ENTITY_MAN->GetRoot() == 0))
            {
                
            }
            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            {
                ImGui::OpenPopup("options");
                hovered = entities.at(i);
            }
            if (ImGui::IsItemClicked() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                for (int j : *selected)
                {
                    j = -1;
                }
                selected->at(0) = i;
                LN_ENTITY_MAN->SetRoot(0);
                changed = true;
            }
            if (selected->at(0) == i)
            {
                if (EntityChildren(entities.at(i), 1) == true)
                    changed = true;

            }
            
        }
        
        PopMenu(hovered);

        if (changed==true)
            LN_ENTITY_MAN->SetActiveEntity(selected);
        
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
                    LN_ENTITY_MAN->SetRoot(1);
                    selected->at(0) = 0;
                    for (int i = 1; i < selected->size(); i++)
                    {
                        selected->at(i) = -1;
                    }
                    LN_ENTITY_MAN->activeFromSelection = true;
                    LN_ENTITY_MAN->SetActiveEntity(selected);
                }

                else
                {
                    LN_ENTITY_MAN->DestroyGameObject(hover);
                }
            }
            if (hover)
            {
                if (hover->m_Parent)
                {
                    if (ImGui::Selectable("Unchild"))
                    {
                        GameObject* del = hover;
                        hover->m_Parent->DelChild(del);
                        LN_ENTITY_MAN->SetRoot(1);
                        selected->at(0) = 0;
                        for (int i = 1; i < selected->size(); i++)
                        {
                            selected->at(i) = -1;
                        }
                        LN_ENTITY_MAN->activeFromSelection = true;
                    }
                }
            }
            if (hover)
            {
                if (hover->m_Children.size() > 0)
                {
                    if (ImGui::Selectable("Clear children"))
                    {
                        hover->m_Children.clear();
                        LN_ENTITY_MAN->SetRoot(1);
                        selected->at(0) = 0;
                        for (int i = 1; i < selected->size(); i++)
                        {
                            selected->at(i) = -1;
                        }
                        LN_ENTITY_MAN->activeFromSelection = true;
                    }
                }
            }
            
            if (ImGui::BeginMenu("entitiesList"))
            {
                for (int i = 0; i < LN_ENTITY_MAN->GetEntityList()->size(); i++)
                {
                    GameObject* entity = LN_ENTITY_MAN->GetEntityList()->at(i);
                    if (entity == hover) continue;
                    else
                    {
                        if (ImGui::MenuItem(entity->m_Name.c_str()))
                        {
                            hover->Reparent(entity);
                        }
                        AllChildrenList(hover, entity);
                    }
                }
                ImGui::EndMenu();
            }

            ImGui::EndPopup();
        }
    }
    void HierarchyPanel::UpdateEntry(GameObject* entity)
    {

    }
    bool HierarchyPanel::EntityChildren(GameObject* entity, int n)
    {
        bool ret = false;
        if (selected->size() <= n)
            selected->push_back(-1);
        for (int i = 0; i < entity->m_Children.size(); i++)
        {
            std::string name;
            for (int i = 0; i < n; i++)name.append(" ");
            name.append("-");
            name.append(entity->m_Children.at(i)->m_Name);
            if (ImGui::Selectable(name.c_str(), selected->at(n) == i&& LN_ENTITY_MAN->GetRoot() == n))
            {

            }
            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            {
                ImGui::OpenPopup("options");
                hovered = entity->m_Children.at(i);
            }
            if (ImGui::IsItemClicked() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                selected->at(n) = i;
                for (int j = n + 1; j < selected->size(); j++)
                    selected->at(j) = -1;
                LN_ENTITY_MAN->SetRoot(n);
                ret = true;
            }
            if (selected->at(n) == i)
            {
                if (EntityChildren(entity->m_Children.at(i), n + 1) == true)
                    ret = true;
            }

        }
        return ret;
    }
    GameObject* HierarchyPanel::AllChildrenList(GameObject* hover, GameObject* entity)
    {
        for (int i = 0; i < entity->m_Children.size(); i++)
        {
            GameObject* o= entity->m_Children.at(i);
            if (entity == hover) continue;
            else
            {
                if (ImGui::MenuItem(o->m_Name.c_str()))
                {
                    hover->Reparent(o);
                }
                AllChildrenList(hover, o);
            }
        }
        return entity;
    }
}