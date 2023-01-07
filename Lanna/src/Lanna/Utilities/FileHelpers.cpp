#include "lnpch.h"
#include "FileHelpers.h"

std::string GetDir(const char* full_path)
{
	if (full_path != nullptr)
	{
		const char* test = strrchr(full_path, '\\/');
		const char* test1 = strchr(full_path, '\\/');
		std::string aux = full_path;
		if (test == NULL)
		{
			if (test1 != NULL)
				aux = test1;
			else
			{
				int last = aux.find_last_of('\\');
				aux.erase(last + 1);
				return aux;
			}
		}
		else
			aux = test;

		std::string path = full_path;
		path.erase(path.length() - aux.length() + 1);
		return path;
	}
	return std::string("");
}

unsigned int GetExtSize(const char* file)
{
	std::string ret = strrchr(file, '.');

	return ret.length();
}

std::string GetExtension(const char* file)
{
	return strrchr(file, '.');
}

std::string GetFileName(const char* file)
{
	std::string ret = file;

	ret = ret.substr(ret.find_last_of("\\/") + 1);

	const char* test = strrchr(ret.c_str(), '.');
	if (test != NULL && test != nullptr)
	{
		std::string aux = test;
		ret.erase(ret.length() - aux.length()).c_str();
	}
	return ret;
}

int StringToInt(std::string str)
{
	int ret = 0;

	for (int i = 0, j = str.length() - 1; i < str.length(); i++, j--)
		ret += (str[i] - 48) * (std::pow(10, j));

	return ret;
}

int StringToInt(const char* str, int size)
{
	int ret = 0;

	for (int i = 0, j = size - 1; i < size; i++, j--)
		ret += (str[i] - 48) * (std::pow(10, j));

	return ret;
}

FileType CheckExtension(std::string& ext)
{
	FileType ret = LFT_Error;

	if (ext == std::string(".fbx") || ext == std::string(".FBX") || ext == std::string(".dae") || ext == std::string(".DAE"))
		ret = LFT_FBX;
	else if (ext == std::string(".png") || ext == std::string(".bmp") || ext == std::string(".jpg") || ext == std::string(".dds"))
		ret = LFT_Texture;
	else if (ext == std::string(".lnmesh"))
		ret = LFT_Mesh;
	else if (ext == std::string(".lnmat"))
		ret = LFT_Material;
	else if (ext == std::string(".lnskel"))
		ret = LFT_Skeleton;
	else if (ext == std::string(".lnanim"))
		ret = LFT_Animation;
	return ret;
}
