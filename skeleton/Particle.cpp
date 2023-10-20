#include "Particle.h"
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color,int c): posicion(Pos) {
	masa = mas;
	ac = aceler;
	vel = Vel;
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2)), &posicion,color);
	_type = c;
	this->color = color;
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
Particle* Particle::clone()const {
	//Vector3 Pos, Vector3 Vel,Vector3 aceler, int mas,Vector4 color,int c
	return new Particle(posicion.p,vel,ac,masa,color,_type);

}
// Destructor de la clase Particle
Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}
