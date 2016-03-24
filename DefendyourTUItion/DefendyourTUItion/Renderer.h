#pragma once

#include "MainHeaders.h"
#include "Model.h"

namespace Renderer {

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void setShader(GLuint pgroamID);
		void beginDrawing(GLFWwindow* window);

		void drawModel(std::shared_ptr<Model> model);
	private:


	};

}