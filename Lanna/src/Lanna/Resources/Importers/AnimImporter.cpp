#include "lnpch.h"
#include "AnimImporter.h"

#include "Lanna/Application.h"
#include "Lanna/Resources/Mesh.h"
#include "Lanna/Resources.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include "Lanna/Utilities/FileHelpers.h"


void Test() {
	std::fstream file;

	// clear file
	file.open("test.uwu", std::ofstream::out | std::ofstream::trunc);
	file.close();


	file.open("test.uwu", std::fstream::in|std::fstream::out|std::fstream::app);
	int num = 1;
	file.write((const sbyte*)&num, sizeof(int));
	//file << "a la lloreria\n";
	file.close();

	//delete data;

	//--------------------------------

	int res;
	file.open("test.uwu", std::fstream::in | std::fstream::out | std::fstream::app);
	file.read((sbyte*) & res, sizeof(int));
	file.close();


}

namespace Lanna {

	void ImportAnimationFromFile(const char* file)
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
					ImportAnimation(scene->mAnimations[i]);
				}


			}
			else LN_CORE_INFO("mamaste pinga");
			aiReleaseImport(scene);
		}
		else {
			LN_CORE_INFO("Error loading mesh {0} with error {1}", file, aiGetErrorString());
		}
	}

	void ImportAnimation(aiAnimation* ani)
	{
		std::string m_name = ani->mName.C_Str();
		double duration = ani->mDuration;
		double tickspersec = ani->mTicksPerSecond;
		unsigned int nChannels = ani->mNumChannels;
		for (size_t i = 0; i < ani->mNumChannels; i++)
		{
			ImportChannel(ani->mChannels[i]);
		}
	}

	void ImportChannel(aiNodeAnim* channel)
	{
		std::string nodeName = channel->mNodeName.C_Str();
		// position keys
		// scaling keys
		// rotation keys

	}

	

}