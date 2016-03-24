#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Model.h"
#include "Renderer.h"

namespace Avatar {


	class Avatar :
		public GameObject::GameObject
	{
	private:
		void initModel();

	public:
		Avatar(std::shared_ptr<Camera::Camera> camera);
		~Avatar();
		void update(double deltaTime);
		void render(std::shared_ptr<Renderer::Renderer> renderer);

		bool operator==(const Avatar& rhs) {
			return m_name == rhs.m_name;
		}
	private:
		std::shared_ptr<Camera::Camera> m_camera;
		std::shared_ptr<Renderer::Model> m_model;
		static GLfloat m_modelVertices[];

	};

}