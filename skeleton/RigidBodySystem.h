#pragma once
#include "PxShape.h"
#include "PxPhysics.h"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <list>
#include "Firework.h"
#include "SolidoDinamico.h"
class RigidBodySystem
{
public:
	RigidBodySystem(PxScene* scene, PxPhysics* gPhysics);
	~RigidBodySystem();
	void update(double t);
	void explosion();
	void generateFirework(unsigned firework_type);
	void onParticleDeath(SolidoDinamico* p);
	void addPersonajeForce(Vector3 const v) { personaje->addForce(v); };
	void addPersonajeLinearForce(Vector3 const v) { personaje->setLinearVel(v); };

	void createFireworkSystem();
	void generateSpringDemo();
	void P4_ejercicio1();
protected:
	std::list<SolidoDinamico*> particles;
	PxScene* scene; PxPhysics* gPhysics;
	SolidoDinamico* personaje;


};

