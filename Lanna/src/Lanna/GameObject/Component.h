#pragma once

namespace Lanna
{
	class Component
	{
	public:
		enum Type {
			TRANSFORM,
			MESH,
			MATERIAL,
			CAMERA,
			SKELETON,

			TOTAL
		};


		Type m_Type;
		const char* name;
		bool toDel = false;
	public:
		Component(Type type);

		~Component();

		virtual void Use() = 0;
		virtual void ImGuiDraw() = 0;
		virtual void Render() {};
		
	};
}