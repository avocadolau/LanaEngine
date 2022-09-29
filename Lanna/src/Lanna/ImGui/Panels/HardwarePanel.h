#pragma once
#include "Panel.h"
class HardwarePanel : public Panel
{
public:
	HardwarePanel();
	~HardwarePanel();

	void Draw() override;
};

