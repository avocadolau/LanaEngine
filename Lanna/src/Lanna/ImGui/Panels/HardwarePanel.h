#pragma once
#include "Panel.h"

namespace Lanna {
	class HardwarePanel : public Panel
	{
	public:
		HardwarePanel();
		~HardwarePanel();

		void Draw() override;
	};

}