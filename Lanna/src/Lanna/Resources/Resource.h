#include "lnpch.h"
#include "Lanna/FileSystem.h"

namespace Lanna{

	class Asset {
	public:
		Asset();
		~Asset();
	private:
	};

	class Resource {
	public:
		Resource();
		~Resource();

		void Import(const char* file);
		void Save();
		void Load(const char* file);
	private:
		Asset* m_Asset;
		std::string filePath;
		unsigned int usingCount = 0;
		ResourceType type = LRT_ERROR;
	};
}