#include "Particle.h"
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color,int c): posicion(Pos) {
	masa = mas;
	ac = aceler;
	force = Vector3(0, 0, 0);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2)), &posicion,color);
	_type = c;
	vel =Vel;
	this->color = color;
}
void Particle::addForce(const Vector3& f) {
	force += f;
}
void  Particle::clearForce() {
	force *= 0.0f;
}

bool Particle::integrate(float t) {
	// Get the accel considering the force accum
	Vector3 resulting_accel = force * masa;
	vel += resulting_accel * t; // Ex. 1.3 --> add  acceleration
	vel *= powf(damping, t); // Exercise 1.3 --> add
	
	posicion.p += vel * t;
	duration -= t;
	// Clear accum
	clearForce();
	return duration < 0.0;

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