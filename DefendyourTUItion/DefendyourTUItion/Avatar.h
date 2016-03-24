#pragma once
#include "GameObject.h"
#include "Camera.h"

namespace Avatar {


	class Avatar :
		public GameObject::GameObject
	{
	public:
		Avatar(std::shared_ptr<Camera::Camera> camera);
		~Avatar();
		void update(double deltaTime);
		void render();

		bool operator==(const Avatar& rhs) {
			return m_name == rhs.m_name;
		}
	private:
		std::shared_ptr<Camera::Camera> m_camera;
		static GLfloat m_modelVertices[];
	};

}