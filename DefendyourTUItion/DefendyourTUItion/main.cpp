#include "Scene.h"

int main() {
	Scene* scene = new Scene();
	
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