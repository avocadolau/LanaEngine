#include "lnpch.h"
#include "Animation.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Lanna {
	AniChannel::AniChannel(aiNodeAnim* channel)
	{
		node_name = channel->mNodeName.C_Str();

		for (unsigned int i = 0; i < channel->mNumPositionKeys; i++)
		{
			positionKeys.push_back(new VectorKey(channel->mPositionKeys[i].mTime,
				channel->mPositionKeys[i].mValue.x, channel->mPositionKeys[i].mValue.y, channel->mPositionKeys[i].mValue.z));
		}
		for (unsigned int i = 0; i < channel->mNumScalingKeys; i++)
		{
			scaleKeys.push_back(new VectorKey(channel->mScalingKeys[i].mTime,
				channel->mScalingKeys[i].mValue.x, channel->mScalingKeys[i].mValue.y, channel->mScalingKeys[i].mValue.z));
			
		}
		for (unsigned int i = 0; i < channel->mNumRotationKeys; i++)
		{
			rotationKeys.push_back(new QuatKey(channel->mRotationKeys[i].mTime,
				channel->mRotationKeys[i].mValue.x, channel->mRotationKeys[i].mValue.y, channel->mRotationKeys[i].mValue.z, channel->mRotationKeys[i].mValue.w));
		}
	}
	
	void MetaAnimation::Import(aiAnimation* ani)
	{
		name = ani->mName.C_Str();
		duration = ani->mDuration;
		tickrate = ani->mTicksPerSecond;
		for (unsigned int i = 0; i < ani->mNumChannels; i++)
		{
			m_Channels.push_back(new AniChannel(ani->mChannels[i]));
		}
	}

	Animation::Animation()
	{

	}

	Animation::~Animation()
	{
	}

	void Animation::Import(const char* file)
	{
		const aiScene* scene = aiImportFile(file, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_PreTransformVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			LN_ERROR("Couldn't load animation file: {0}", file);
		}
		LN_CORE_INFO("Loading animation file at: {0} ...", file);

		if (scene != nullptr)
		{
			if (scene->HasAnimations() == true)
			{
				for (size_t i = 0; i < scene->mNumAnimations; i++)
				{
					MetaAnimation* nAni = new MetaAnimation();
					nAni->Import(scene->mAnimations[i]);
					anims.push_back(nAni);
				}
			}
			else LN_CORE_INFO("mamaste pinga");
			aiReleaseImport(scene);
		}
		else {
			LN_CORE_INFO("Error loading mesh {0} with error {1}", file, aiGetErrorString());
		}
	}


}