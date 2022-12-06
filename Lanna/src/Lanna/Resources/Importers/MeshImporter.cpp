#include "lnpch.h"
#include "MeshImporter.h"

#include "Lanna/Application.h"
#include "Lanna/Resources/Mesh.h"
#include "Lanna/Resources.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include "Lanna/Utilities/FileHelpers.h"


void Test() {
	std::fstream file;

	// clear file
	file.open("test.uwu", std::ofstream::out | std::ofstream::trunc);
	file.close();


	file.open("test.uwu", std::fstream::in|std::fstream::out|std::fstream::app);
	int num = 1;
	file.write((const sbyte*)&num, sizeof(int));
	//file << "a la lloreria\n";
	file.close();

	//delete data;

	//--------------------------------

	int res;
	file.open("test.uwu", std::fstream::in | std::fstream::out | std::fstream::app);
	file.read((sbyte*) & res, sizeof(int));
	file.close();


}

namespace Lanna {

	

}