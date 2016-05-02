#include "ModelLoaderHelper.h"

namespace Common {
	std::shared_ptr<ModelLoaderHelper> ModelLoaderHelper::m_instance = nullptr;

	ModelLoaderHelper::ModelLoaderHelper()
	{
	}


	ModelLoaderHelper::~ModelLoaderHelper()
	{
	}

	std::shared_ptr<ModelLoaderHelper> ModelLoaderHelper::getInstance() {
		if (m_instance == nullptr) {
			m_instance = std::shared_ptr<ModelLoaderHelper>(new ModelLoaderHelper());
		}
		return m_instance;
	}

	std::shared_ptr<Renderer::Model> ModelLoaderHelper::getTextureModel(std::string modelString, 
		std::string bumpTextureString, std::string specularTextureString){
		std::vector<Vertex> vertices = loadOBJ(modelString.c_str());		//"monkey.obj", "cube.obj","cat.obj"

		if (vertices.empty()) {
			std::cerr << "Failed to load model Floor.";
			return nullptr;
		}

		GLuint vao;
		GLuint vertexBuffer;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
			&vertices[0], GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),                  // stride
			(void*)0            // array buffer offset
			);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),                  // stride
			(GLvoid*)offsetof(Vertex, Normal)            // array buffer offset
			);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),                 // stride
			(GLvoid*)offsetof(Vertex, TexCoords)             // array buffer offset
			);

		glBindVertexArray(0);


		auto model = std::shared_ptr<Renderer::Model>(new Renderer::Model(vao, vertexBuffer, vertices.size()/3));

		auto textureHelper = Common::TextureHelper::getInstance();
		model->addTexture("material.diffuse", textureHelper->getTextureByName(bumpTextureString));
		model->addTexture("material.specular", textureHelper->getTextureByName(specularTextureString));
		
		return model;
	}
}