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
	}
	void AnimManager::Update()
	{
	}
	void AnimManager::Render()
	{
		LN_RESOURCES.GetResourceById<Skeleton>(0)->RenderBones();
	}
}


