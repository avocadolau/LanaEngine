#pragma once
#include "lnpch.h"

namespace Lanna {

	enum ResourceType {
		LRT_IMAGE,
		LRT_SHADER,
		LRT_MODEL,
		LRT_TEXTURE,
		LRT_ERROR
	};

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