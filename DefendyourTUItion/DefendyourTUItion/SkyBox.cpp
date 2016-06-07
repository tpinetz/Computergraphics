#include "SkyBox.h"
GLfloat skyboxVertices[] = {
	// Positions          
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

namespace GameObject {

	SkyBox::SkyBox(GLuint shader)
		:m_shader(shader)
	{
		m_position = glm::vec3(0, -2, 0);
		m_scale = glm::vec3(10, 10, 10);
		m_transform = getTransformMatrix();

		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glBindVertexArray(0);

		faces.push_back("../Assets/Textures/clouds.jpg");
		faces.push_back("../Assets/Textures/clouds.jpg");
		faces.push_back("../Assets/Textures/clouds.jpg");
		faces.push_back("../Assets/Textures/clouds.jpg");
		faces.push_back("../Assets/Textures/clouds.jpg");
		faces.push_back("../Assets/Textures/clouds.jpg");
		cubemapTexture = loadCubemap(faces);
	}


	SkyBox::~SkyBox()
	{
	}

	GLuint SkyBox::loadCubemap(vector<const GLchar*> faces)
	{
		GLuint textureID;
		glGenTextures(1, &textureID);

		int width, height;
		unsigned char* image;

		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		for (GLuint i = 0; i < faces.size(); i++)
		{
			image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		return textureID;
	}

	void SkyBox::update(double time) {

	}

	void SkyBox::render(std::shared_ptr<Renderer::Renderer> renderer) {
/*		//glDisable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		glDisable(GL_DEPTH_TEST);
		GLint modelLoc = glGetUniformLocation(m_shader, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_transform));


		GLint viewLoc = glGetUniformLocation(m_shader, "view");
		GLint projLoc = glGetUniformLocation(m_shader, "projection");
		std::shared_ptr<Camera::Camera> m_camera = renderer->getCamera();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_camera->getViewMatrix()));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_camera->getProjectionMatrix()));

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(m_shader, "skybox"), 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthMask(GL_TRUE);
		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);     
		//glCullFace(GL_BACK);*/
	}

	void SkyBox::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
		// TODO: not sure if the skybox should throw shadows.
	}

}
