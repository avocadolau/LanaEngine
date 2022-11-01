#pragma once

#include "Panel.h"

namespace Lanna {
	class AboutPanel :public Panel
	{
	public:
		AboutPanel();
		~AboutPanel();

		void Draw() override;
	};
}