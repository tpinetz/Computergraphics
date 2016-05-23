#include "Renderer.h"

namespace Renderer {
	Renderer::Renderer()
	{
		setupFreeType();
	}


	Renderer::~Renderer()
	{
	}

	bool Renderer::init() {
		return setupFreeType();
	}

	bool Renderer::setupFreeType() {
		FT_Error error = FT_Init_FreeType(&m_library);
		if (error) {
			std::cerr << "Failed to initialize Freetype." << std::endl;
			return false;
		}
		
		error = FT_New_Face(m_library,
			"../Assets/Font/arial.ttf",
			0,
			&m_face);

		if (error) {
			std::cerr << "Failed to read arial.ttf" << std::endl;
			return false;
		}

		FT_Set_Pixel_Sizes(m_face, 0, 48);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

		for (GLubyte c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				m_face->glyph->bitmap.width,
				m_face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				m_face->glyph->bitmap.buffer
				);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Now store character for later use
			Character character = {
				texture,
				glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
				glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
				m_face->glyph->advance.x
			};
			m_Characters.insert(std::pair<GLchar, Character>(c, character));
		}
		FT_Done_Face(m_face);
		FT_Done_FreeType(m_library);

		glGenVertexArrays(1, &m_textVAO);
		glGenBuffers(1, &m_textVBO);
		glBindVertexArray(m_textVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_textVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return true;
	}

	void Renderer::drawModel(std::shared_ptr<Model> model) {
		glm::mat4 transform;
		transform= glm::translate(transform, glm::vec3(0, 0, 0));
		drawModel(model, transform);
	}

