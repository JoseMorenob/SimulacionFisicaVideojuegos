#pragma once
#include "ParticleGenerator.h"
#include <random>
class GaussianParticleGenerator :
    public ParticleGenerator
{
public:
    GaussianParticleGenerator(PxScene* scene, PxPhysics* gPhysics);


public:
    PxScene* scene; PxPhysics* gPhysics;
    Vector3  dev_pos = Vector3(2, 2, 2);
    Vector3 dev_vel = Vector3(30, 40, 1);
    virtual std::list<Particle*> generateParticles();
    double generateGaussianValue(double mean, double stddev);
};

