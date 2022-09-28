#pragma once


namespace Lanna
{
	class Panel
	{
	public:
		Panel();
		~Panel();

		virtual void Draw() = 0;
		void Switch();

	public:
		bool active;
		
	};
}


