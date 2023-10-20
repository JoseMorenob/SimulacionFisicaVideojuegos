#pragma once
#include "ParticleGenerator.h"
class UniformParticleGenerator :
    public ParticleGenerator
{
public:
    Vector3 vel_width = Vector3(5, 5, 5);
    Vector3 pos_width = Vector3(4, 4, 4);
private:
    double UniformParticleGenerator::generateUniformValue(double range);
    std::list<Particle*> generateParticles();

};

