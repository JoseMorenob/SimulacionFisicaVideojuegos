#include "GravityForceGenerator.h"
GravityForceGenerator::GravityForceGenerator(const Vector3& g) {
	gravity = g;
}
void GravityForceGenerator::updateForce(Particle* p, double t) {
	
	p->addForce(gravity * p->getMasa());
 }
void GravityForceGenerator::UpdateForce(Particle* p, double t) {

	p->AddForce(gravity * p->getMasa());
}
void GravityForceGenerator::setGravity(const Vector3& g) {
	gravity = g;
 }
GravityForceGenerator::~GravityForceGenerator() {

}