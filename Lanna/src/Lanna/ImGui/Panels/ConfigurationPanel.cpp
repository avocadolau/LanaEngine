#include "lnpch.h"

#include "imgui.h"
#include <list>

#include "Panel.h"
#include "ConfigurationPanel.h"

#include "Lanna/Application.h"
#include <GLFW/glfw3.h>

#include "Utilities/MemoryAllocation.h"

ConfigurationPanel::ConfigurationPanel():Panel("Configuration")
{
}

ConfigurationPanel::~ConfigurationPanel()
{
}

void ConfigurationPanel::Draw()
{
	char title[25];
	msLog.push_back(1000.0f / ImGui::GetIO().Framerate);
	fpsLog.push_back(ImGui::GetIO().Framerate);
	allocLog.push_back(Lanna::MemoryAllocation::allocation_count);
	byteLog.push_back(Lanna::MemoryAllocation::bytes_allocated);
	
	if (msLog.size() > MAX)
		msLog.erase(msLog.begin());
	if (fpsLog.size() > MAX)
		fpsLog.erase(fpsLog.begin());

	ImGui::Begin("Configuration", &active);

	if (ImGui::CollapsingHeader("Window"))
	{
		int width = Lanna::Application::Get().GetWindow().GetWidth();
		int height= Lanna::Application::Get().GetWindow().GetHeight();

		if (ImGui::Checkbox("Fullscreen", &fullscreen))
		{
			Lanna::Application::Get().GetWindow().SetFullScreen(fullscreen);
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Resizable", &resizable))
		{
			Lanna::Application::Get().GetWindow().SetResizable(resizable);

		}
		ImGui::SameLine();
		if (ImGui::Checkbox("vsync", &vsync))
		{
			Lanna::Application::Get().GetWindow().SetVSync(vsync);
		}

		//ImGui::SliderInt("Brightness", &val, 0, 100, "%i");
		
		if (resizable)
		{
			if (ImGui::SliderInt("Width", &width, 400, 2000, "%i"))
				Lanna::Application::Get().GetWindow().SetWidth(width);
			if(ImGui::SliderInt("Height", &height, 600,1600, "%i"))
				Lanna::Application::Get().GetWindow().SetHeight(height);
		}
		else
		{
			sprintf_s(title, 25, "Width  : %i", width);
			ImGui::Text(title);
			sprintf_s(title, 25, "Height : %i", height);
			ImGui::Text(title);
		}
	}

	if (ImGui::CollapsingHeader("Information"))
	{
		
		if (ImGui::BeginTable("Frame info", 2))
		{
			ImGui::TableNextColumn();
			sprintf_s(title, 25, "Framerate %.1f", fpsLog[fpsLog.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fpsLog[0], msLog.size(), 0, title, 0.0f, 100.0f, ImVec2(200, 100));

			ImGui::TableNextColumn();
			sprintf_s(title, 25, "Frametime %.1f", msLog[msLog.size() - 1]);
			ImGui::PlotHistogram("##frametime", &msLog[0], msLog.size(), 0, title, 0.0f, 100.0f, ImVec2(200, 100));

			sprintf_s(title, 25, "Current Allocations %.0f", allocLog[allocLog.size() - 1]);
			ImGui::PlotHistogram("##memory", &allocLog[0], (int)allocLog.size(), 0, title, 0.0f, 100.0f, ImVec2(200, 100));

			sprintf_s(title, 25, "Bytes allocated %.0f", byteLog[byteLog.size() - 1]);
			ImGui::PlotHistogram("##memory", &byteLog[0], (int)byteLog.size(), 0, title, 0.0f, 100.0f, ImVec2(200, 100));

			ImGui::EndTable();
		}
	}

	if (ImGui::CollapsingHeader("Hardware"))
	{
		info = Lanna::Application::Get().GetSystemInfo();

		ImGui::Text("GLFW version:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", info.glfwVer);
		ImGui::Separator();
		ImGui::Text("CPUs:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", info.numCores);
		ImGui::Text("System RAM:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%0.1fMb", info.ram);
		ImGui::Separator();
		ImGui::Text("GPU:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", info.gpu);
		ImGui::Text("Brand:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", info.gpuBrand);
		ImGui::Text("Total VRAM:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%0.1fMb", info.gpuVRAM);
		ImGui::Text("VRAM Usage:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), " %0.1fMb", info.gpuVRAMUsage);
		ImGui::Text("VRAM Available:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%0.1fMb", info.gpuVRAMAV);
		ImGui::Text("VRAM Reserved:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%0.1fMb", info.gpuVRAMReserve);
	}
	
	if (ImGui::CollapsingHeader("Sound"))
	{
		ImGui::Text("WORK IN PROGRESS T_T");
		/*int val = 1;
		int min = 0;
		int max = 100;
		ImGui::SliderInt("volume", &val, min, max, "%i");*/
	}

	ImGui::End();
}
