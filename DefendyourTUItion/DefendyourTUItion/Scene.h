#pragma once
#include "MainHeaders.h"
#include "ShaderHelper.h"

class Scene
{
private:
	void render();

public:
	Scene();
	~Scene();

	bool init();

	bool run();

private:
	GLFWwindow* window;
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	ShaderHelper* shaderHelper;

};

