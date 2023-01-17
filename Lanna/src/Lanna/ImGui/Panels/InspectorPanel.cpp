#include "lnpch.h"
#include "imgui.h"
#include <list>

#include "InspectorPanel.h"
#include "Lanna/Application.h"

#include "Lanna/EntityManager.h"
#include "Lanna/GameObject/GameObject.h"
#include "Lanna/GameObject/Components/TransformComponent.h"
#include "Lanna/GameObject/Components/MeshComponent.h"
#include "Lanna/GameObject/Components/MaterialComponent.h"
#include "Lanna/GameObject/Components/CameraComponent.h"

namespace Lanna {
	InspectorPanel::InspectorPanel() : Panel("Inspector")
	{
		active = true;
	}

	InspectorPanel::~InspectorPanel()
	{

	}


	void InspectorPanel::ShowObjectHierarchy(GameObject* obj)
	{
		bool node_open = ImGui::TreeNode(obj->m_Name.c_str());
		ImGui::SameLine();
		/*if (ImGui::SmallButton("Del"))
			obj->DelParent();*/

		if (node_open)
		{
			for (GameObject* o : obj->m_Children)
			{
				ShowObjectHierarchy(o);
			}
			ImGui::TreePop();
		}
	}

	void InspectorPanel::Draw()
	{
		bool changes_happened = false;
		GameObject* activeObject = LN_ENTITY_MAN->GetActiveEntitiy();

		ImGui::Begin("Inspector", &active);
		if (activeObject != nullptr)
		{
			//char nName[25] = { activeObject->m_Name.c_str() };
			//changes_happened |= ImGui::InputText("##EntityNameInspector",nName, sizeof(entity->name));
			
			static char buff[20];
			int size = activeObject->m_Name.size();
			*buff = *activeObject->m_Name.c_str();
			for (int i = 0; i < 20; i++)
			{
				if (i < size)
					buff[i] = activeObject->m_Name.at(i);
				else buff[i] = ' ';
			}

			changes_happened |= ImGui::InputText("##EntityNameInspector", buff, sizeof(buff));

			activeObject->m_Name = buff;
			//ImGui::Text(activeObject->m_Name.c_str());

			ImGui::Text("Parent: ");
			ImGui::SameLine();
			if (activeObject->m_Parent == nullptr)
			{
				ImGui::Text("None");
			}
			else {
				ImGui::Text(activeObject->m_Parent->m_Name.c_str());
				/*ImGui::SameLine();
				if (ImGui::SmallButton("Del")) {
					GameObject* copy = new GameObject(activeObject);
					GameObject* parent = activeObject->m_Parent;
					parent->DelChild(activeObject);
					LN_ENTITY_MAN->AddGameObject(copy);
					activeObject = copy;
				}*/
			}


			/*ImGui::Text("Children");
			if(activeObject->m_Children.size()>0)
				ShowObjectHierarchy(activeObject);*/


				/*bool node_open = ImGui::TreeNode("Children");
				if (node_open)
				{
					for (GameObject* o : activeObject->m_Children)
					{
						ShowObjectHierarchy(o);
					}
					ImGui::TreePop();
				}
				if (ImGui::SmallButton("Add")) {}*/


				// components
			ImGui::Separator();
			/*activeObject->m_Transform->ImGuiDraw();*/
			
			
			for (Component* comps : activeObject->m_Components)
			{
				comps->ImGuiDraw();
			}

			for (int i = activeObject->m_Components.size() - 1; i >= 0; i--)
			{
				Component* comp = activeObject->m_Components.at(i);
				if (comp->toDel==true)
				{
					if (comp->m_Type == Component::Type::MESH)activeObject->m_Mesh = nullptr;
					if (comp->m_Type == Component::Type::MATERIAL)activeObject->m_Material = nullptr;
					if (comp->m_Type == Component::Type::CAMERA)activeObject->m_Camera = nullptr;
					if (comp->m_Type == Component::Type::SKELETON)activeObject->m_Skeleton = nullptr;
					if (comp->m_Type == Component::Type::ANIMATION)activeObject->m_Anim = nullptr;
					activeObject->DestroyComponent(comp);
				}
			}

			if (activeObject->loockComonents == false)
			{
				ImGui::Separator();
				if (ImGui::Button("Add Component"))
					addComp = !addComp;

				if (addComp)
				{
					if (ImGui::Button("Transform"))
					{
						activeObject->AddComponent(Component::Type::TRANSFORM);
						addComp = false;
					}
					if (ImGui::Button("Mesh"))
					{
						activeObject->AddComponent(Component::Type::MESH);
						addComp = false;
					}
					if (ImGui::Button("Material"))
					{
						activeObject->AddComponent(Component::Type::MATERIAL);
						addComp = false;
					}
					if (ImGui::Button("Skeleton"))
					{
						activeObject->AddComponent(Component::Type::SKELETON);
						addComp = false;
					}
					if (ImGui::Button("Animation"))
					{
						activeObject->AddComponent(Component::Type::ANIMATION);
						addComp = false;
					}
					/*if (ImGui::Button("Camera"))
					{
						activeObject->AddComponent(Component::Type::CAMERA);
						addComp = false;
					}*/
				}
			}

		}

		ImGui::End();
	}
}