#include "lnpch.h"
#include "Panel.h"
#include <string>

namespace Lanna
{
	Panel::Panel(const char* name) : name(name)
	{}

	Panel::~Panel()
	{}

	void Panel::SetActive(bool enabled)
	{
		active = enabled;
	}

	void Panel::SwitchActive()
	{
		active = !active;
	}

	bool Panel::IsActive() const
	{
		return active;
	}

}
