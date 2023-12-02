#pragma once
#include "PxPhysics.h"
#include "PxShape.h"
#include "RenderUtils.hpp"
#include "ParticleGenerator.h"
#include <list>
#include "Particle.h"
#include "Firework.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "MiniFirework_Generator.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"
#include "ForceGenerator.h"
#include "WindForceGenerator.h"
#include "TorbellinoForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "BuyoancyForceGenerator.h"
class ParticleSystem
{
public:
	// Creates a void system with a det. gravity
	ParticleSystem(const Vector3 & g = { 0.0f, -9.8f, 0.0f});
	~ParticleSystem();
	// Integrates the particles and checks for its lifetime, 
	void update(double t);
	void explosion();
	void generateFirework(unsigned firework_type);
	// Gets a particle generator with name...
	ParticleGenerator* getParticleGenerator(const std::string& n);

	void createFireworkSystem();
	void generateSpringDemo();
	void P4_ejercicio1();
	void setK(double k) {
		anche->setk(k);
	}
	void P4_ejercicio3();
	void setMasaParticulaagua(int d) { pl->setMasa(6); };
protected:
	AnchoredSpringFG* anche;
	ParticleForceRegistry* force_registry;
	std::list <Particle*> _particles;
	std::list <ParticleGenerator*> _particle_generators; // 
	std::list<Particle*> explosion_parts;
//	These are the registred generators(for on demand set
	//	generation prob.to 0
	GaussianParticleGenerator* _firework_generator; // This 
	UniformParticleGenerator* g2;
	GaussianParticleGenerator* g3;
	MiniFirework_Generator* fire;
	GravityForceGenerator* gr;
	ExplosionForceGenerator* eg;
	std::vector<ForceGenerator*> fg;
	WindForceGenerator* wf;
	BuyoancyForceGenerator* buyoancy;
//	generator is only to shoot the firework!!
	Vector3 _gravity;
	TorbellinoForceGenerator* tg;
	std::vector<Firework*> _firework_pool; // Fireworks to 
	//be used as models!
		//! This is used currently in the Fireworks to spread 
	//	more Fireworks!
	void onParticleDeath(Particle * p);
	Particle* pl;


};

