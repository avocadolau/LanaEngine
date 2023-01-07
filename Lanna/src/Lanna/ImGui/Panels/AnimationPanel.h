#include "Panel.h"
#include "Lanna/Resources/Animation.h"

namespace Lanna {
	class AnimPanel :public Panel
	{
	public:
		AnimPanel();
		~AnimPanel();

		void Draw() override;
	private:
		Animation* ani = nullptr;
	};
}