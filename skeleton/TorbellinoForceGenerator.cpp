#include "TorbellinoForceGenerator.h"

TorbellinoForceGenerator::TorbellinoForceGenerator(Vector3 f, Vector3 ini_pos, Vector3 tam, const float k1, const float k2): WindForceGenerator(f,ini_pos,tam,k1,k2) {

}

void TorbellinoForceGenerator::updateForce(Particle* p, double t) {
	Vector3 pp = p->GetPos();
	Vector3 vel_tb;
	vel_tb.x = 0.5 * _k1 * (-(pp.z - porigen.z));  // Ajusta el factor multiplicativo (0.5 en este caso)
	vel_tb.y = 0.5 * _k1 * (50 - (pp.y - porigen.y));  // Ajusta el factor multiplicativo (0.5 en este caso)
	vel_tb.z = 0.5 * _k1 * (pp.x - porigen.x);  // Ajusta el factor multiplicativo (0.5 en este caso)

	Vector3 v = p->getVel() - vel_tb;
	float drag_coef = v.normalize();
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	Vector3 dragF = -v * drag_coef;

	p->addForce(dragF);

 }
void TorbellinoForceGenerator::UpdateForce(Particle* p, double t) {
	Vector3 pp = p->GetPos();
	Vector3 vel_tb;
	vel_tb.x = 0.5 * _k1 * (-(pp.z - porigen.z));  // Ajusta el factor multiplicativo (0.5 en este caso)
	vel_tb.y = 0.5 * _k1 * (50 - (pp.y - porigen.y));  // Ajusta el factor multiplicativo (0.5 en este caso)
	vel_tb.z = 0.5 * _k1 * (pp.x - porigen.x);  // Ajusta el factor multiplicativo (0.5 en este caso)

	Vector3 v = p->getVel() - vel_tb;
	float drag_coef = v.normalize();
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	Vector3 dragF = -v * drag_coef;

	p->AddForce(dragF);

}