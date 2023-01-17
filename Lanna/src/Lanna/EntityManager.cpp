#include "lnpch.h"
#include "EntityManager.h"

#include "GameObject/GameObject.h"
#include "GameObject/Components/TransformComponent.h"
#include "GameObject/Components/MeshComponent.h"

#include <vector>

namespace Lanna {

	EntityManager::EntityManager()
	{

	}

	EntityManager::~EntityManager()
	{
		m_Entities.clear();
	}

	void EntityManager::Init()
	{
		/*AddEmptyGameObject("uwu");
		GameObject* house = AddEmptyGameObject("House");
		MeshComponent* houseMesh = new MeshComponent("resources/models/BakerHouse.fbx");
		MaterialComponent* houseMat = new MaterialComponent("resources/images/bakerHouse.png");
		house->m_Transform->m_Position = glm::vec3(0.0, 0.0, 1.0f);
		house->m_Mesh = houseMesh;
		house->m_Material = houseMat;
		house->m_Components.push_back(houseMesh);
		house->m_Components.push_back(houseMat);*/

		AddEmptyGameObject("uwu");
		GameObject* street = AddEmptyGameObject("Street");
		MeshComponent* streetMesh = new MeshComponent("resources/models/Street environment_V01.FBX");
		MaterialComponent* streetMat = new MaterialComponent("resources/images/Building_V02_C.png");
		street->m_Transform->m_Position = glm::vec3(0.0, 0.0, 1.0f);
		street->m_Mesh = streetMesh;
		street->m_Material = streetMat;
		street->m_Components.push_back(streetMesh);
		street->m_Components.push_back(streetMat);

		GameObject* test = AddEmptyGameObject("test");
		MeshComponent* testMesh = new MeshComponent("resources/animations/test.fbx");
		test->m_Mesh = testMesh;
		test->m_Components.push_back(testMesh);
		test->m_Skeleton = new SkeletonComponent();
		test->m_Skeleton->m_SkeletonID = 0;
		test->m_Anim = new AnimationComponent();
		test->m_Anim->m_AnimationID = 0;
		test->m_Components.push_back(test->m_Skeleton);
		test->m_Components.push_back(test->m_Anim);
	}

	void EntityManager::Update()
	{
		for (GameObject* object : m_Entities)
			if (object->active) object->Update();
	}

	void EntityManager::Render()
	{
		for (GameObject* object : m_Entities)
			if (object->active) object->Render();
	}

	void EntityManager::AddGameObject(GameObject* gameObject)
	{
		if (gameObject)
			m_Entities.push_back(gameObject);
	}

	GameObject* EntityManager::AddEmptyGameObject(const char* name)
	{
		std::string nName = name;
		int count = 0;
		for (GameObject* object : m_Entities)
		{
			std::string nObj = object->m_Name;
			if (nObj.find(name) != -1)
				count++;
		}
		GameObject* object;
		if (count > 0)
		{
			nName.append(" ");
			nName.append(std::to_string(count + 1).c_str());
			object = new GameObject(nName.c_str());

		}
		else
			object = new GameObject(name);

		m_Entities.push_back(object);
		return object;
	}

	void EntityManager::DeleteGameObject(GameObject* entity)
	{

		int pos = 0;
		for (GameObject* o : m_Entities)
		{
			if (o == entity)
			{
				m_Entities.at(pos) = nullptr;
				auto it = std::find(m_Entities.begin(), m_Entities.end(), nullptr);
				m_Entities.erase(it);
				o->m_Parent = nullptr;
				break;
			}
			else
			{
				pos++;
			}
		}
	}

	void EntityManager::DestroyGameObject(GameObject* gameObject)
	{
		if (gameObject->canDelete)
		{
			auto it = std::find(m_Entities.begin(), m_Entities.end(), gameObject);
			if (it != m_Entities.end())
			{
				m_Entities.erase(it); //Layer isnt deleted, just removed from the actual vector
				delete gameObject;
				gameObject = nullptr;
			}
		}
		else
		{
			std::string message = "Game object '" + gameObject->m_Name+"' cant be deleted";
			LN_WARN(message.c_str());
		}
	}

	void EntityManager::SetActiveEntity(std::vector<uint64_t>* selection)
	{
		if (selection->at(0) == -1)
			activeEntitiy = nullptr;
		else
		{

			activeEntitiy = m_Entities.at(selection->at(0));

			for (int i = 1; i <= root; i++)
			{
				if (selection->at(i) != -1)
					activeEntitiy = activeEntitiy->m_Children.at(selection->at(i));
				else break;
			}
		}
		activeFromSelection = true;
	}

	void EntityManager::SetActiveEntity(GameObject* enitity)
	{
		
		activeFromSelection = false;
		activeEntitiy = enitity;
	}

	bool EntityManager::FindEntity(GameObject* entity, int count)
	{
		for (int i = 0; i < entity->m_Children.size(); i++)
		{
			if (entity->m_Children.at(i) == entity)
			{
				selected[0] = i;
				root = count;
				for (int i = root; i < selected.size(); i++)
				{
					selected[i] = -1;
				}
				return true;
			}
			else
			{
				if (FindEntity(entity->m_Children.at(i), count + 1))
				{
					break;
				}
			}
		}
		return false;
	}

}