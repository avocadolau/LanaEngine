#include "lnpch.h"

#include "imgui.h"
#include "Panel.h"
#include "AboutPanel.h"

AboutPanel::AboutPanel() :Panel("About")
{

}

AboutPanel::~AboutPanel()
{
}

void AboutPanel::Draw()
{
	ImGui::Begin(name, &active);

	ImGui::Text("put all the boring stuff T_T");

	ImGui::End();
}
