
#include <SDL3/SDL_stdinc.h>

#ifndef Vec2
#define Vec2

typedef struct { float x; float y; } Vector2;

Vector2 
Vec2_Add(Vector2 a, Vector2 b) {
	a.x += b.x;
	a.y += b.y;
	return a;
}

Vector2 
Vec2_Sub(Vector2 a, Vector2 b) {
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

Vector2 
Vec2_Scale(Vector2 a, float v) {
	a.x *= v;
	a.y *= v;
	return a;
}

Vector2 
Vec2_Rotate(Vector2 a, float angle) {
	Vector2 ret;
	ret.x = a.x * SDL_cos(angle) - a.y * SDL_sin(angle);
	ret.y = a.x * SDL_sin(angle) + a.y * SDL_cos(angle);
	return ret;
}

float 
Vec2_Magnitude(Vector2 a) {
	return SDL_sqrtf(a.x*a.x + a.y*a.y);
}

float
Vec2_MagnitudeSquared(Vector2 a) {
	return (a.x*a.x + a.y*a.y);
}

Vector2 
Vec2_Normalize(Vector2 a) {
	float mag = Vec2_Magnitude(a);
	a.x /= mag;
	a.y /= mag;
	return a;
}

Vector2 
Vec2_UnitVector(Vector2 a) {
	return Vec2_Normalize(a);
}

float 
Vec2_Dot(Vector2 a, Vector2 b) {
	return a.x * b.x + a.y * b.y;
}

float 
Vec2_Cross(Vector2 a, Vector2 b) {
	//perp dot product
	//https://www.sunshine2k.de/articles/Notes_PerpDotProduct_R2.pdf
	return a.x * b.y - a.y * b.x;
}

#endif
