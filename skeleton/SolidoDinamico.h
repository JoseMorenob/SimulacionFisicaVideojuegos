#pragma once
#include "PxShape.h"
#include "PxPhysics.h"
#include "RenderUtils.hpp"

using namespace physx;
class SolidoDinamico
{
public:
	SolidoDinamico(PxScene* scene, PxPhysics* gPhysics, Vector3  pos, Vector3 size);
	~SolidoDinamico();
	inline void setLinearVel(Vector3 const v) { new_solid->setLinearVelocity(v); };
	inline void addForce(Vector3 const v) { new_solid->addForce(v); };
	inline void addTorque(Vector3 const v) { new_solid->addTorque(v); };
	
protected:
	
	Vector3 size;
	PxRigidDynamic* new_solid;
	RenderItem* t;
	physx::PxTransform posicion;
};

