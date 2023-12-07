#pragma once
#include "UniformParticleGenerator.h"
#include "PxPhysics.h"
#include "PxShape.h"
#include <PxPhysicsAPI.h>
class ParticleGenerator;
class MiniFirework_Generator :
    public UniformParticleGenerator
{
public:
    MiniFirework_Generator(PxScene* scene, PxPhysics* gPhysics);
    void setgenerator(ParticleGenerator* g);
private:
    PxScene* scene;
    PxPhysics* gPhysics;
    std::list<Particle*> generateParticles();
    ParticleGenerator* g;
};

