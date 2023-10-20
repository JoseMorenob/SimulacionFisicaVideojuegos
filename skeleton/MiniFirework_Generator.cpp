#include "MiniFirework_Generator.h"
#include "Firework.h"
#include "ParticleGenerator.h"
std::list<Particle*> MiniFirework_Generator::generateParticles() {
    std::list<Particle*> particles;

    for (int i = 0; i < _n_particles/2; i++) {
        double x = _origin.x + generateUniformValue(pos_width.x);
        double y = _origin.y + generateUniformValue(pos_width.y);
        double z = _origin.z + generateUniformValue(pos_width.z);

        double velX = _mean_velocity.x + generateUniformValue(vel_width.x);
        double velY = _mean_velocity.y + generateUniformValue(vel_width.y);
        double velZ = _mean_velocity.z + generateUniformValue(vel_width.z);

        Vector3 position(x, y, z);
        Vector3 velocity(velX, velY, velZ);

        Firework* newParticle = new Firework(position, velocity, gravity, 2, Vector4{ 0.3 , 0.3 , 0.4, 1 }, 2);
        newParticle->setDuration(0.5);
        newParticle->setTimer(0);
        newParticle->addGenerator(g);
        particles.push_back(newParticle);
    }


    return particles;
}
void MiniFirework_Generator::setgenerator(ParticleGenerator* g) {
    this->g = g;
}