	void Renderer::drawModel(std::shared_ptr<Model> model, glm::mat4 transform) {
		GLint modelLoc = glGetUniformLocation(m_currentProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
		
		GLint viewLoc = glGetUniformLocation(m_currentProgram, "view");
		GLint projLoc = glGetUniformLocation(m_currentProgram, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_camera->getViewMatrix()));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_camera->getProjectionMatrix()));

		if (m_useLighting) {
			setLightingRelatedConfiguration();
		}

		activateTextures(model);

		glBindVertexArray(model->getVAO());

		if (model->getHasIndices()) {
			glDrawElements(GL_TRIANGLES, model->getTriangleCount() * 3, GL_UNSIGNED_INT, (GLvoid*)0);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, model->getTriangleCount() * 3);		//You need to change it with diffrent objects, i guess it should be vertices size
		}

		glBindVertexArray(0);
		deactivateTextures(model);
	}

	void Renderer::drawModel(ModelLoader& mod, glm::mat4 transform ) {
		GLint modelLoc = glGetUniformLocation(m_currentProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));

		if (m_useLighting) {
			setLightingRelatedConfiguration();
		}

		GLint viewLoc = glGetUniformLocation(m_currentProgram, "view");
		GLint projLoc = glGetUniformLocation(m_currentProgram, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_camera->getViewMatrix()));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_camera->getProjectionMatrix()));
		
		mod.Draw(m_currentProgram);
	}

	void Renderer::drawParticles(ModelLoader& mod, glm::mat4 transform, int amount) {
		if (m_useLighting) {
			setLightingRelatedConfiguration();
		}

		GLint viewLoc = glGetUniformLocation(m_currentProgram, "view");
		GLint projLoc = glGetUniformLocation(m_currentProgram, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_camera->getViewMatrix()));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_camera->getProjectionMatrix()));

		mod.DrawInstanced(m_currentProgram, amount);
	}

	void Renderer::activateTextures(std::shared_ptr<Model> model) {
		for (unsigned int i = 0; i < model->getTextures().size(); i++){
			auto texturePair = model->getTextures()[i];
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, texturePair.second);
			glUniform1i(glGetUniformLocation(m_currentProgram, texturePair.first.c_str()), i);
		}
		glUniform1f(glGetUniformLocation(m_currentProgram, "material.shininess"), 32.0f );
	}
	
	void Renderer::deactivateTextures(std::shared_ptr<Model> model) {
		for (unsigned int i = 0; i < model->getTextures().size(); i++){
			auto texturePair = model->getTextures()[i];
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	void Renderer::setLightingRelatedConfiguration() {

		for (int i = 0; i < m_lights.size(); i++) {
			auto light = m_lights[i];
			GLint lightPosLoc = glGetUniformLocation(m_currentProgram, "pointLight.position" );
			glUniform3f(lightPosLoc, light->position.x, light->position.y, light->position.z);

			GLint lightAmbientLoc = glGetUniformLocation(m_currentProgram, "pointLight.ambient" );
			glUniform3f(lightAmbientLoc, light->ambient.x, light->ambient.y, light->ambient.z);

			GLint lightDiffuseLoc = glGetUniformLocation(m_currentProgram, "pointLight.diffuse");
			glUniform3f(lightDiffuseLoc, light->diffuse.x, light->diffuse.y, light->diffuse.z);
			
			GLint lightSpecularLoc = glGetUniformLocation(m_currentProgram, "pointLight.specular" );
			glUniform3f(lightSpecularLoc, light->specular.x, light->specular.y, light->specular.z);
			

			glUniform1f(glGetUniformLocation(m_currentProgram, "pointLight.constant"), light->constant);
			glUniform1f(glGetUniformLocation(m_currentProgram, "pointLight.linear"), light->linear);
			glUniform1f(glGetUniformLocation(m_currentProgram, "pointLight.quadratic"), light->quadratic);

		}

		glUniform3f(glGetUniformLocation(m_currentProgram, "dirLight.direction"),
			m_directionalLight->direction.x, m_directionalLight->direction.y, m_directionalLight->direction.z);
		glUniform3f(glGetUniformLocation(m_currentProgram, "dirLight.ambient"),
			m_directionalLight->ambient.x, m_directionalLight->ambient.y, m_directionalLight->ambient.z);
		glUniform3f(glGetUniformLocation(m_currentProgram, "dirLight.diffuse"),
			m_directionalLight->diffuse.x, m_directionalLight->diffuse.y, m_directionalLight->diffuse.z);
		glUniform3f(glGetUniformLocation(m_currentProgram, "dirLight.specular"),
			m_directionalLight->specular.x, m_directionalLight->specular.y, m_directionalLight->specular.z);



		GLint viewPosLoc = glGetUniformLocation(m_currentProgram, "viewPos");
		glUniform3f(viewPosLoc, m_camera->getCameraPosition().x, m_camera->getCameraPosition().y, m_camera->getCameraPosition().z);

	}

	void Renderer::drawText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
		glUniform3f(glGetUniformLocation(m_currentProgram, "textColor"), color.x, color.y, color.z);
		glUniformMatrix4fv(glGetUniformLocation(m_currentProgram, "projection"), 1, GL_FALSE, glm::value_ptr(m_camera->getOrthoMatrix()));
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(m_textVAO);

		// Iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = m_Characters[*c];

			GLfloat xpos = x + ch.Bearing.x * scale;
			GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			GLfloat w = ch.Size.x * scale;
			GLfloat h = ch.Size.y * scale;
			// Update VBO for each character
			GLfloat vertices[6][4] = {
				{ xpos, ypos + h, 0.0, 0.0 },
				{ xpos, ypos, 0.0, 1.0 },
				{ xpos + w, ypos, 1.0, 1.0 },

				{ xpos, ypos + h, 0.0, 0.0 },
				{ xpos + w, ypos, 1.0, 1.0 },
				{ xpos + w, ypos + h, 1.0, 0.0 }
			};
			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, m_textVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Renderer::beginDrawing(GLFWwindow* window) {
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::endDrawing(GLFWwindow* window) {
		glfwSwapBuffers(window);
	}

	void Renderer::startShader(GLuint programID) {
		m_currentProgram = programID;
		glUseProgram(programID);
	}

	void Renderer::stopShader() {
		glUseProgram(0);
	}

	void Renderer::setCamera(std::shared_ptr<Camera::Camera> camera) {
		m_camera = camera;
	}

	std::shared_ptr<Camera::Camera> Renderer::getCamera()
	{
		return m_camera;
	}
}