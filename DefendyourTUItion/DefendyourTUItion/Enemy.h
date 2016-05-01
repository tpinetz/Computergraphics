#pragma once
#include "Model.h"
#include "Renderer.h"
#include "ObjectLoader.hpp"
#include "TextureHelper.h"
#include "ModelLoader.h"
#include "FormattingHelper.h"
#include "PhysicsObject.h"


namespace GameObject{

	class Enemy
	: public PhysicsObject
	{
	public:
		static std::string m_typeName;
		Enemy(std::string name, glm::vec3 position, GLuint shader, ModelLoader& mod);
		~Enemy();

		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);

		void handlePhysicsCollision(PhysicsObject* otherObject);
		inline bool isDead() {
			return m_dead;
		}
	private:
		
		GLfloat movementSpeed = 3;
		GLuint m_shader;
		std::string m_modelString = "../Assets/Model/nanosuit/nanosuit.obj";
		ModelLoader mod;

		bool m_dead = false;
	};
}

