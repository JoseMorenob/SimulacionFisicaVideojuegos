#include "Particula.h"

Particle::Particle(Vector3 Pos, Vector3 velocity, Vector3 gravity, int masa, Vector4 color) : posicion(Pos) {
	this->masa = masa;
	this->gravity = gravity;
	this->velocity = velocity;
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(4)), &posicion, color);
}
void Particle::integrate(float t) {
	timer += t;
	velocity += gravity * t;
	velocity *= pow(damping, t);
	posicion.p = posicion.p + (gravity * t);//p=po+ac*t
}
float Particle::gettimer() {
	return timer;
}