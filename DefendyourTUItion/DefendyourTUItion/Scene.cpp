#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}


bool Scene::init() {
	if (!glfwInit()) {
		std::cerr << "Test!";
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	window = glfwCreateWindow(1024, 768, "Defend your TUItion", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Failed to create Window";
		return false;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize.";
		return false;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	return true;
}

bool Scene::run() {
	do {
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	
	return true;
}