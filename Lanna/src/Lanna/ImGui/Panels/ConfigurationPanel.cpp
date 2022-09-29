#include "lnpch.h"

#include "imgui.h"
#include <list>

#include "Panel.h"
#include "ConfigurationPanel.h"

#include "Lanna/Application.h"

ConfigurationPanel::ConfigurationPanel():Panel("Configuration")
{
}

ConfigurationPanel::~ConfigurationPanel()
{
}

void ConfigurationPanel::Draw()
{
	msLog.push_back(1000.0f / ImGui::GetIO().Framerate);
	fpsLog.push_back(ImGui::GetIO().Framerate);
	
	if (msLog.size() > MAX)
		msLog.erase(msLog.begin());
	if (fpsLog.size() > MAX)
		fpsLog.erase(fpsLog.begin());

	ImGui::Begin("Configuration", &active);

	if (ImGui::CollapsingHeader("Window"))
	{
		int val = 1;
		ImGui::SliderInt("Brightness", &val, 0, 100, "%i");
		ImGui::SliderInt("Width", &val, 0, 100, "%i");
		ImGui::SliderInt("Height", &val, 0, 100, "%i");

		if (ImGui::Checkbox("Fullscreen", &fullscreen))
		{

		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Resizable", &resizable))
		{

		}
	}

	if (ImGui::CollapsingHeader("Render"))
	{
		ImGui::Checkbox("vsync", &vsync);

		if (ImGui::BeginTable("Frame info", 2))
		{
			char title[25];
			ImGui::TableNextColumn();
			sprintf_s(title, 25, "Framerate %.1f", fpsLog[fpsLog.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fpsLog[0], msLog.size(), 0, title, 0.0f, 100.0f, ImVec2(200, 100));

			ImGui::TableNextColumn();
			sprintf_s(title, 25, "Frametime %.1f", msLog[msLog.size() - 1]);
			ImGui::PlotHistogram("##frametime", &msLog[0], msLog.size(), 0, title, 0.0f, 100.0f, ImVec2(200, 100));

			ImGui::EndTable();
		}
	}

	
	if (ImGui::CollapsingHeader("Sound"))
	{
		int val = 1;
		int min = 0;
		int max = 100;
		ImGui::SliderInt("volume", &val, min, max, "%i");
	}

	ImGui::End();
}
