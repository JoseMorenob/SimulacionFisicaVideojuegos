
#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator {
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);
	virtual void updateForce(Particle* particle,double t) override;
	inline void setk(double k) { _k = k; }
	virtual ~SpringForceGenerator() {

	}

protected:
	double _k; // Elastic Coeff.
	double _resting_length;
	Particle* _other;
	
};