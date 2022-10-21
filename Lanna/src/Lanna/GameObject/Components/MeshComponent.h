
#pragma once

#include "Lanna/GameObject/Component.h"

class MeshComponent: public Component
{
public:
	MeshComponent();
	~MeshComponent();

	void ImGuiDraw() override;

};