#include "Particle.h"
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color,int c): posicion(Pos) {
	masa = mas;
	ac = aceler;
	vel = Vel;
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2)), &posicion,color);
	_type = c;
}
void Particle::integrate(float t) {
	timer += t;
	vel += ac * t;
	vel *= pow(damping, t);
	posicion.p = posicion.p + (vel * t);
}
float Particle::gettimer() {
	return timer;
}