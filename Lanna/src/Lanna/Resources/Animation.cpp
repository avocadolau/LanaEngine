#include "lnpch.h"
#include "Animation.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cfileio.h>

#include "Lanna/Application.h"
#include "Skeleton.h"

#include "imgui.h"
#include "Lanna/Utilities/Maths/Math.h"

namespace Lanna {
	AniChannel::AniChannel(aiNodeAnim* channel)
	{
		name = channel->mNodeName.C_Str();

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
	
	void Animation::Import(aiAnimation* ani, aiNode* node, AniChannel* channel)
	{
		AniChannel* nChannel = nullptr;
		for (int i = 0; i < ani->mNumChannels; i++)
		{
			if (node->mName == ani->mChannels[i]->mNodeName)
			{
				nChannel = new AniChannel(ani->mChannels[i]);
				if (channel)
					channel->children.push_back(nChannel);
				else
					m_Channels.push_back(nChannel);
				
				break;
			}
		}
		for (int i = 0; i < node->mNumChildren; i++)
		{
			if (nChannel)
				Import(ani, node->mChildren[i], nChannel);
			else
				Import(ani, node->mChildren[i], channel);
		}
	}

	StateMachine::StateMachine()
	{
		
	}

	StateMachine::~StateMachine()
	{

	}

	void StateMachine::Import(const char* file)
	{
		//const aiScene* scene = aiImportFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);
		const aiScene* scene = aiImportFile(file, aiProcessPreset_TargetRealtime_Fast);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			LN_ERROR("Couldn't load animation file: {0}", file);
		}
		LN_CORE_INFO("Loading animation file at: {0} ...", file);

		if (scene != nullptr)
		{
			if (scene->HasAnimations())
			{
				for (size_t i = 0; i < scene->mNumAnimations; i++)
				{
					Animation* nAni = new Animation();
					nAni->name = scene->mAnimations[i]->mName.C_Str();
					nAni->duration = scene->mAnimations[i]->mDuration;
					nAni->tickrate = scene->mAnimations[i]->mTicksPerSecond;
					nAni->Import(scene->mAnimations[i], scene->mRootNode, nullptr);
					anims.push_back(nAni);
					//-------------------------
				}
			}
			else LN_CORE_INFO("Couldn't find the animation at: {0}", file);
			aiReleaseImport(scene);
		}
		else {
			LN_CORE_INFO("Error loading mesh {0} with error {1}", file, aiGetErrorString());
		}
		StateMachine* example = this;
		const char* uwu;
	}

	bool StateMachine::LinkSkeleton(Skeleton* skl)
	{
		for (int i = 0; i < skl->bones.size(); i++)
		{
			for (Animation* ani : anims)
			{
				for (AniChannel* channel : ani->m_Channels)
				{
					ani->LinkBone(channel, skl);
					for (Bone* b : skl->bones)
					{
						if (b->name == channel->name)
						{
							channel->m_Bone = b;
							break;
						}
					}
					for (AniChannel* child : channel->children)
					{
						ani->LinkBone(child, skl);
					}
				}
			}
		}
		linked = true;
		return true;
	}
	void Animation::LinkBone(AniChannel* channel, Skeleton* skl)
	{
		static int color = 0;
		for (Bone* b : skl->bones)
		{
			if (b->name == channel->name)
			{
				channel->m_Bone = b;
				color++;
				break;
			}
		}
		for (AniChannel* child : channel->children)
		{
			LinkBone(child, skl);
		}
	}

	AniChannel* Animation::ImGuiHierarchyDraw(AniChannel* channel)
	{
		AniChannel* ret = nullptr;
		if (ImGui::TreeNode(name.c_str()))
		{
			if (ImGui::IsItemToggledOpen())
			{
				ret = channel;
			}
			for (AniChannel* ani : m_Channels)
			{
				AniChannel* nRet = ImGuiHierarchyDraw(ani);
				if (nRet) ret = nRet;
			}
			ImGui::TreePop();
		}
		return ret;
	}

	


	
	void Animation::Update()
	{
		lastFrame = currFrame;
		float time = Lanna::Application::Get().GetTime().GetTime();
		currFrame = (int)(time*tickrate);
		if (currFrame != lastFrame)
		{
			lastFrame = currFrame;
			

			/*if (currFrame < duration)
			{
				for (AniChannel* channel : m_Channels)
					channel->Reset();
				for (AniChannel* channel : m_Channels)
					channel->SetFromKeys(glm::mat4(1.0f), glm::vec3(1.0f), (int)currFrame % (int)duration);
			}*/

			for (AniChannel* channel : m_Channels)
				channel->Reset();
			for (AniChannel* channel : m_Channels)
				channel->SetFromKeys(glm::mat4(1.0f), glm::vec3(1.0f), (int)currFrame % (int)duration);

			// follow parent
			//MoveBones();
			// move bones T_T
		}
	}

	void StateMachine::Update()
	{
		// only the current and the secondary
		if (linked)anims[0]->Update();
	}

