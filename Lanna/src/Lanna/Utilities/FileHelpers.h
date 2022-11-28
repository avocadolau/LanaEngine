#pragma once

#include "lnpch.h"

std::string GetDir(const char* full_path);

unsigned int GetExtSize(const char* file);

std::string GetExtension(const char* file);

std::string GetFileName(const char* file);

int StringToInt(std::string str);
int StringToInt(const char* str, int size);

enum FileType
{
	LFT_Error = -1,
	LFT_Texture,
	LFT_Object,
	LFT_FBX,
	LFT_Material,
	LFT_Mesh,
	LFT_Bilboad,
	LFT_Skeleton,
	LFT_Animation,

	LFT_Files_Max
};
FileType CheckExtension(std::string& ext);
