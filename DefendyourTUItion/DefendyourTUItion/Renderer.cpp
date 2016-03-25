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

		glBindBuffer(GL_ARRAY_BUFFER, *model->getVertexBuffer());
		glDrawArrays(GL_TRIANGLES, 0, model->getTriangleCount() * 3);
	}

	void Renderer::beginDrawing(GLFWwindow* window) {
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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