	void Animation::MoveBones()
	{
		for (AniChannel* channel : m_Channels)
			if (channel!=NULL)
				channel->MoveBone(glm::mat4(1.0f), glm::vec3(0.0f), glm::vec3(1.0f), currFrame%(int)duration);
	}

	void AniChannel::GetKeys(glm::vec3*pos, glm::vec3*scale, glm::vec4*rot, unsigned int frame)
	{
		// position
		if (positionKeys[0]->time >= frame)
			*pos = positionKeys[0]->value;
		else if (positionKeys[positionKeys.size() - 1]->time <= frame)
			*pos = positionKeys[positionKeys.size() - 1]->value;
		else for (int i = 0; i < positionKeys.size() - 1; i++)
		{
			int start = positionKeys[i]->time;
			int end = positionKeys[i + 1]->time;
			if (start == frame)
			{
				*pos = positionKeys[i]->value;
				break;
			}
			else if (end == frame)
			{
				*pos = positionKeys[i + 1]->value;
				break;
			}
			else if (frame > start && frame < end)
			{
				float scalar = (frame - start) / (end - start);
				*pos = scalar * (positionKeys[i + 1]->value - positionKeys[i]->value);
				break;
			}

		}

		// scale
		if (scaleKeys[0]->time >= frame)
			*scale = scaleKeys[0]->value;
		else if (scaleKeys[scaleKeys.size() - 1]->time <= frame)
			*scale = scaleKeys[scaleKeys.size() - 1]->value;
		else for (int i = 0; i < scaleKeys.size() - 1; i++)
		{
			int start = scaleKeys[i]->time;
			int end = scaleKeys[i + 1]->time;
			if (start == frame)
			{
				*scale = scaleKeys[i]->value;
				break;
			}
			else if (end == frame)
			{
				*scale = scaleKeys[i + 1]->value;
				break;
			}
			else if (frame > start && frame < end)
			{
				float scalar = (frame - start) / (end - start);
				*scale = scalar * (scaleKeys[i + 1]->value - scaleKeys[i]->value);
				break;
			}

		}

		// quat
		if (rotationKeys[0]->time >= frame)
			*rot = rotationKeys[0]->value;
		else if (rotationKeys[rotationKeys.size() - 1]->time <= frame)
			*rot = rotationKeys[rotationKeys.size() - 1]->value;
		else for (int i = 0; i < rotationKeys.size() - 1; i++)
		{
			int start = rotationKeys[i]->time;
			int end = rotationKeys[i + 1]->time;
			if (start == frame)
			{
				*rot = rotationKeys[i]->value;
				break;
			}
			else if (end == frame)
			{
				*rot = rotationKeys[i + 1]->value;
				break;
			}
			else if (frame > start && frame < end)
			{
				glm::vec4 startq, endq;
				startq = rotationKeys[i]->value;
				endq = rotationKeys[i + 1]->value;
				float scalar = (frame - start) / (end - start);
				startq.x = cos(acos(startq.x) * 2 * (1-scalar));
				endq.x = cos(acos(endq.x) * 2 * scalar);
				*rot = startq*endq;
				break;
			}

		}
	}

	// only affect the prent bone traansformations to all the children
	void AniChannel::MoveBone(glm::mat4 prevView, glm::vec3 totalRotations, glm::vec3 prevScale, unsigned int frame)
	{
		if (m_Bone!=nullptr)
		{

			//frame = 0;
			glm::vec3 poskey;
			glm::vec3 sclkey;
			glm::vec4 quatkey;
			GetKeys(&poskey, &sclkey, &quatkey, frame);

			// position in world view
			glm::vec4 nPos = glm::vec4(0.0f);
			nPos = glm::vec4(m_Bone->wpos.x, m_Bone->wpos.y, m_Bone->wpos.z, 1.0f);

			
			glm::mat4 accumulated = prevView * Math::TranslationMatrix(poskey * prevScale) * glm::inverse(prevView);
			
			// translated world point
			nPos = nPos * accumulated;

			//m_Bone->wpos = glm::vec3(nPos.x, nPos.y, nPos.z);
			m_Bone->wpos = glm::vec3(nPos.x, nPos.y, nPos.z);
			m_Bone->wrot = m_Bone->rot + totalRotations + Math::QuaternionToEulerAngles(quatkey);
			m_Bone->wscl = m_Bone->scl * prevScale * sclkey;


			glm::mat4 localRotation = Math::TranslationMatrix(quatkey, glm::vec3(0.0f));
			glm::mat4 currView = accumulated * localRotation;


			for (AniChannel* child : children)
			{
				child->FollowParent(this, accumulated);
			}

			//working with local point of view
			for (VertexWeights* weight : m_Bone->weights)
			{
				// move vertices depending on influences
				// accumulated* localRotation* weight
			}


			
			for (AniChannel* child : children)
			{
				child->MoveBone(currView, m_Bone->wrot, m_Bone->wscl, frame);
			}
		}
		

	}

