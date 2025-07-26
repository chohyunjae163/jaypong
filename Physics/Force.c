#ifndef FORCE_H
#define FORCE_H

#include "./Vec2.c"
#include "./Particle.c"

Vector2 GenerateDragForce(Particle particle, float k) {
	Vector2 drag_force = { .x = 0, .y = 0 };

	Vector2 v = particle.velocity;
	// drag direction is the opposite of particle velocity direction
	const Vector2 v_dir = Vec2_UnitVector(v);
	const Vector2 drag_dir = Vec2_Scale(v_dir, -1.0f);

	// calculate the drag magnitude, k * |v| ^ 2
	const float drag_mag = k * Vec2_MagnitudeSquared(v);

	//generate the final drag force with direction and magnitude
	drag_force = Vec2_Scale(drag_dir, drag_mag);
	return drag_force;
}

Vector2 GenerateSpringForce(const Particle a, const Particle b, float restLength, float k) {
	
	Vector2 d = Vec2_Sub(a.position, b.position);

	float displacement = Vec2_Magnitude(d) - restLength;

	Vector2 spring_dir = Vec2_UnitVector(d);

	float spring_mag = -k * displacement;

	Vector2 spring_force = Vec2_Scale(spring_dir, spring_mag);
	return spring_force;
}

#endif
