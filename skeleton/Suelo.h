	#pragma once
	#include "PxShape.h"
	#include "PxPhysics.h"
	#include "RenderUtils.hpp"

	using namespace physx;
	class Suelo
	{
	public:
		Suelo(Vector3 pos,Vector4 size, PxScene* scene, PxPhysics* gPhysics);
		virtual ~Suelo();
		PxRigidStatic* suelo;
	protected:
		Vector4 s;
		RenderItem* t;
		physx::PxTransform posicion;
		PxScene* scene;
	
	};

