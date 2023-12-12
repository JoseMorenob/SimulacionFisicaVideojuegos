#pragma once
#include "ForceGenerator.h"
class ExplosionForceGenerator :
    public ForceGenerator
{
public: 
    ExplosionForceGenerator(Vector3 inipos, Vector3 lado,float k,float tau);
    ~ExplosionForceGenerator() {

    }
    virtual void updateForce(Particle* p, double t);
    virtual void UpdateForce(Particle* p, double t);
protected:
    float calculateDistance(float x, float y, float z, float x_c, float y_c, float z_c);
    float r,k,tau;
    Vector3 inipos, lado;
};

