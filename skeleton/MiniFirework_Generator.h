#pragma once
#include "UniformParticleGenerator.h"
class ParticleGenerator;
class MiniFirework_Generator :
    public UniformParticleGenerator
{
public:
    void setgenerator(ParticleGenerator* g);
private:
    std::list<Particle*> generateParticles();
    ParticleGenerator* g;
};