	void AniChannel::SetFromKeys(glm::mat4 prevView, glm::vec3 prevRot,unsigned int frame)
	{
		// doesnt work T_T
		/*for (AniChannel* channel : children)
		{
			channel->m_Bone->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
			channel->SetFromKeys(m_Bone->m_OffsetMat, m_Bone->wrot, frame);
		}*/

		//frame = 0;
		glm::vec3 poskey;
		glm::vec3 sclkey;
		glm::vec4 quatkey;
		glm::vec3 rotkey;
		GetKeys(&poskey, &sclkey, &quatkey, frame);
		glm::vec3 rot = Math::QuaternionToEulerAngles(quatkey);
		m_Bone->wrot = m_Bone->wrot+Math::QuaternionToEulerAngles(quatkey);
		m_Bone->wscl *= sclkey;

		glm::mat4 transformation = prevView *Math::TranslationMatrix(poskey) * Math::InverseTranslation(prevView);


		glm::vec4 nvec = glm::vec4(m_Bone->wpos.x, m_Bone->wpos.y, m_Bone->wpos.z, 1.0f);// *transformation;
		nvec = nvec * prevView * transformation;
		m_Bone->wpos = glm::vec3(nvec.x, nvec.y, nvec.z);
		
		/*if (m_Bone->v_data)
		{
			for (VertexWeights* w : m_Bone->weights)
			{
				std::vector<float> *data = m_Bone->v_data;
				if (w->vID * 8 > data->size())
				{

				}
				else
				{
					glm::vec4 nVertex = glm::vec4(data->at(w->vID * 8 + 0), data->at(w->vID * 8 + 1), data->at(w->vID * 8 + 2), 1.0f);
					nVertex = nVertex * (w->weight * transformation);
					data->at(w->vID * 8 + 0) = nVertex.x;
					data->at(w->vID * 8 + 1) = nVertex.y;
					data->at(w->vID * 8 + 2) = nVertex.z;
				}
				
			}
		}*/
		

		//transformation = mOffset * Math::TranslationMatrix(quatkey, poskey) * glm::inverse(mOffset);
		for (AniChannel* child : children)
			child->FollowParent(prevView,poskey, quatkey,sclkey);

	}

	void AniChannel::SetFromKeys(glm::mat4 transformation, glm::mat4 prevoffsetmat, unsigned int frame)
	{
		//frame = 0;
		glm::vec3 poskey;
		glm::vec3 sclkey;
		glm::vec4 quatkey;
		GetKeys(&poskey, &sclkey, &quatkey, frame);
		glm::vec3 rot = Math::QuaternionToEulerAngles(quatkey);
		m_Bone->wrot = m_Bone->wrot + Math::QuaternionToEulerAngles(quatkey);
		m_Bone->wscl *= sclkey;

		glm::vec4 nvec = glm::vec4(m_Bone->wpos.x, m_Bone->wpos.y, m_Bone->wpos.z, 1.0f);
		glm::mat4 localtransform = prevoffsetmat * Math::TranslationMatrix(poskey) * Math::InverseTranslation(prevoffsetmat) * transformation;
		nvec = nvec*localtransform;
		m_Bone->wpos = glm::vec3(nvec.x, nvec.y, nvec.z);

		glm::mat4 childtransform = prevoffsetmat * Math::TranslationMatrix(poskey)* Math::TranslationMatrix(quatkey,glm::vec3(0.0f)) * Math::InverseTranslation(prevoffsetmat) * transformation;

		for (AniChannel* channel : children)
		{
			channel->m_Bone->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
			channel->SetFromKeys(childtransform,m_Bone->m_OffsetMat, frame);
		}
	}

	void AniChannel::FollowParent(glm::mat4 offsetmat, glm::vec3 translate, glm::vec4 rotate, glm::vec3 scale)
	{
		glm::vec4 mPos = glm::vec4(m_Bone->wpos.x, m_Bone->wpos.y, m_Bone->wpos.z, 1.0f);
		
		// parent view
		//mPos = mPos * offsetmat * Math::TranslationMatrix(translate*scale);
		mPos = mPos * offsetmat * Math::TranslationMatrix(rotate, translate) * Math::InverseTranslation(offsetmat);

		//mPos = mPos * Math::TranslationMatrix(rotate, glm::vec3(mPos.x * scale.x, mPos.y * scale.y, mPos.z * scale.z)) * glm::inverse(offsetmat);
		m_Bone->wpos = glm::vec3(mPos.x,mPos.y,mPos.z);
		m_Bone->wrot = m_Bone->wrot + Math::QuaternionToEulerAngles(rotate);
		m_Bone->wscl *= scale;

		for (AniChannel* channel : children)
			channel->FollowParent(offsetmat,translate,rotate,scale);
	}

	void AniChannel::FollowParent(AniChannel* parent, glm::mat4 translations)
	{
		glm::vec4 nPos = glm::vec4(m_Bone->pos.x, m_Bone->pos.y, m_Bone->pos.z, 1.0f);
		nPos = nPos * translations;
		for (AniChannel* child : children)
		{
			child->FollowParent(this, translations);
		}
	}

	void AniChannel::Reset()
	{
		m_Bone->wpos = m_Bone->pos;
		m_Bone->wrot = m_Bone->rot;
		m_Bone->wscl = m_Bone->scl;
		for (AniChannel* child : children)
			child->Reset();
	}
}