#include "Panel.h"
#include "Lanna/Resources/Skeleton.h"

namespace Lanna {
	class AnimPanel :public Panel
	{
	public:
		AnimPanel();
		~AnimPanel();

		void Draw() override;
		void SetActiveBone(Bone* b);
	private:
		Skeleton* skl = nullptr;
		Bone* bone = nullptr;
	};
}