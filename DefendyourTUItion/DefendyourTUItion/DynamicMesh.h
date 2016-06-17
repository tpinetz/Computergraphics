#ifndef DYNAMICMESH_H
#define DYNAMICMESH_H



//Includes
#include "MainHeaders.h"
#include <vector>
#include <iostream>


#define NumBones 4

#define BUFFER_OFFSET(i) (reinterpret_cast<void*>(i))
#define WORLD_COORD_LOCATION 0
#define NORMAL_COORD_LOCATION 1
#define TEXTURE_COORD_LOCATION 2
#define BONES_ID_LOCATION 3
#define BONES_WEIGTH_LOCATION 4


/**
* Class Vertex.
* A class that defines a vertex.
*
*/
class DynamicVertex
{
public:
	glm::vec4 WorldCoord;
	glm::vec3 NormalCoord;
	glm::vec2 TextureCoord;
	GLint BoneID[NumBones];
	GLfloat  BoneWeight[NumBones];



	//Default Constructor
	DynamicVertex() :
		WorldCoord(0.0f, 0.0f, 0.0f, 0.0f),
		NormalCoord(0.0f, 0.0f, 0.0f),
		TextureCoord(0.0f, 0.0f)
	{
		for (int i = 0; i < NumBones; ++i){
			BoneID[i] = 0;
			BoneWeight[i] = 0.0f;
		}

	}
};



/**
* Class Mesh.
* A class that defines a mesh.
*
*/
class DynamicMesh
{
public:
	std::vector<DynamicVertex> m_vVertexInfo;
	std::vector<GLuint> m_vIndex;
	GLuint m_uiVao;
	GLuint m_uiVbo;
	GLuint m_uiIndexVbo;
	GLuint m_uitextureID;
	GLboolean init;
	GLuint m_iSize;
	std::string m_textureName;


	DynamicMesh();
	~DynamicMesh();
	void setupMesh();
	void Draw(GLuint shader);
	void DrawShadow(GLuint shader);

};




#endif //Vertex_H