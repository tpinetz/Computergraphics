#ifndef DynamicObject_H
#define DynamicObject_H



#include <sstream>
using namespace std;

#include "MainHeaders.h"
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <SOIL\src\SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>


/**
* Class Vertex.
* A class that defines a vertex.
*
*/
class Vert
{
public:
	glm::vec4 WorldCoord;
	glm::vec3 NormalCoord;
	glm::vec2 TextureCoord;
};

/* Vector */
typedef float vec3_t[3];

/* MD2 header */
class md2_header_t
{
public:
	int ident;
	int version;

	int skinwidth;
	int skinheight;

	int framesize;

	int num_skins;
	int num_vertices;
	int num_st;
	int num_tris;
	int num_glcmds;
	int num_frames;

	int offset_skins;
	int offset_st;
	int offset_tris;
	int offset_frames;
	int offset_glcmds;
	int offset_end;
};

/* Texture name */
class md2_skin_t
{
public:
	char name[64];
};

/* Texture coords */
class md2_texCoord_t
{
public:
	short s;
	short t;
};

/* Triangle info */
class md2_triangle_t
{
public:
	unsigned short vertex[3];
	unsigned short st[3];
};

/* Compressed vertex */
class md2_vertex_t
{
public:
	unsigned char v[3];
	unsigned char normalIndex;
};

/* Model frame */
class md2_frame_t
{
public:
	vec3_t scale;
	vec3_t translate;
	char name[16];
	std::vector<md2_vertex_t> verts;
};

/* GL command packet */
class md2_glcmd_t
{
public:
	float s;
	float t;
	int index;
};

/* MD2 model structure */
class md2_model_t
{
public:
	md2_header_t header;
	std::vector<md2_skin_t> skins;
	std::vector<md2_texCoord_t> texcoords;
	std::vector<md2_triangle_t> triangles;
	std::vector<md2_frame_t> frames;
	std::vector<int> glcmds;
	GLuint tex_id;
};


/**
* Class DynamicObject.
* A Class to track the GPU time from different part of the program
* Also includes a log to print all the times
*
*/
class DynamicModelLoader
{
	//Functions

public:
	///Default constructor
	DynamicModelLoader(){};

	///Default destructor
	~DynamicModelLoader();

	///Load an MD2 model from file.
	void LoadModel(const char *filename, const glm::mat4 &TransformationMatrix);

	///Render MD2 using Vertex Buffer Object
	void Draw(GLuint shader);

	void DrawShadow(GLuint shader); 

	///Update Vertex Buffer Object
	void UpdateVAO(int frame1, int frame2, float interpol);

private:
	///Method to Load texture
	void LoadTexture(md2_model_t * m_Object);

	///Initialize Vertex Buffer Object
	void InitVAO();

	///Transform the model
	void Transform(md2_model_t * m_Object, const glm::mat4 &TransformationMatrix);

	//Variables

public:
	std::vector<Vert> m_vVertex;
	std::string m_sFile;
	GLuint m_iVao, m_Vbo;
	GLuint m_textureId;
	std::vector<std::vector<Vert>> m_finalObject;
};


#endif //DynamicObject_H