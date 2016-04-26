#include "Renderer.h"

namespace Renderer {
	Renderer::Renderer()
	{
	}


	Renderer::~Renderer()
	{
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

	void Renderer::drawModel(ModelLoader mod, glm::mat4 transform ) {
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

	void Renderer::activateTextures(std::shared_ptr<Model> model) {
		for (unsigned int i = 0; i < model->getTextures()->size(); i++){
			GLuint texture = model->getTextures()->at(i);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, texture);
		}
	}
	
	void Renderer::deactivateTextures(std::shared_ptr<Model> model) {
		for (unsigned int i = 0; i < model->getTextures()->size(); i++){
			GLuint texture = model->getTextures()->at(i);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	void Renderer::setLightingRelatedConfiguration() {
		GLint lightColorLoc = glGetUniformLocation(m_currentProgram, "lightColor");
		glUniform3f(lightColorLoc, m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);

		for (int i = 0; i < m_lights.size(); i++) {
			auto light = m_lights[i];
			GLint lightPosLoc = glGetUniformLocation(m_currentProgram, "light.position" );
			glUniform3f(lightPosLoc, light->position.x, light->position.y, light->position.z);

			GLint lightAmbientLoc = glGetUniformLocation(m_currentProgram, "light.ambient" );
			glUniform3f(lightAmbientLoc, light->ambient.x, light->ambient.y, light->ambient.z);

			GLint lightDiffuseLoc = glGetUniformLocation(m_currentProgram, "light.diffuse");
			glUniform3f(lightDiffuseLoc, light->diffuse.x, light->diffuse.y, light->diffuse.z);
			
			GLint lightSpecularLoc = glGetUniformLocation(m_currentProgram, "light.specular" );
			glUniform3f(lightSpecularLoc, light->specular.x, light->specular.y, light->specular.z);
		}

		GLint viewPosLoc = glGetUniformLocation(m_currentProgram, "viewPos");
		glUniform3f(viewPosLoc, m_camera->getCameraPosition().x, m_camera->getCameraPosition().y, m_camera->getCameraPosition().z);

	}

	void Renderer::beginDrawing(GLFWwindow* window) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
}