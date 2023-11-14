#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class GravityForceGenerator :
    public ForceGenerator
{
public:
    GravityForceGenerator(const Vector3& g);
    virtual void updateForce(Particle* p, double t);
    inline void setGravity(const Vector3& g);
    ~GravityForceGenerator();
protected:
    Vector3 gravity;
};

