#pragma once
#include "Panel.h"
#include "lnpch.h"

struct ShadingView
{
	const char* name;
	bool active = false;

	ShadingView() = default;

	ShadingView(const char* Name, bool Active)
		: name(Name), active(Active) {}
};

class ScenePanel : public Panel
{
public:
	ScenePanel();
	~ScenePanel();

	void Draw() override;
	void DrawElements();
private:
	std::vector<ShadingView*> m_Shadings;
#ifdef CAMERA
	const Camera* m_Camera;

#endif // CAMERA

};

