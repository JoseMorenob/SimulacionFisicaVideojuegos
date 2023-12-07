#include "SolidoDinamico.h"
SolidoDinamico::SolidoDinamico( PxScene* scene, PxPhysics* gPhysics,Vector3  pos,Vector3 size) : posicion(pos), size(size) {
	// Añadir un actor dinámico
	
	new_solid = gPhysics->createRigidDynamic(posicion); 
	new_solid->setLinearVelocity({ 0,5,0 });
	new_solid->setAngularVelocity({ 0,0,0 });
	PxShape* shape_ad = CreateShape(PxBoxGeometry(size)); 
	new_solid->attachShape(*shape_ad);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, 0.15);
	scene->addActor(*new_solid);
	// Pintar actor dinámico

	t = new RenderItem(shape_ad, new_solid, { 0.8, 0.8, 0.8, 1 });

}
SolidoDinamico::~SolidoDinamico(){
	DeregisterRenderItem(t);
}