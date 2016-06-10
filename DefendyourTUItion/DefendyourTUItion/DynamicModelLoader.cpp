#define FILE_REVISION "$Revision: $"


#include "DynamicModelLoader.h"
#include <stdio.h>
#include <iostream>
using namespace std;



/**
* Default destructor
*/
DynamicModelLoader::~DynamicModelLoader()
{
	glDeleteBuffers(1, &m_Vbo);
	glDeleteVertexArrays(1, &m_iVao);
}



/**
* Load an MD2 model from file.
*
* Note: MD2 format stores model's data in little-endian ordering.  On
* big-endian machines, you'll have to perform proper conversions.
*
* @params filename the name of the model to be loaded
* @params TransformationMatrix a Matrix with all the transformations to be made to the model
*
*/
void DynamicModelLoader::LoadModel(const char *filename, const glm::mat4 &TransformationMatrix)
{
	FILE *fp;
	int i;

	m_sFile = filename;

	fopen_s(&fp, filename, "rb");

	if (!fp)
	{
		fprintf(stderr, "Error: couldn't open \"%s\"!\n", filename);
		system("pause");
		exit(0);
	}

	md2_model_t m_Object;

	/* Read header */
	fread(&m_Object.header, 1, sizeof (md2_header_t), fp);

	if ((m_Object.header.ident != 844121161) ||
		(m_Object.header.version != 8))
	{
		/* Error! */
		fprintf(stderr, "Error: bad version or identifier\n");
		fclose(fp);
		system("pause");
		exit(0);
	}

	/* Memory allocations */
	m_Object.skins.resize(m_Object.header.num_skins);
	m_Object.texcoords.resize(m_Object.header.num_st);
	m_Object.triangles.resize(m_Object.header.num_tris);
	m_Object.frames.resize(m_Object.header.num_frames);
	m_Object.glcmds.resize(m_Object.header.num_glcmds);


	/* Read model data */
	if (m_Object.header.num_skins != 0)
	{
		fseek(fp, m_Object.header.offset_skins, SEEK_SET);
		fread(&m_Object.skins[0], sizeof (md2_skin_t),
			m_Object.header.num_skins, fp);
	}

	if (m_Object.header.num_st != 0)
	{
		fseek(fp, m_Object.header.offset_st, SEEK_SET);
		fread(&m_Object.texcoords[0], sizeof (md2_texCoord_t),
			m_Object.header.num_st, fp);
	}

	if (m_Object.header.num_tris != 0)
	{
		fseek(fp, m_Object.header.offset_tris, SEEK_SET);
		fread(&m_Object.triangles[0], sizeof (md2_triangle_t),
			m_Object.header.num_tris, fp);
	}

	if (m_Object.header.num_glcmds != 0)
	{
		fseek(fp, m_Object.header.offset_glcmds, SEEK_SET);
		fread(&m_Object.glcmds[0], sizeof (int), m_Object.header.num_glcmds, fp);
	}

	/* Read frames */
	fseek(fp, m_Object.header.offset_frames, SEEK_SET);
	for (i = 0; i < m_Object.header.num_frames; ++i)
	{
		/* Memory allocation for vertices of this frame */
		m_Object.frames[i].verts.resize(m_Object.header.num_vertices);

		/* Read frame data */
		fread(m_Object.frames[i].scale, sizeof (vec3_t), 1, fp);
		fread(m_Object.frames[i].translate, sizeof (vec3_t), 1, fp);
		fread(m_Object.frames[i].name, sizeof (char), 16, fp);
		fread(&m_Object.frames[i].verts[0], sizeof (md2_vertex_t),
			m_Object.header.num_vertices, fp);
	}

	fclose(fp);


	///////////////////End of file read/////////////////////////

	LoadTexture(&m_Object);
	Transform(&m_Object, TransformationMatrix);

	//Free the memory from the auxiliar data structure
	m_Object.skins.clear();
	m_Object.texcoords.clear();
	m_Object.triangles.clear();
	m_Object.glcmds.clear();

	for (int i = 0; i < m_Object.header.num_frames; ++i)
	{
		m_Object.frames[i].verts.clear();
	}

	m_Object.frames.clear();

	//End of freeing memory


	InitVAO();
}

