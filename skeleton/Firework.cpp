#include "Firework.h"
std::list<Particle*> Firework::explode() {
	_gens.front()->setOrigin(posicion.p);
	_gens.front()->setMeanVelocity(vel);
	return _gens.front()->generateParticles();
}
void Firework::addGenerator(ParticleGenerator* p) {
	_gens.push_back(std::shared_ptr<ParticleGenerator>(p));
}
Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c):Particle(Pos,Vel,aceler,mas,color,c) {

}
// Particle* Firework::clone() const {
//	 return static_cast<Particle>(&this);
//}