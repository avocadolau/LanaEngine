#pragma once
#include "Panel.h"
#include "Lanna/GameObject/GameObject.h"
class InspectorPanel : public Panel
{
public:
	InspectorPanel();
	~InspectorPanel();

	void Draw() override;

private:
	void ShowObjectHierarchy(GameObject* obj);
	bool addComp = false;
};

