#pragma once
#include "Panel.h"

namespace Lanna {
	class HierarchyPanel : public Panel
	{
	public:
		HierarchyPanel();
		~HierarchyPanel();

		void Draw() override;
	};

}