#include "lnpch.h"
#include "AnimationPanel.h"

#include "imgui.h"


namespace Lanna
{
	AnimPanel::AnimPanel(): Panel("Animation")
	{

	}

	AnimPanel::~AnimPanel()
	{
	}

	void AnimPanel::Draw()
	{
		ImGui::Begin(name, &active);






		ImGui::End();
	}

}