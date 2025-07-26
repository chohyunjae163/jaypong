
#ifndef PARTICLE
#define PARTICLE

#include "Vec2.c"

float PARTICLE_RADIUS = 5.0f;

typedef struct {
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;

	float mass;
} Particle;


void Particle_Integrate(Particle* particle, Vector2 force, float dt) {
	if (particle != NULL) {
		// a = F/m
		particle->acceleration = Vec2_Scale(force, 1.0f / particle->mass);//force / particle->mass;
		
		//integrate the acceleration to find the new velocity
		Vector2 acceleration_delta = Vec2_Scale(particle->acceleration, dt);
		particle->velocity = Vec2_Add(particle->velocity, acceleration_delta);

		//integrate the velocity to find the position
		Vector2 velocity_delta = Vec2_Scale(particle->velocity, dt);
		particle->position = Vec2_Add(particle->position, velocity_delta);

	}
}


#endif





