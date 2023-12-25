#include "AnchoredSpringFG.h"
AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3 anchor_pos, PxScene* scene, PxPhysics* gPhysics):SpringForceGenerator(k,resting,new Particle(anchor_pos,{0,0,0},{0,0,0},0,{0.0,0.0,0.0,0.0},0,2)), posicion(anchor_pos){



   item=new RenderItem(CreateShape(physx::PxBoxGeometry(3,3,3)), &posicion, Vector4(0.5,0.7,0.8,0.1));
  /* if (_other->GetPxRigidDynamic() != nullptr) {
	   _other->GetPxRigidDynamic()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);

   }*/
}