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
			glm::vec3 pos;
			GLfloat rotationSpeed, rotation;
			GLfloat scale;
			GLfloat angle, displacement;
		};
	private:
		void setUpParticles();
		void updateParticles(float deltaTime);
		void renderParticles(std::shared_ptr<Renderer::Renderer> renderer);
	public:
		static std::string m_typeName;

		Projectile(GLuint shader, glm::vec3 position, glm::vec3 scale, 
			glm::vec3 direction, std::shared_ptr<Renderer::Model> model,
			std::shared_ptr<Camera::Camera> camera, std::shared_ptr<ModelLoader> particleModel, GLuint particleShader);
		~Projectile();
		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader);

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
		GLfloat m_force = 400.f;
		GLfloat m_lifeTime = 1000.0f;
		static const int s_MaxParticles = 70;
		Particle m_particles[s_MaxParticles];
		glm::mat4 m_particleModels[s_MaxParticles];

		static GLfloat m_particleVertexData[];

		// The VBO containing the positions and sizes of the particles
		GLuint billboard_vertex_buffer;
		GLuint particles_position_buffer;
		// The VBO containing the colors of the particles
		GLuint particles_color_buffer;

		GLfloat g_particule_position_size_data[s_MaxParticles];
		GLfloat g_particule_color_data[s_MaxParticles];
		int m_ParticlesCount = 0;

		std::shared_ptr<ModelLoader> m_particleModel;
		GLuint m_particleShader;

	};

}