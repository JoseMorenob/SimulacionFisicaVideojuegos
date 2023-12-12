#pragma once
#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, Particle*> FRPair;
class ParticleForceRegistry:public std::multimap<ForceGenerator*,Particle*>	 {
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); ++it) {
			if (it->second->GetPxRigidDynamic() != nullptr) {
				it->first->UpdateForce(it->second, duration);
			}
			else {
				it->first->updateForce(it->second, duration); 
			}
		}
	}	

	void addRegistry(ForceGenerator* fg, Particle* p) {
		
		emplace(fg, p);
		//emplace({fg,p});
	}
	void deleteParticleRegistry(ForceGenerator* P) {

		erase(P);
		
	}
};