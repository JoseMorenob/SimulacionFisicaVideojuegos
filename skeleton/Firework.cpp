#include "Firework.h"
std::list<Particle*> Firework::explode() {
	
	_gens.front()->setMeanVelocity(vel);
	_gens.front()->setOrigin(currentTransform.p);
	//_gens.front()->setParticle(clone());
	std::list<Particle*> parts;
	std::list<Particle*> parts_;
	for (auto c : _gens) {
		parts = c->generateParticles();
		for (auto p : parts) {
			parts_.push_back(p);
		}
	}
	return parts_;


}
void Firework::addGenerator(ParticleGenerator* p) {
	_gens.push_back(std::shared_ptr<ParticleGenerator>(p));
}
Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c,int size):Particle(Pos,Vel,aceler,mas,color,c,size) {

}
Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c, PxScene* scene, PxPhysics* gPhysics,int size) :Particle(Pos, Vel, aceler, mas, color, c,scene,gPhysics,size) {

}
