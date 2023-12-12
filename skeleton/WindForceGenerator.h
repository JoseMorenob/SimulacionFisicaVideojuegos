#pragma once
#include "DragForceGenerator.h"
class WindForceGenerator :
    public DragForceGenerator
{
public:
    WindForceGenerator(Vector3 f, Vector3 ini_pos, Vector3 tam, const float k1, const float k2);
    virtual void updateForce(Particle* particle, double t) override;
    virtual void UpdateForce(Particle* particle, double t) ;
protected:
    Vector3 porigen, lado;
    Vector3 f;
};

