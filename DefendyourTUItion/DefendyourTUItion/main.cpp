#include "Scene.h"

int main() {
	Scene::Scene* scene = new Scene::Scene();
	
	
	if (!scene->init()) {
		std::cerr << "Failed to init Scene.";
		return -1;
	}

	if (!scene->run()) {
		std::cerr << "Unexpectatly failed running the game";
		return -1;
	}


	return 0;
}