#include "lnpch.h"

#include "imgui.h"
#include "Panel.h"
#include "AboutPanel.h"

#include "Lanna/Application.h"

AboutPanel::AboutPanel() :Panel("About")
{

}

AboutPanel::~AboutPanel()
{
}

void AboutPanel::Draw()
{
	ImGui::Begin(name, &active);

	ImGui::Text("Lanna Engine v0.1");
	ImGui::Text("Cute functional game engine");
	ImGui::Text("By Laura Isidro & Anna Metrevelli");
	ImGui::Text("\n3rd Party Libraries used:");

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0, 0.0, 0.0, 0.0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0, 0.0, 0.0, 0.0));
	if (ImGui::Button("> OpenGL v3.2.1       "))
		Lanna::Application::Get().OpenUrl("https://github.com/glfw/glfw");
	if (ImGui::Button("> GLFW v3.3.8         "))
		Lanna::Application::Get().OpenUrl("https://glfw.org/");
	if (ImGui::Button("> ImGui v1.66b        "))
		Lanna::Application::Get().OpenUrl("https://github.com/ocornut/imgui");
	if (ImGui::Button("> spdlog v1.10.0      "))
		Lanna::Application::Get().OpenUrl("https://github.com/gabime/spdlog");
	if (ImGui::Button("> premake v5.0.0-beta2"))
		Lanna::Application::Get().OpenUrl("https://github.com/premake/premake-core");
	if (ImGui::Button("> MathGeoLib v1.5     "))
		Lanna::Application::Get().OpenUrl("https://github.com/juj/MathGeoLib");
	if (ImGui::Button("> Glew v2.2.0         "))
		Lanna::Application::Get().OpenUrl("https://glew.sourceforge.net");
	if (ImGui::Button("> PCG v0.98.1         "))
		Lanna::Application::Get().OpenUrl("https://github.com/imneme/pcg-cpp");
	if (ImGui::Button("> assimp v5.2.5       "))
		Lanna::Application::Get().OpenUrl("https://github.com/assimp/assimp");
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::Text("\nLicence:  MIT License");

	ImGui::TextWrapped("\nCopyright(c) 2022 Laura Isidro & Anna Metrevelli");
	ImGui::TextWrapped("\nPermission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :");
	ImGui::TextWrapped("\nThe above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.");
	ImGui::TextWrapped("\nTHE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");

	ImGui::End();
}
