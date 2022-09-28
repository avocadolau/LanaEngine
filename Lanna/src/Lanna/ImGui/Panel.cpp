#include "lnpch.h"
#include "Panel.h"

namespace Lanna
{
	Panel::Panel()
	{
		active = true;
	}

	Panel::~Panel()
	{

	}

	void Panel::Switch()
	{
		active = !active;
	}

}
