#pragma once

#include "MainHeaders.h"
#include "Model.h"
#include "Camera.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ModelLoader.h"

namespace Renderer {

	struct LightRenderingData {
		glm::vec3 position;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		GLfloat constant;
		GLfloat linear;
		GLfloat quadratic;
	};

	struct DirectionalLightRenderingData {
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
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
		std::shared_ptr<Camera::Camera> getCamera();
		void beginDrawing(GLFWwindow* window);
		void endDrawing(GLFWwindow* window);

		void drawModel(std::shared_ptr<Model> model);
		void drawModel(std::shared_ptr<Model> model, glm::mat4 transform);
		void drawModel(ModelLoader& mod, glm::mat4 transform);

		inline void setUseLighting(bool useLighting) {
			m_useLighting = useLighting;
		}

		inline void addLight(std::shared_ptr<LightRenderingData> light) {
			m_lights.push_back(light);
		}

		inline void setDirectionalLight(std::shared_ptr<DirectionalLightRenderingData> dlight) {
			m_directionalLight = dlight;
		}

	private:
		bool m_useLighting = true;
		GLuint m_currentProgram;
		std::shared_ptr<Camera::Camera> m_camera;
		
		glm::vec3 m_lightcolor = glm::vec3(1.0f, 1.0f, 1.0f);
		std::vector<std::shared_ptr<LightRenderingData> > m_lights;
		std::shared_ptr<DirectionalLightRenderingData>  m_directionalLight;

	};

}