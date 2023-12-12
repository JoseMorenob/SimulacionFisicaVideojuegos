#pragma once
#include "WindForceGenerator.h"
class TorbellinoForceGenerator :
    public WindForceGenerator
{
public:
    TorbellinoForceGenerator(Vector3 f, Vector3 ini_pos, Vector3 tam, const float k1, const float k2);
    ~TorbellinoForceGenerator() {

    }
    virtual void updateForce(Particle* p, double t);
    virtual void UpdateForce(Particle* p, double t);

protected:
};

