#include "lnpch.h"

#include "imgui.h"

#include "Panel.h"
#include "HardwarePanel.h"

HardwarePanel::HardwarePanel(): Panel("Hardware")
{
}

HardwarePanel::~HardwarePanel()
{
}

void HardwarePanel::Draw()
{
	ImGui::Begin("Hardware", &active);

	ImGui::Text("aqui va el textito pereza del hardware");

	ImGui::End();
}
