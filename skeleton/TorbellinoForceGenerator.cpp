#include "TorbellinoForceGenerator.h"

TorbellinoForceGenerator::TorbellinoForceGenerator(Vector3 f, Vector3 ini_pos, Vector3 tam, const float k1, const float k2): WindForceGenerator(f,ini_pos,tam,k1,k2) {

}
TorbellinoForceGenerator::~TorbellinoForceGenerator() {

}
void TorbellinoForceGenerator::updateForce(Particle* p, double t) {

	Vector3 vel_t;
	Vector3 part_pos=p->GetPos();
	//t.x=-(part_pos.z-ini)




 }