#include "Player.h"
#include "ParticleSystem.h"
Player::Player(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c , PxScene* scene, PxPhysics* gPhysics, ParticleGenerator* g,ParticleSystem* ps) : Firework(Pos, Vel, aceler, mas, color, c, scene, gPhysics,2),ps(ps) {

    
    //rigidDynamic->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
    g->setMeanVelocity({ -200,0,-200 });
    
    g->setNParticles(1);
    addGenerator(g);
}

bool Player::integrate(float t) {
  bool c=  Particle::integrate(t);
  for (auto c : _gens) {
      c->setOrigin(currentTransform.p-Vector3(2,0,2));
     std:: list<Particle*> lt= c->generateParticles();
     ps->addParticles(lt);

  }

  return c;


}