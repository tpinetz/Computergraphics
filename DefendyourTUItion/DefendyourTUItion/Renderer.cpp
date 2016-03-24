#include "Renderer.h"

namespace Renderer {
	Renderer::Renderer()
	{
	}


	Renderer::~Renderer()
	{
	}

	void Renderer::drawModel(std::shared_ptr<Model> model) {

		glBindBuffer(GL_ARRAY_BUFFER, *model->getVertexBuffer());
		glDrawArrays(GL_TRIANGLES, 0, model->getTriangleCount() * 3);
	}

	void Renderer::beginDrawing(GLFWwindow* window) {
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::setShader(GLuint pgroamID) {
		
	}
}