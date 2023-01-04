#include "lnpch.h"

struct aiMesh;
struct aiAnimation;
struct aiNodeAnim;

typedef char sbyte;
void Test();

namespace Lanna {

	void ImportAnimationFromFile(const char* file);

	void ImportAnimation(aiAnimation* ani);
	void ImportChannel(aiNodeAnim* channel);
}