#include "Lanna/ImGui/Panel.h"
#include "imgui.h"

namespace Lanna
{
	class Configuration : public Panel
	{
	public:
		void Draw() override
		{
			if (active)
			{
				ImGui::Begin("Configuration");
				ImGui::Text("Pitos");
				ImGui::End();
			}
		}
	};
}