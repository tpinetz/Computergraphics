#pragma once

#include "MainHeaders.h"
#include "Model.h"
#include "Camera.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Renderer {

	struct LightRenderingData {
		glm::vec3 position;
		GLfloat lightStrength;
	};

	class Renderer
	{
	private:
		void activateTextures(std::shared_ptr<Model> model);
		void deactivateTextures(std::shared_ptr<Model> model);
		void setLightingRelatedConfiguration();
	public:
		Renderer();
		~Renderer();

		void startShader(GLuint programID);
		void stopShader();
		void setCamera(std::shared_ptr<Camera::Camera> camera);
		void beginDrawing(GLFWwindow* window);
		void endDrawing(GLFWwindow* window);

		void drawModel(std::shared_ptr<Model> model);
		void drawModel(std::shared_ptr<Model> model, glm::mat4 transform);

		inline void setUseLighting(bool useLighting) {
			m_useLighting = useLighting;
		}

		inline void addLight(std::shared_ptr<LightRenderingData> light) {
			m_lights.push_back(light);
		}

	private:
		bool m_useLighting = true;
		GLuint m_currentProgram;
		std::shared_ptr<Camera::Camera> m_camera;
		
		glm::vec3 m_lightcolor = glm::vec3(1.0f, 1.0f, 1.0f);
		std::vector<std::shared_ptr<LightRenderingData> > m_lights;

	};

}