#pragma once


class Component
{
public:
	enum Type {
		TRANSFORM = 0,
		MESH=1,
		MATERIAL=2,
		CAMERA=3,


		TOTAL
	};


	Type m_Type;

public:
	Component(Type type);

	~Component();

	virtual void Use() = 0;
	virtual void ImGuiDraw() = 0;
};