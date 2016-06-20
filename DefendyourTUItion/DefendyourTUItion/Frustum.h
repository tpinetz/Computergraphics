#pragma once

#include "MainHeaders.h"
#include "glm\gtc\type_ptr.hpp"

namespace Renderer {

	class Frustum {
	public:
		Frustum::Frustum();
		Frustum::~Frustum();
		void updateViewProjMatrix(glm::mat4& view, glm::mat4& projection);
		void updateFrustum(glm::mat4& model);

		bool pointInFrustum(float x, float y, float z);
		bool CubeInFrustum(float x, float y, float z, float size);

		void toggle() {
			activated = !activated;
			std::cout << "View Frustum Culling turned " << (activated ? "on" : "off") << std::endl;
		}

	private:
		float frustum[6][4];
		glm::mat4 m_view;
		glm::mat4 m_proj;
		bool activated = true;
	};
}