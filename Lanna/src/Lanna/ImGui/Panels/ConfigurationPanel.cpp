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

	bool testBool = true;

	ImGui::Begin("Configuration", &active);

	if (ImGui::CollapsingHeader("Options"))
	{
		ImGui::Checkbox("vsync", &testBool);
	}

	
	if (ImGui::CollapsingHeader("Info"))
	{
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

	ImGui::End();
}
