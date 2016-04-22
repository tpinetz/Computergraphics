#pragma once

#include "MainHeaders.h"
#include "Model.h"
#include "Camera.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Renderer {

	class Renderer
	{
	private:
		void activateTextures(std::shared_ptr<Model> model);
		void deactivateTextures(std::shared_ptr<Model> model);
	public:
		Renderer();
		~Renderer();

		void startShader(GLuint programID);
		void stopShader();
		void setCamera(std::shared_ptr<Camera::Camera> camera);
		void beginDrawing(GLFWwindow* window);

		void drawModel(std::shared_ptr<Model> model);
		void drawModel(std::shared_ptr<Model> model, glm::mat4 transform);
	private:
		GLuint m_currentProgram;
		std::shared_ptr<Camera::Camera> m_camera;
	};

}