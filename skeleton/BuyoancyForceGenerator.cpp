#include "BuyoancyForceGenerator.h"

BuyoancyForceGenerator::BuyoancyForceGenerator(float h, float v, float d,Vector3 pos) : height(h),volume(v),liquid_density(d),posicion(pos) {
	item = new RenderItem(CreateShape(physx::PxBoxGeometry(h, 20, h)), &posicion, Vector4(0.5, 0.7, 0.8, 0.1));
}
void BuyoancyForceGenerator::updateForce(Particle* particle, double duration) {
	float h = particle->GetPos().y;
	float h0 =posicion.p.y;

	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > height * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h > height * 0.5) {
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / height + 0.5;
	}
	f.y = liquid_density * volume * immersed * 9.8;
	particle->addForce(f);
}
BuyoancyForceGenerator::~BuyoancyForceGenerator() {

 }