#include "Suelo.h"
Suelo::Suelo(Vector3 pos, Vector4 size, PxScene* scene,PxPhysics* gPhysics, Vector4 color) : posicion(pos),s(size),scene(scene) {
	// Generar suelo
	 suelo = gPhysics->createRigidStatic(posicion); 
	 PxShape* shape = CreateShape(PxBoxGeometry(size.x,size.y,size.z));
	suelo->attachShape(*shape);
	scene->addActor(*suelo);
	t = new RenderItem(shape, suelo,color);

}
Suelo::~Suelo() {
	DeregisterRenderItem(t);
}