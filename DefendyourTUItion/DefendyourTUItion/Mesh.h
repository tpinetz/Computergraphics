#pragma once
#include "MainHeaders.h"
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <assimp/Importer.hpp>
#include "TextureHelper.h"
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

struct Vertex {
	// Position
	glm::vec3 Position;
	// Normal
	glm::vec3 Normal;
	// TexCoords
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	std::string type;
	aiString path;
};

class Mesh {
private:
	void setupTextures(GLuint shader);
	void deactivateTextures();
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	void Draw(GLuint shader);
	void DrawInstanced(GLuint shader, int amount);
	void DrawShadow(GLuint shader);

	inline GLuint getVAO() {
		return VAO;
	}
private:
	/* Render data */
	GLuint VAO, VBO, EBO;

	void setupMesh();

};