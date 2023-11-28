#include "AnchoredSpringFG.h"
AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3 anchor_pos):SpringForceGenerator(k,resting,new Particle(anchor_pos,{0,0,0},{0,0,0},0,{0.0,0.0,0.0,0.0},0)), posicion(anchor_pos){

   item=new RenderItem(CreateShape(physx::PxBoxGeometry(3,3,3)), &posicion, Vector4(0.5,0.7,0.8,0.1));
}