#include "Suelo.h"
Suelo::Suelo(Vector3 pos, Vector4 size, PxScene* scene,PxPhysics* gPhysics) : posicion(pos),s(size),scene(scene) {
	// Generar suelo
	 suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 })); 
	 PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo->attachShape(*shape);
	scene->addActor(*suelo);
	t = new RenderItem(shape, suelo, size);
}
Suelo::~Suelo() {
	DeregisterRenderItem(t);
}