#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(Vector3 f, Vector3 ini_pos, Vector3 tam, const float k1, const float k2):DragForceGenerator(k1,k2){
	this->f = f;
	porigen = ini_pos;
	lado = tam;
}
void WindForceGenerator::updateForce(Particle* particle, double t) {
	Vector3 pos = particle->GetPos();

	if ((pos.x >= porigen.x && pos.x <= porigen.x + lado.x) && (pos.y >= porigen.y && pos.y <= porigen.y + lado.y) && (pos.z >= porigen.z && pos.z <= porigen.z + lado.z)) {
		
		Vector3 vel_result = (f + particle->getVel());
		//compute drag force
		Vector3 dragF = _k1 * vel_result + _k2 * vel_result * vel_result.magnitude();
		particle->addForce(dragF);
	}
	else return;
 }