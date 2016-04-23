#ifndef OBJLOADER_H
#define OBJLOADER_H
#include "Mesh.h"
#include "MainHeaders.h"
#include <direct.h>

std::vector<Vertex> loadOBJ(const char * path);



bool loadAssImp(
	const char * path,
	std::vector<unsigned short> & indices,
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals
	);

#endif