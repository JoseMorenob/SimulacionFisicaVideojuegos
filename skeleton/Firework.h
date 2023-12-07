#pragma once
#include "Particle.h"
#include <list>
#include "ParticleGenerator.h"

class Firework :
    public Particle
{
public:
    // The firework generates more fireworks when exploding --> 
   // they should be gathered by the System
    Firework(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c);
    Firework(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c, PxScene* scene, PxPhysics* gPhysics);
     std::list<Particle*> explode();
    void addGenerator(ParticleGenerator* p);
   
  
protected:

  
    std::list<std::shared_ptr<ParticleGenerator> > _gens;
};



