#pragma once
#include "PxPhysics.h"
#include "PxShape.h"

#include "RenderUtils.hpp"
const float damping = 0.998;
class Particle
{
public:
	Particle(Vector3 pos, Vector3 Velocity, Vector3 gravity, int masa, Vector4 color);
	void integrate(float t);
	float gettimer();

private:
	float timer = 0;
	int masa;
	Vector3 gravity;
	Vector3 velocity;
	physx::PxTransform posicion;
	RenderItem* renderItem;
};

