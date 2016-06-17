#ifndef DYNAMICMODELLOADER_H
#define DYNAMICMODELLOADER_H



#include <sstream>
using namespace std;

#include "MainHeaders.h"
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include "glm/glm.hpp" // glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr
#include "glm/gtx/transform2.hpp" // for glm::lookAt
#include <SOIL\src\SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

//Includes
#include "DynamicMesh.h"
#include <vector>




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
	DynamicModelLoader();

	///Default destructor
	~DynamicModelLoader();

	///Load an MD2 model from file.
	void LoadModel(const char *filename, const glm::mat4 &TransformationMatrix);

	///Calculate the current frame in animation
	void Animate(double time);

	///Render MD2 using Vertex Buffer Object
	void Draw(GLuint shader);


	void DrawShadow(GLuint shader);

	///Method to get the array with all the bone transformations
	std::vector<glm::mat4>& getBonesMatrix(GLuint &count){ count = m_finalBoneTransforms.size(); return m_finalBoneTransforms; }

	GLdouble getTicksPerSecond(){ return scene->mAnimations[0]->mTicksPerSecond != 0 ? scene->mAnimations[0]->mTicksPerSecond : 25.0; }

private:
	///Process the mesh to obtain the object and bones
	void ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4 &TransformationMatrix, DynamicMesh &data);

	///Process a node in the hierarchy to obtain the mesh
	void ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4 &TransformationMatrix);

	///Function to process the bone hierarchy
	void BoneHeirarchyTransform(float AnimationTime, const aiNode *pNode, const glm::mat4 & parentTransform);

	///Function to obtain the interpolated animation in a specific time
	glm::mat4 Interpolatedtransformation(float AnimationTime, const aiNodeAnim * pNodeAnim);

	//Variables

public:
	std::vector<DynamicMesh> m_vMeshes;
	std::map<std::string, GLuint> m_BoneMapping;
	GLuint m_NumBones;
	std::vector<glm::mat4> m_originalBoneTransform;
	std::vector<glm::mat4> m_finalBoneTransforms;
	glm::mat4 m_userTransform;
	glm::mat4 m_GlobalInverseTransform;

	/*Texture * m_pText;*/
	std::string m_sFile;
	std::string m_directory;
	aiScene *scene;

};


#endif //DynamicObject_H