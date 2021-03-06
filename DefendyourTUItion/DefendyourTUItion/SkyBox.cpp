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
		m_position = glm::vec3(0, 0, 0);
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

		faces.push_back("../Assets/Textures/PondNight/posx.jpg");
		faces.push_back("../Assets/Textures/PondNight/negx.jpg");
		faces.push_back("../Assets/Textures/PondNight/posy.jpg");
		faces.push_back("../Assets/Textures/PondNight/negy.jpg");
		faces.push_back("../Assets/Textures/PondNight/posz.jpg");
		faces.push_back("../Assets/Textures/PondNight/negz.jpg");

		/*faces.push_back("../Assets/Textures/Powerlines/posx.jpg");
		faces.push_back("../Assets/Textures/Powerlines/negx.jpg");
		faces.push_back("../Assets/Textures/Powerlines/posy.jpg");
		faces.push_back("../Assets/Textures/Powerlines/negy.jpg");
		faces.push_back("../Assets/Textures/Powerlines/posz.jpg");
		faces.push_back("../Assets/Textures/Powerlines/negz.jpg");*/

		/*faces.push_back("../Assets/Textures/sor_land/land_rt.jpg");
		faces.push_back("../Assets/Textures/sor_land/land_lf.jpg");
		faces.push_back("../Assets/Textures/sor_land/land_up.jpg");
		faces.push_back("../Assets/Textures/sor_land/land_dn.jpg");
		faces.push_back("../Assets/Textures/sor_land/land_bk.jpg");
		faces.push_back("../Assets/Textures/sor_land/land_ft.jpg");*/

		/*faces.push_back("../Assets/Textures/skybox/right.jpg");
		faces.push_back("../Assets/Textures/skybox/left.jpg");
		faces.push_back("../Assets/Textures/skybox/top.jpg");
		faces.push_back("../Assets/Textures/skybox/bottom.jpg");
		faces.push_back("../Assets/Textures/skybox/back.jpg");
		faces.push_back("../Assets/Textures/skybox/front.jpg");*/

		/*faces.push_back("../Assets/Textures/CNTower/posx.jpg");
		faces.push_back("../Assets/Textures/CNTower/negx.jpg");
		faces.push_back("../Assets/Textures/CNTower/posy.jpg");
		faces.push_back("../Assets/Textures/CNTower/negy.jpg");
		faces.push_back("../Assets/Textures/CNTower/posz.jpg");
		faces.push_back("../Assets/Textures/CNTower/negz.jpg");*/

		/*faces.push_back("../Assets/Textures/NightPath/posx.jpg");
		faces.push_back("../Assets/Textures/NightPath/negx.jpg");
		faces.push_back("../Assets/Textures/NightPath/posy.jpg");
		faces.push_back("../Assets/Textures/NightPath/negy.jpg");
		faces.push_back("../Assets/Textures/NightPath/posz.jpg");
		faces.push_back("../Assets/Textures/NightPath/negz.jpg");*/
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

	int SkyBox::render(std::shared_ptr<Renderer::Renderer> renderer) {
		glDisable(GL_CULL_FACE);
		glDepthMask(GL_FALSE);
		glUseProgram(m_shader);
		
		//glDisable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		glDisable(GL_DEPTH_TEST);
		GLint modelLoc = glGetUniformLocation(m_shader, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_transform));

		GLint viewLoc = glGetUniformLocation(m_shader, "view");
		GLint projLoc = glGetUniformLocation(m_shader, "projection");
		GLint scaleLoc = glGetUniformLocation(m_shader, "scale");
		glUniform3fv(scaleLoc, 1, &m_scale[0]);
		std::shared_ptr<Camera::Camera> m_camera = renderer->getCamera();
		glm::mat4 view = glm::mat4(glm::mat3(m_camera->getViewMatrix()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_camera->getProjectionMatrix()));

		glBindVertexArray(skyboxVAO);

		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(m_shader, "skybox"), 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthMask(GL_TRUE);

		glUseProgram(0);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);     
		glCullFace(GL_BACK);
		return 1;
	}

	void SkyBox::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
		// TODO: not sure if the skybox should throw shadows.
	}

}
