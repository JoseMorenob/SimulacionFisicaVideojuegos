#include "RigidBodySystem.h"
RigidBodySystem::RigidBodySystem(PxScene* scene, PxPhysics* gPhysics):scene(scene), gPhysics(gPhysics) {
	// PxScene * scene, PxPhysics* gPhysics, Vector3  pos, Vector3 size
	personaje = new SolidoDinamico(scene,gPhysics,{0,15,0},{2,2,2});
	particles.push_back(personaje);
}
RigidBodySystem::~RigidBodySystem() {
	auto c = particles.begin();
	while (c != particles.end()) {
		auto v = c;
		++c;
		onParticleDeath(*v);
	}
	
}
void RigidBodySystem::update(double t) {
	
}
	void RigidBodySystem::onParticleDeath(SolidoDinamico* p) {
			delete(p);
			particles.remove(p);



		}
void RigidBodySystem::explosion() {

}
void RigidBodySystem::generateFirework(unsigned firework_type) {

	float randomX = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; // Número aleatorio entre -1 y 1
	float randomY = 1; // Número aleatorio entre -1 y 1
	float randomZ = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; // Número aleatorio entre -1 y 1

	// Normaliza el vector para asegurarse de que tenga longitud 1
	physx::PxVec3 randomDirection(randomX, randomY, randomZ);
	randomDirection.normalize();
					//(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c, PxScene* scene, PxPhysics* gPhysi
	//Particle* p = new Particle({-100,30,-100}, randomDirection,{0,0,0},1,{0.5,0.3,0.3,1},0,scene,gPhysics);
	//p->SetLinearVelocity(randomDirection);
	//PxScene* scene, PxPhysics* gPhysics, Vector3  pos, Vector3 size
	SolidoDinamico* d = new SolidoDinamico(scene,gPhysics,{-100,30,-100},{2,2,2});
	d->setLinearVel(randomDirection);
	particles.push_back(d);
	

}



void RigidBodySystem::createFireworkSystem() {

}
void RigidBodySystem::generateSpringDemo() {

}
void RigidBodySystem::P4_ejercicio1() {

}