#pragma once
#include "PhysicsObject.h"
#include "Model.h"
#include "ObjectLoader.hpp"
#include "FormattingHelper.h"

namespace GameObject {
	
class Projectile :
		public PhysicsObject
	{
		struct Particle {
			glm::vec3 pos, speed;
			unsigned char r, g, b, a; // Color
			float size, angle, weight;
			float life; // Remaining life of the particle. if < 0 : dead and unused.
			float cameradistance;
			bool operator<(Particle& that){
				return this->cameradistance > that.cameradistance;
			}
		};
	private:
		void setUpParticles();
		void updateParticles(float deltaTime);
		void renderParticles();
	public:
		static std::string m_typeName;

		Projectile();
		Projectile(GLuint shader, glm::vec3 position, glm::vec3 scale, 
			glm::vec3 direction, std::shared_ptr<Renderer::Model> model,
			std::shared_ptr<Camera::Camera> camera);
		~Projectile();
		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);

		void handlePhysicsCollision(PhysicsObject* otherObject);

		inline bool isActive() {
			return m_active;
		}

	private:

		glm::vec3 m_direction;
		GLuint m_shader;
		std::shared_ptr<Renderer::Model> m_model;
		std::shared_ptr<Camera::Camera> m_camera;

		std::string m_modelString = "../Assets/Model/Floor/Floor.obj";
		std::string m_textureString = "../Assets/Textures/ground.jpg";

		bool m_active;
		GLfloat m_force = 500.f;
		GLfloat m_lifeTime = 1000.0f;
		static const int s_MaxParticles = 10000;
		Particle m_ParticlesContainer[s_MaxParticles];

		static GLfloat m_particleVertexData[];

		// The VBO containing the positions and sizes of the particles
		GLuint billboard_vertex_buffer;
		GLuint particles_position_buffer;
		// The VBO containing the colors of the particles
		GLuint particles_color_buffer;

		GLfloat g_particule_position_size_data[s_MaxParticles];
		GLfloat g_particule_color_data[s_MaxParticles];
		int m_ParticlesCount = 0;

	};

}