#pragma once


class Component
{
public:
	enum Type {
		NONE,
		TRANSFORM,
		MESH,
		MATERIAL
		
	};


	Type m_Type;

public:
	Component(Type type) : m_Type(type) {}

	~Component() {}

	virtual void Use() = 0;
	virtual void ImGuiDraw() = 0;
};