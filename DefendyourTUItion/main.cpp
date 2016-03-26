#include "Scene.h"
//#include "ObjectLoader.h"
int main(int argc, char** argv) {

	ObjectLoader::ObjectLoader* objectLoader = new ObjectLoader::ObjectLoader();
	objectLoader->loadObject("monkey.obj");
	delete objectLoader;


	Scene::Scene* scene = new Scene::Scene();
	
	
	if (!scene->init()) {
		std::cerr << "Failed to init Scene.";
		return -1;
	}

	if (!scene->run()) {
		std::cerr << "Unexpectatly failed running the game";
		return -1;
	}

	delete scene;

	return 0;
}