#pragma once
#include "Panel.h"
#include "lnpch.h"
#include "Lanna/Resources/Texture.h"

namespace Lanna {
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
		void ImportFBX(const std::filesystem::path& path);

		void OnScenePlay();
		void OnSceneStop();

		// UI Panels
		void UI_Toolbar();

	private:
		std::vector<ShadingView*> m_Shadings;

		enum class SceneState
		{
			Edit = 0, Play = 1
	    };

		SceneState m_SceneState = SceneState::Edit;

		Texture* m_IconPlay;
		Texture* m_IconStop;

#ifdef CAMERA
		const Camera* m_Camera;

#endif // CAMERA

	};

}