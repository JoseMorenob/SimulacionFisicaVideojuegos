#pragma once
#include "ForceGenerator.h"
#include "Particle.h"
#include <cmath>

class RotateAroundPoint : public ForceGenerator {
public:
    RotateAroundPoint(const Vector3& rotationCenter, double rotationSpeed)
        : rotationCenter(rotationCenter), rotationSpeed(rotationSpeed) {}

    void updateForce(Particle* particle, double t) override {
        if (particle) {
            // Calcular el vector desde la partícula hasta el centro de rotación
            Vector3 toCenter = rotationCenter - particle->GetPos();

            // Calcular el ángulo de rotación en función del tiempo
            double angle = rotationSpeed * t;

            // Aplicar la rotación al vector toCenter
            double cosTheta = std::cos(angle);
            double sinTheta = std::sin(angle);

            double newX = cosTheta * toCenter.x - sinTheta * toCenter.z;
            double newZ = sinTheta * toCenter.x + cosTheta * toCenter.z;

            // Calcular la nueva posición después de la rotación
            Vector3 newPosition = rotationCenter - Vector3(newX, 0, newZ);

            // Establecer la nueva posición y orientación de la partícula
            PxTransform newTransform = PxTransform(PxVec3(newPosition.x, newPosition.y, newPosition.z));
           // particle->setGlobalPose(newTransform);
        }
    }
    void UpdateForce(Particle* particle, double t) override {
        float newX = rotationCenter.x + radius * cos(angle);
        float newZ = rotationCenter.z + radius * sin(angle);
        angle = PxPi / 2 + angle;
        PxTransform p = particle->getTrans();
        p.p.x = newX;
        p.p.z = newZ;
        newRotationAngle = atan2(newZ - rotationCenter.z, newX - rotationCenter.x);
        p.q = PxQuat(-newRotationAngle, PxVec3(0, 1, 0));
      
        particle->GetPxRigidDynamic()->setGlobalPose(p);
    }
private:
    Vector3 rotationCenter;
    double rotationSpeed;
    float radius = 5;
    float angle = 0,newRotationAngle=0;
};
