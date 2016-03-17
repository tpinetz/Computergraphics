#include "Scene.h"

int main() {
	Scene* scene = new Scene();
	
	if (!scene->init()) {
		std::cerr << "Failed to init Scene.";
		return -1;
	}

	if (!scene->run()) {
		std::cerr << "Unexpectatly failed to running the game";
		return -1;
	}

	return 0;
}