#pragma once
#include "ForceGenerator.h"
class BuyoancyForceGenerator :
    public ForceGenerator
{
public: 
    BuyoancyForceGenerator(float h, float v, float d, Vector3 pos);
    virtual void updateForce(Particle* particle, double duration) override;
    virtual void UpdateForce(Particle* particle, double duration) override;
    virtual ~BuyoancyForceGenerator();
protected:
    float height, volume, liquid_density, gravity;
    RenderItem* item;
    physx::PxTransform posicion;
};

