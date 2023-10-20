#pragma once
#include "PxPhysics.h"
#include "PxShape.h"
#include "RenderUtils.hpp"
#include <random>
#include "Particle.h"
#include <list>
class ParticleGenerator
{
public:
	virtual std::list<Particle*> generateParticles() = 0;
	inline void setOrigin(const Vector3& p) { _origin = p; }
	inline void setMeanVelocity(const Vector3& v) {
		_mean_velocity
			= v;
	}
	inline Vector3 getMeanVelocity() const {
		return _mean_velocity;
	}
	inline void setMeanDuration(double new_duration) {
		_model_particle->setTimer(new_duration);
	}
	//! @brief --> sets the particle, including its type, lifetime 
	//and mean positions and velocities
		inline void setParticle(Particle* p, bool modify_pos_vel =
			true) {
		delete (_model_particle);
		_model_particle = p->clone();
		if (modify_pos_vel) {
			_origin = p->GetPos();
			_mean_velocity = p->getVel();
		}
		_model_particle->setPos({ -1000.0f, -1000.0f, -1000.0f });
	}
		inline void setNParticles(int n_p) {
			_n_particles = n_p;
		}
		inline void setGravity(const  Vector3& v) { gravity = v; };
protected:
	int _n_particles = 15; // Number of particles for each 
	//generateParticles call(TODO: add randomness ? ? )
		double _generation_prob = 1.0; // IF 1.0 --> always produces 
	//particles
		Particle* _model_particle = nullptr; // Has the attributes of 
	//the particle that will be generated!(damping, lifetime, etc.)
		Vector3 gravity;
		Vector3 _origin, _mean_velocity;
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _u{ 0,1 };
	std::string _name;

};

