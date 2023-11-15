#include "TorbellinoForceGenerator.h"

TorbellinoForceGenerator::TorbellinoForceGenerator(Vector3 f, Vector3 ini_pos, Vector3 tam, const float k1, const float k2): WindForceGenerator(f,ini_pos,tam,k1,k2) {

}

void TorbellinoForceGenerator::updateForce(Particle* p, double t) {
	Vector3 pp = p->GetPos();
	Vector3 vel_tb;
	vel_tb.x = _k1 *(-(pp.z - porigen.z));
	vel_tb.y = _k1 * (50 - (pp.y - porigen.y));
	vel_tb.z= _k1 *(pp.x - porigen.x);
	Vector3 v = p->getVel() - vel_tb;
	float drag_coef = v.normalize();
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	Vector3 dragF = -v * drag_coef;//determinan la dirección y magnitud de la fuerza de arrastre resultante.

	p->addForce(dragF);
	

 }