#pragma once
#include "Panel.h"
#include "Lanna/GameObject/GameObject.h"

namespace Lanna {


	class HierarchyPanel : public Panel
	{
	public:
		HierarchyPanel();
		~HierarchyPanel();

		void Draw() override;
		void PopMenu(GameObject* hover);

		std::vector<uint64_t> *selected;
		GameObject* hovered;
		bool IsSelected(uint64_t eid) { for (auto v : *selected) if (eid == v) return true; return false; }
		void UpdateEntry(GameObject* entity);

		bool EntityChildren(GameObject* entity, int root);
		GameObject* AllChildrenList(GameObject* hover, GameObject* entity);
	};
}

