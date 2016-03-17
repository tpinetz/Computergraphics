#pragma once
#include "MainHeaders.h"

class Scene
{
private:
	GLFWwindow* window;

public:
	Scene();
	~Scene();

	bool init();

	bool run();
};

