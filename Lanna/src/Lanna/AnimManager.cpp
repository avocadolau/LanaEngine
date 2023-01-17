#include <lnpch.h>
#include "Render3D.h"
#include "lnpch.h"

#include "Application.h"
#include "AnimManager.h"

namespace Lanna {
	AnimManager::AnimManager()
	{
	}
	AnimManager::~AnimManager()
	{
	}
	void AnimManager::Init()
	{
		//LN_RESOURCES.Import<Animation>("resources/animations/test.FBX");
		LN_RESOURCES.Import<Skeleton>("resources/animations/test.fbx");
		boneMesh = new Mesh();
		boneMesh->LoadFromFile("resources/models/Primitives/small_cube.fbx");

		LN_RESOURCES.Import<StateMachine>("resources/animations/test.fbx");
	}
	void AnimManager::Update()
	{
		LN_RESOURCES.GetResourceById<StateMachine>(0)->Update();
	}
	void AnimManager::Render()
	{
		LN_RESOURCES.GetResourceById<Skeleton>(0)->RenderBones();
	}
}


