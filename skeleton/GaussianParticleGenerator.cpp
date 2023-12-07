#include "GaussianParticleGenerator.h"
double GaussianParticleGenerator::generateGaussianValue(double mean, double stddev) {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::normal_distribution<double> distribution(mean, stddev);
    return distribution(generator);
}

std::list<Particle*> GaussianParticleGenerator::generateParticles() {
    std::list<Particle*> particles;

    for (int i = 0; i < _n_particles; i++) {
        // Genera posiciones y velocidades muestreadas de una distribución gaussiana
        double x = generateGaussianValue(_origin.x, dev_pos.x);
        double y = generateGaussianValue(_origin.y, dev_pos.y);
        double z = generateGaussianValue(_origin.z, dev_pos.z);

        Vector3 position(x, y, z);

        double velX = generateGaussianValue(_mean_velocity.x, dev_vel.x);
        double velY = generateGaussianValue(_mean_velocity.y, dev_vel.y);
        double velZ = generateGaussianValue(_mean_velocity.z, dev_vel.z);

        Vector3 velocity(velX, velY, velZ);
   //                                  Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color
        Particle* newParticle = new Particle(position, velocity, gravity, 0.5, Vector4{ 0.6 , 0.1 , 1, 1 },0);
        newParticle->setDuration(20);



        particles.push_back(newParticle);
    }

    return particles;
}
    