#pragma once
#include "lnpch.h"

namespace Lanna {
	class FileSystem
	{
	public:
		FileSystem();
		~FileSystem();

		void Init();
		bool Import();
		bool Save();
		bool Load();

	private:

		static FileSystem* s_Instance;
	};
}