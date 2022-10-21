#pragma once
#include "Lanna/GameObject/Component.h"

class CameraComponent : public Component
{

public:

	
public:
	CameraComponent();
	~CameraComponent();

	void Use() override;
	void ImGuiDraw() override;

};