#pragma once

#include "Lanna/GameObject/Component.h"


class MaterialComponent : public Component
{
public:
	MaterialComponent();
	~MaterialComponent();

	void Use() override;
	void ImGuiDraw() override;

};