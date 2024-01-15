#include "UniformParticleGenerator.h"
#include <random>

double UniformParticleGenerator::generateUniformValue(double range) {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(-range / 2, range / 2);

    return distribution(generator);
}

std::list<Particle*> UniformParticleGenerator::generateParticles() {
    std::list<Particle*> particles;

    for (int i = 0; i < _n_particles; i++) {
        double x = _origin.x + generateUniformValue(pos_width.x);
        double y = _origin.y + generateUniformValue(pos_width.y);
        double z = _origin.z + generateUniformValue(pos_width.z);

        double velX = _mean_velocity.x + generateUniformValue(vel_width.x);
        double velY = _mean_velocity.y + generateUniformValue(vel_width.y);
        double velZ = _mean_velocity.z + generateUniformValue(vel_width.z);

        Vector3 position(x, y, z);
        Vector3 velocity(velX, velY, velZ);

        Particle* newParticle = new Particle(position, velocity, gravity, 2, Vector4{0.125,0.129,0.122,0.702 }, 0,2);
        particles.push_back(newParticle);
    }
   

    return particles;
}
