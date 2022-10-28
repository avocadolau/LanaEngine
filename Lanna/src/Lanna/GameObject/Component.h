#pragma once


class Component
{
public:
	enum Type {
		TRANSFORM,
		MESH,
		MATERIAL,
		CAMERA,


		TOTAL
	};


	Type m_Type;

public:
	Component(Type type);

	~Component();

	virtual void Use() = 0;
	virtual void ImGuiDraw() = 0;
	virtual void Render() {};
};