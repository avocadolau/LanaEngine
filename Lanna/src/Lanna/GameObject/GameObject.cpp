
#include "lnpch.h"
#include "GameObject.h"
#include <vector>

#include "Component.h"

#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"
#include "Components/MaterialComponent.h"

GameObject::GameObject()
{

}
GameObject::~GameObject()
{
	m_Components.clear();
	m_Children.clear();
}


void GameObject::Update() {


}
void GameObject::Render() {}

void GameObject::AddComponent(Component::Type type)
{

}

