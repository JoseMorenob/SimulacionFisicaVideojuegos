#pragma once
#include "PxPhysics.h"
#include "PxShape.h"

#include "RenderUtils.hpp"
const float damping = 0.998;
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel,Vector3 aceler, int mas,Vector4 color,int c);
	bool integrate(float t);
	float gettimer();
	inline void setTimer(float t) { timer = t; };
	inline void setVel(Vector3 v) { vel = v; };
	const inline Vector3 getVel() { return vel; };
	inline void setPos(Vector3 p) { posicion.p = p; };
	inline Vector3 GetPos() { return posicion.p; }
	inline bool getCuhete() { return cuehete; };
	inline float getDuration()const {
		return duration;
	}
	
	inline void setDuration(float d) {
		duration = d;
	}
	inline float getMasa()const { return masa; }
	 virtual Particle* clone() const;
	 ~Particle();
	   // Type
	unsigned _type;
	// Add force to apply in next integration only
	void addForce(const Vector3& f);
protected:
	float duration = 95.0f;
	bool cuehete;
	float timer=0;
	int masa;
	Vector3 ac;
	Vector3 vel;
	physx::PxTransform posicion;
	RenderItem* renderItem;// desregistrar el objeto
	Vector4 color;
	//Accumulated force
	Vector3 force;
	// Clears accumulated force
	void clearForce();


};

