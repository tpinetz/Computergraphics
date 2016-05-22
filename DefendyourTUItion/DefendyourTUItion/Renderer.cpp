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

	std::shared_ptr<Camera::Camera> Renderer::getCamera()
	{
		return m_camera;
	}
}