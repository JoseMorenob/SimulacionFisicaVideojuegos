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
class ParticleSystem
{
public:
	// Creates a void system with a det. gravity
	ParticleSystem(const Vector3 & g = { 0.0f, -9.8f, 0.0f});
	~ParticleSystem();
	// Integrates the particles and checks for its lifetime, 
	void update(double t);
	void generateFirework(unsigned firework_type);
	// Gets a particle generator with name...
	ParticleGenerator* getParticleGenerator(const std::string& n);
protected:
	std::list <Particle*> _particles;
	std::list <ParticleGenerator*> _particle_generators; // 
//	These are the registred generators(for on demand set
	//	generation prob.to 0
	GaussianParticleGenerator* _firework_generator; // This 
	UniformParticleGenerator* g2;
	GaussianParticleGenerator* g3;
	MiniFirework_Generator* fire;
//	generator is only to shoot the firework!!
	Vector3 _gravity;
	std::vector<Firework*> _firework_pool; // Fireworks to 
	//be used as models!
		//! This is used currently in the Fireworks to spread 
	//	more Fireworks!
	void onParticleDeath(Particle * p);
	void createFireworkSystem();

};

