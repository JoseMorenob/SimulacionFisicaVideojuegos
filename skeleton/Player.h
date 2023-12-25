#pragma once
#include <list>
#include "Firework.h"
#include "ParticleGenerator.h"
#include <PxPhysicsAPI.h>
class ParticleSystem;
class Player: public Firework
{
public:
	Player(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c , PxScene* scene, PxPhysics* gPhysics, ParticleGenerator* g,ParticleSystem* ps);
	~Player() {

	};
	virtual    bool integrate(float t);
protected:
	ParticleSystem* ps;
};