/**
* Transform the model to a new data estructure
*
* @params m_vObject a pointer to the old data structure
* @params TransformationMatrix a Matrix to transform every vertex in the model
*
*/
void DynamicModelLoader::Transform(md2_model_t * m_Object, const glm::mat4 &TransformationMatrix)
{
	//Precalculated normals
	GLuint cc = 0;
	glm::vec3 * m_pNormals = new glm::vec3[162];

	m_pNormals[cc++] = glm::vec3(-0.525731f, 0.000000f, 0.850651f);
	m_pNormals[cc++] = glm::vec3(-0.442863f, 0.238856f, 0.864188f);
	m_pNormals[cc++] = glm::vec3(-0.295242f, 0.000000f, 0.955423f);
	m_pNormals[cc++] = glm::vec3(-0.309017f, 0.500000f, 0.809017f);
	m_pNormals[cc++] = glm::vec3(-0.162460f, 0.262866f, 0.951056f);
	m_pNormals[cc++] = glm::vec3(0.000000f, 0.000000f, 1.000000f);
	m_pNormals[cc++] = glm::vec3(0.000000f, 0.850651f, 0.525731f);
	m_pNormals[cc++] = glm::vec3(-0.147621f, 0.716567f, 0.681718f);
	m_pNormals[cc++] = glm::vec3(0.147621f, 0.716567f, 0.681718f);
	m_pNormals[cc++] = glm::vec3(0.000000f, 0.525731f, 0.850651f);
	m_pNormals[cc++] = glm::vec3(0.309017f, 0.500000f, 0.809017f);
	m_pNormals[cc++] = glm::vec3(0.525731f, 0.000000f, 0.850651f);
	m_pNormals[cc++] = glm::vec3(0.295242f, 0.000000f, 0.955423f);
	m_pNormals[cc++] = glm::vec3(0.442863f, 0.238856f, 0.864188f);
	m_pNormals[cc++] = glm::vec3(0.162460f, 0.262866f, 0.951056f);
	m_pNormals[cc++] = glm::vec3(-0.681718f, 0.147621f, 0.716567f);
	m_pNormals[cc++] = glm::vec3(-0.809017f, 0.309017f, 0.500000f);
	m_pNormals[cc++] = glm::vec3(-0.587785f, 0.425325f, 0.688191f);
	m_pNormals[cc++] = glm::vec3(-0.850651f, 0.525731f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(-0.864188f, 0.442863f, 0.238856f);
	m_pNormals[cc++] = glm::vec3(-0.716567f, 0.681718f, 0.147621f);
	m_pNormals[cc++] = glm::vec3(-0.688191f, 0.587785f, 0.425325f);
	m_pNormals[cc++] = glm::vec3(-0.500000f, 0.809017f, 0.309017f);
	m_pNormals[cc++] = glm::vec3(-0.238856f, 0.864188f, 0.442863f);
	m_pNormals[cc++] = glm::vec3(-0.425325f, 0.688191f, 0.587785f);
	m_pNormals[cc++] = glm::vec3(-0.716567f, 0.681718f, -0.147621f);
	m_pNormals[cc++] = glm::vec3(-0.500000f, 0.809017f, -0.309017f);
	m_pNormals[cc++] = glm::vec3(-0.525731f, 0.850651f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(0.000000f, 0.850651f, -0.525731f);
	m_pNormals[cc++] = glm::vec3(-0.238856f, 0.864188f, -0.442863f);
	m_pNormals[cc++] = glm::vec3(0.000000f, 0.955423f, -0.295242f);
	m_pNormals[cc++] = glm::vec3(-0.262866f, 0.951056f, -0.162460f);
	m_pNormals[cc++] = glm::vec3(0.000000f, 1.000000f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(0.000000f, 0.955423f, 0.295242f);
	m_pNormals[cc++] = glm::vec3(-0.262866f, 0.951056f, 0.162460f);
	m_pNormals[cc++] = glm::vec3(0.238856f, 0.864188f, 0.442863f);
	m_pNormals[cc++] = glm::vec3(0.262866f, 0.951056f, 0.162460f);
	m_pNormals[cc++] = glm::vec3(0.500000f, 0.809017f, 0.309017f);
	m_pNormals[cc++] = glm::vec3(0.238856f, 0.864188f, -0.442863f);
	m_pNormals[cc++] = glm::vec3(0.262866f, 0.951056f, -0.162460f);
	m_pNormals[cc++] = glm::vec3(0.500000f, 0.809017f, -0.309017f);
	m_pNormals[cc++] = glm::vec3(0.850651f, 0.525731f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(0.716567f, 0.681718f, 0.147621f);
	m_pNormals[cc++] = glm::vec3(0.716567f, 0.681718f, -0.147621f);
	m_pNormals[cc++] = glm::vec3(0.525731f, 0.850651f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(0.425325f, 0.688191f, 0.587785f);
	m_pNormals[cc++] = glm::vec3(0.864188f, 0.442863f, 0.238856f);
	m_pNormals[cc++] = glm::vec3(0.688191f, 0.587785f, 0.425325f);
	m_pNormals[cc++] = glm::vec3(0.809017f, 0.309017f, 0.500000f);
	m_pNormals[cc++] = glm::vec3(0.681718f, 0.147621f, 0.716567f);
	m_pNormals[cc++] = glm::vec3(0.587785f, 0.425325f, 0.688191f);
	m_pNormals[cc++] = glm::vec3(0.955423f, 0.295242f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(1.000000f, 0.000000f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(0.951056f, 0.162460f, 0.262866f);
	m_pNormals[cc++] = glm::vec3(0.850651f, -0.525731f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(0.955423f, -0.295242f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(0.864188f, -0.442863f, 0.238856f);
	m_pNormals[cc++] = glm::vec3(0.951056f, -0.162460f, 0.262866f);
	m_pNormals[cc++] = glm::vec3(0.809017f, -0.309017f, 0.500000f);
	m_pNormals[cc++] = glm::vec3(0.681718f, -0.147621f, 0.716567f);
	m_pNormals[cc++] = glm::vec3(0.850651f, 0.000000f, 0.525731f);
	m_pNormals[cc++] = glm::vec3(0.864188f, 0.442863f, -0.238856f);
	m_pNormals[cc++] = glm::vec3(0.809017f, 0.309017f, -0.500000f);
	m_pNormals[cc++] = glm::vec3(0.951056f, 0.162460f, -0.262866f);
	m_pNormals[cc++] = glm::vec3(0.525731f, 0.000000f, -0.850651f);
	m_pNormals[cc++] = glm::vec3(0.681718f, 0.147621f, -0.716567f);
	m_pNormals[cc++] = glm::vec3(0.681718f, -0.147621f, -0.716567f);
	m_pNormals[cc++] = glm::vec3(0.850651f, 0.000000f, -0.525731f);
	m_pNormals[cc++] = glm::vec3(0.809017f, -0.309017f, -0.500000f);
	m_pNormals[cc++] = glm::vec3(0.864188f, -0.442863f, -0.238856f);
	m_pNormals[cc++] = glm::vec3(0.951056f, -0.162460f, -0.262866f);
	m_pNormals[cc++] = glm::vec3(0.147621f, 0.716567f, -0.681718f);
	m_pNormals[cc++] = glm::vec3(0.309017f, 0.500000f, -0.809017f);
	m_pNormals[cc++] = glm::vec3(0.425325f, 0.688191f, -0.587785f);
	m_pNormals[cc++] = glm::vec3(0.442863f, 0.238856f, -0.864188f);
	m_pNormals[cc++] = glm::vec3(0.587785f, 0.425325f, -0.688191f);
	m_pNormals[cc++] = glm::vec3(0.688191f, 0.587785f, -0.425325f);
	m_pNormals[cc++] = glm::vec3(-0.147621f, 0.716567f, -0.681718f);
	m_pNormals[cc++] = glm::vec3(-0.309017f, 0.500000f, -0.809017f);
	m_pNormals[cc++] = glm::vec3(0.000000f, 0.525731f, -0.850651f);
	m_pNormals[cc++] = glm::vec3(-0.525731f, 0.000000f, -0.850651f);
	m_pNormals[cc++] = glm::vec3(-0.442863f, 0.238856f, -0.864188f);
	m_pNormals[cc++] = glm::vec3(-0.295242f, 0.000000f, -0.955423f);
	m_pNormals[cc++] = glm::vec3(-0.162460f, 0.262866f, -0.951056f);
	m_pNormals[cc++] = glm::vec3(0.000000f, 0.000000f, -1.000000f);
	m_pNormals[cc++] = glm::vec3(0.295242f, 0.000000f, -0.955423f);
	m_pNormals[cc++] = glm::vec3(0.162460f, 0.262866f, -0.951056f);
	m_pNormals[cc++] = glm::vec3(-0.442863f, -0.238856f, -0.864188f);
	m_pNormals[cc++] = glm::vec3(-0.309017f, -0.500000f, -0.809017f);
	m_pNormals[cc++] = glm::vec3(-0.162460f, -0.262866f, -0.951056f);
	m_pNormals[cc++] = glm::vec3(0.000000f, -0.850651f, -0.525731f);
	m_pNormals[cc++] = glm::vec3(-0.147621f, -0.716567f, -0.681718f);
	m_pNormals[cc++] = glm::vec3(0.147621f, -0.716567f, -0.681718f);
	m_pNormals[cc++] = glm::vec3(0.000000f, -0.525731f, -0.850651f);
	m_pNormals[cc++] = glm::vec3(0.309017f, -0.500000f, -0.809017f);
	m_pNormals[cc++] = glm::vec3(0.442863f, -0.238856f, -0.864188f);
	m_pNormals[cc++] = glm::vec3(0.162460f, -0.262866f, -0.951056f);
	m_pNormals[cc++] = glm::vec3(0.238856f, -0.864188f, -0.442863f);
	m_pNormals[cc++] = glm::vec3(0.500000f, -0.809017f, -0.309017f);
	m_pNormals[cc++] = glm::vec3(0.425325f, -0.688191f, -0.587785f);
	m_pNormals[cc++] = glm::vec3(0.716567f, -0.681718f, -0.147621f);
	m_pNormals[cc++] = glm::vec3(0.688191f, -0.587785f, -0.425325f);
	m_pNormals[cc++] = glm::vec3(0.587785f, -0.425325f, -0.688191f);
	m_pNormals[cc++] = glm::vec3(0.000000f, -0.955423f, -0.295242f);
	m_pNormals[cc++] = glm::vec3(0.000000f, -1.000000f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(0.262866f, -0.951056f, -0.162460f);
	m_pNormals[cc++] = glm::vec3(0.000000f, -0.850651f, 0.525731f);
	m_pNormals[cc++] = glm::vec3(0.000000f, -0.955423f, 0.295242f);
	m_pNormals[cc++] = glm::vec3(0.238856f, -0.864188f, 0.442863f);
	m_pNormals[cc++] = glm::vec3(0.262866f, -0.951056f, 0.162460f);
	m_pNormals[cc++] = glm::vec3(0.500000f, -0.809017f, 0.309017f);
	m_pNormals[cc++] = glm::vec3(0.716567f, -0.681718f, 0.147621f);
	m_pNormals[cc++] = glm::vec3(0.525731f, -0.850651f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(-0.238856f, -0.864188f, -0.442863f);
	m_pNormals[cc++] = glm::vec3(-0.500000f, -0.809017f, -0.309017f);
	m_pNormals[cc++] = glm::vec3(-0.262866f, -0.951056f, -0.162460f);
	m_pNormals[cc++] = glm::vec3(-0.850651f, -0.525731f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(-0.716567f, -0.681718f, -0.147621f);
	m_pNormals[cc++] = glm::vec3(-0.716567f, -0.681718f, 0.147621f);
	m_pNormals[cc++] = glm::vec3(-0.525731f, -0.850651f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(-0.500000f, -0.809017f, 0.309017f);
	m_pNormals[cc++] = glm::vec3(-0.238856f, -0.864188f, 0.442863f);
	m_pNormals[cc++] = glm::vec3(-0.262866f, -0.951056f, 0.162460f);
	m_pNormals[cc++] = glm::vec3(-0.864188f, -0.442863f, 0.238856f);
	m_pNormals[cc++] = glm::vec3(-0.809017f, -0.309017f, 0.500000f);
	m_pNormals[cc++] = glm::vec3(-0.688191f, -0.587785f, 0.425325f);
	m_pNormals[cc++] = glm::vec3(-0.681718f, -0.147621f, 0.716567f);
	m_pNormals[cc++] = glm::vec3(-0.442863f, -0.238856f, 0.864188f);
	m_pNormals[cc++] = glm::vec3(-0.587785f, -0.425325f, 0.688191f);
	m_pNormals[cc++] = glm::vec3(-0.309017f, -0.500000f, 0.809017f);
	m_pNormals[cc++] = glm::vec3(-0.147621f, -0.716567f, 0.681718f);
	m_pNormals[cc++] = glm::vec3(-0.425325f, -0.688191f, 0.587785f);
	m_pNormals[cc++] = glm::vec3(-0.162460f, -0.262866f, 0.951056f);
	m_pNormals[cc++] = glm::vec3(0.442863f, -0.238856f, 0.864188f);
	m_pNormals[cc++] = glm::vec3(0.162460f, -0.262866f, 0.951056f);
	m_pNormals[cc++] = glm::vec3(0.309017f, -0.500000f, 0.809017f);
	m_pNormals[cc++] = glm::vec3(0.147621f, -0.716567f, 0.681718f);
	m_pNormals[cc++] = glm::vec3(0.000000f, -0.525731f, 0.850651f);
	m_pNormals[cc++] = glm::vec3(0.425325f, -0.688191f, 0.587785f);
	m_pNormals[cc++] = glm::vec3(0.587785f, -0.425325f, 0.688191f);
	m_pNormals[cc++] = glm::vec3(0.688191f, -0.587785f, 0.425325f);
	m_pNormals[cc++] = glm::vec3(-0.955423f, 0.295242f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(-0.951056f, 0.162460f, 0.262866f);
	m_pNormals[cc++] = glm::vec3(-1.000000f, 0.000000f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(-0.850651f, 0.000000f, 0.525731f);
	m_pNormals[cc++] = glm::vec3(-0.955423f, -0.295242f, 0.000000f);
	m_pNormals[cc++] = glm::vec3(-0.951056f, -0.162460f, 0.262866f);
	m_pNormals[cc++] = glm::vec3(-0.864188f, 0.442863f, -0.238856f);
	m_pNormals[cc++] = glm::vec3(-0.951056f, 0.162460f, -0.262866f);
	m_pNormals[cc++] = glm::vec3(-0.809017f, 0.309017f, -0.500000f);
	m_pNormals[cc++] = glm::vec3(-0.864188f, -0.442863f, -0.238856f);
	m_pNormals[cc++] = glm::vec3(-0.951056f, -0.162460f, -0.262866f);
	m_pNormals[cc++] = glm::vec3(-0.809017f, -0.309017f, -0.500000f);
	m_pNormals[cc++] = glm::vec3(-0.681718f, 0.147621f, -0.716567f);
	m_pNormals[cc++] = glm::vec3(-0.681718f, -0.147621f, -0.716567f);
	m_pNormals[cc++] = glm::vec3(-0.850651f, 0.000000f, -0.525731f);
	m_pNormals[cc++] = glm::vec3(-0.688191f, 0.587785f, -0.425325f);
	m_pNormals[cc++] = glm::vec3(-0.587785f, 0.425325f, -0.688191f);
	m_pNormals[cc++] = glm::vec3(-0.425325f, 0.688191f, -0.587785f);
	m_pNormals[cc++] = glm::vec3(-0.425325f, -0.688191f, -0.587785f);
	m_pNormals[cc++] = glm::vec3(-0.587785f, -0.425325f, -0.688191f);
	m_pNormals[cc++] = glm::vec3(-0.688191f, -0.587785f, -0.425325f);


	//Every md2 model have to be rotated in this way
	/*glm::mat4 FinalTransform =	TransformationMatrix *
	glm::rotate(-90.0f,glm::vec3(1.0f,0.0f,0.0f)) *
	glm::rotate(-90.0f,glm::vec3(0.0f,0.0f,1.0f));*/

	glm::mat4 FinalTransform = TransformationMatrix;


	int i, j;
	md2_frame_t *pframe;
	md2_vertex_t *pvert;
	vec3_t v_curr, norm;
	glm::vec3 n_curr;

	m_finalObject.resize(m_Object->frames.size());
	Vert aux_vertex;
	vector<Vert> aux_frame;

	for (GLuint k = 0; k < m_Object->frames.size(); ++k)
	{
		aux_frame.resize(m_Object->header.num_tris * 3);

		for (i = 0; i < m_Object->header.num_tris; ++i)
		{
			/* Draw each vertex */
			for (j = 0; j < 3; ++j)
			{

				pframe = &m_Object->frames[k];
				pvert = &pframe->verts[m_Object->triangles[i].vertex[j]];

				/* Compute texture coordinates */
				aux_vertex.TextureCoord = glm::vec2(((GLfloat)m_Object->texcoords[m_Object->triangles[i].st[j]].s / m_Object->header.skinwidth),
					1.0f - ((GLfloat)m_Object->texcoords[m_Object->triangles[i].st[j]].t / m_Object->header.skinheight));


				/* Interpolate normals */
				n_curr = m_pNormals[pvert->normalIndex];

				norm[0] = n_curr[0];
				norm[1] = n_curr[1];
				norm[2] = n_curr[2];

				aux_vertex.NormalCoord = glm::vec3(norm[0], norm[1], norm[2]);

				/* Interpolate vertices */
				v_curr[0] = pframe->scale[0] * pvert->v[0] + pframe->translate[0];
				v_curr[1] = pframe->scale[1] * pvert->v[1] + pframe->translate[1];
				v_curr[2] = pframe->scale[2] * pvert->v[2] + pframe->translate[2];


				aux_vertex.WorldCoord = FinalTransform * glm::vec4(v_curr[0], v_curr[1], v_curr[2], 1.0f);

				aux_frame[i * 3 + j] = aux_vertex;
			}
		}

		m_finalObject[k] = aux_frame;
	}

	delete m_pNormals;
}

/**
* Render MD2 using Vertex Buffer Object
*/
void DynamicModelLoader::Draw(GLuint shader)
{
	// Bind appropriate textures
	GLuint diffuseNr = 0;
	GLuint specularNr = 0;
	for (GLuint i = 0; i < 1; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
		// Retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		std::string number;
		std::string name = "texture_diffuse";
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();
		// Now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader, ("material[" + number + "]." + name).c_str()), i);
		// And finally bind the texture
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}

	// Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
	glUniform1f(glGetUniformLocation(shader, "material[0].shininess"), 16.0f);
	glUniform1i(glGetUniformLocation(shader, "nrDiffuseTextures"), diffuseNr);
	glUniform1i(glGetUniformLocation(shader, "nrDiffuseTextures"), specularNr);

	// Draw mesh
	glBindVertexArray(m_iVao);
	glDrawArrays(GL_TRIANGLES, 0, m_vVertex.size());
	glBindVertexArray(0);

	// Always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < 1; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	/*glDisableVertexAttribArray(WORLD_COORD_LOCATION);
	glDisableVertexAttribArray(NORMAL_COORD_LOCATION);
	glDisableVertexAttribArray(TEXTURE_COORD_LOCATION);*/
}

void DynamicModelLoader::DrawShadow(GLuint shader) {
	// Bind appropriate textures
	GLuint diffuseNr = 0;
	GLuint specularNr = 0;
	for (GLuint i = 0; i < 1; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
		// Retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		std::string number;
		std::string name = "texture_diffuse";
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();
		// Now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader, ("material[" + number + "]." + name).c_str()), i);
		// And finally bind the texture
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}

	// Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
	glUniform1f(glGetUniformLocation(shader, "material[0].shininess"), 16.0f);
	glUniform1i(glGetUniformLocation(shader, "nrDiffuseTextures"), diffuseNr);
	glUniform1i(glGetUniformLocation(shader, "nrDiffuseTextures"), specularNr);

	// Draw mesh
	glBindVertexArray(m_iVao);
	glDrawArrays(GL_TRIANGLES, 0, m_vVertex.size());
	glBindVertexArray(0);

	// Always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < 1; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

/**
* Initialize Vertex Buffer Object
*/
void  DynamicModelLoader::InitVAO()
{
	m_vVertex.resize(m_finalObject[0].size());

	glGenBuffers(1, &m_Vbo);

	// bind buffer for positions and copy data into buffer
	// GL_ARRAY_BUFFER is the buffer type we use to feed attributes
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

	//Set buffer to null with Stream Draw for dynamic feeding
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STREAM_DRAW);

	//Disable Buffers and vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//Generate the VAO
	glGenVertexArrays(1, &m_iVao);
	glBindVertexArray(m_iVao);

	// bind buffer for positions and copy data into buffer
	// GL_ARRAY_BUFFER is the buffer type we use to feed attributes
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vert), (GLvoid*)(0)); //Vertexs
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (GLvoid*)offsetof(Vert, NormalCoord)); //Normals
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (GLvoid*)offsetof(Vert, TextureCoord)); //Text Coords

	//Unbind the vertex array	
	glBindVertexArray(0);


	//Disable Buffers and vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
* Update Vertex Buffer Object
*/
void  DynamicModelLoader::UpdateVAO(int frame1, int frame2, float interpol)
{

	/* Check if it is in a valid range */
	if (frame1 > m_finalObject.size() - 1) frame1 = m_finalObject.size() - 1;
	if (frame1 < 0) frame1 = 0;
	if (frame2 > m_finalObject.size() - 1) frame2 = m_finalObject.size() - 1;
	if (frame2 < 0) frame2 = 0;




	Vert aux_vertex;

	for (GLuint i = 0; i < m_finalObject[frame1].size(); ++i)
	{

		/* Compute texture coordinates */
		aux_vertex.TextureCoord = glm::vec2(m_finalObject[frame1][i].TextureCoord.x, 1.0f - m_finalObject[frame1][i].TextureCoord.y);


		/* Interpolate normals */
		aux_vertex.NormalCoord = m_finalObject[frame1][i].NormalCoord +
			interpol * (m_finalObject[frame2][i].NormalCoord
			- m_finalObject[frame1][i].NormalCoord);

		/* Interpolate vertices */
		aux_vertex.WorldCoord = m_finalObject[frame1][i].WorldCoord +
			interpol * (m_finalObject[frame2][i].WorldCoord
			- m_finalObject[frame1][i].WorldCoord);

		m_vVertex[i] = aux_vertex;
	}

	//Bind Buffer to copy new data
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

	//Free the buffer
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STREAM_DRAW);

	//Fill it with new data
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert)* m_vVertex.size(), &m_vVertex[0], GL_STREAM_DRAW);

	//Disable Buffers and vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

/**
* Method to Load texture (If any)
*
* @params m_Object a pointer to the md2 structure
*
*/
void DynamicModelLoader::LoadTexture(md2_model_t * m_Object)
{
	if (m_Object->header.num_skins != 0)
	{
		//Generate texture ID and load texture data 
		int flo = m_sFile.find_last_of("/");
		string filename = string((m_sFile.substr(0, flo) + "/" + m_Object->skins[0].name).c_str());
		//cout << filename << endl;
		GLuint textureID;
		glGenTextures(1, &m_textureId);
		int width, height;
		unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		// Assign texture to ID
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		SOIL_free_image_data(image);
	}
	else
	{
		//Load a white texture in case the model doesn't have one
		GLubyte data[1];
		data[0] = 255;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

#undef FILE_REVISION

// Revision History:
// $Log: $
// $Header: $
// $Id: $