#include "Particle.h"
#include <iostream>

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c, int size) :masa(mas), ac(aceler), force(Vector3(0, 0, 0)), _type(c), vel(Vel), color(color), scene(nullptr), gPhysics(nullptr), currentTransform(Pos) {
    renderItem = new RenderItem(CreateShape(PxSphereGeometry(size)), &currentTransform, color);
    //new RenderItem(CreateShape(physx::PxBoxGeometry(3,3,3)), &posicion, Vector4(0.5,0.7,0.8,0.1));
//RegisterRenderItem(renderItem);

}
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c, physx::PxGeometry GEO, int size) :masa(mas), ac(aceler), force(Vector3(0, 0, 0)), _type(c), vel(Vel), color(color), scene(nullptr), gPhysics(nullptr), currentTransform(Pos) {
    renderItem = new RenderItem(CreateShape(PxBoxGeometry(size, size, size)), &currentTransform, color);
    // RegisterRenderItem(renderItem);

}
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c, PxScene* scene, PxPhysics* gPhysics, int size) : masa(mas), ac(aceler), force(Vector3(0, 0, 0)), _type(c), vel(Vel), color(color), scene(scene), gPhysics(gPhysics), currentTransform(Pos) {
    this->scene = scene;
    this->gPhysics = gPhysics;
    std::cout << size << std::endl;
    CreateRigidDynamic(size, Pos, color);
    save = rigidDynamic;
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c, physx::PxGeometry GEO, PxScene* scene, PxPhysics* gPhysics, int size) : masa(mas), ac(aceler), force(Vector3(0, 0, 0)), _type(c), vel(Vel), color(color), scene(scene), gPhysics(gPhysics), currentTransform(Pos) {
    this->scene = scene;
    this->gPhysics = gPhysics;
    std::cout << size << std::endl;
    CreateRigidDynamic(size, Pos, color);
    save = rigidDynamic;
}

void Particle::CreateRigidDynamic(int size, Vector3 Pos, Vector4 color) {
    // Configurar el cuerpo dinámico
    rigidDynamic = gPhysics->createRigidDynamic(currentTransform);
    rigidDynamic->setLinearVelocity({ 0,5,0 });
    rigidDynamic->setAngularVelocity({ 0,0,0 });
    shape_ad = CreateShape(PxSphereGeometry(size));
 
    rigidDynamic->attachShape(*shape_ad);

    PxRigidBodyExt::updateMassAndInertia(*rigidDynamic, 0.15);
    scene->addActor(*rigidDynamic);
    // Pintar actor dinámico

   // t = new RenderItem(shape_ad, new_solid, { 0.8, 0.8, 0.8, 1 });
    renderItem = new RenderItem(shape_ad, rigidDynamic, color);

    // RegisterRenderItem(renderItem);
}

void Particle::addForce(const Vector3& f) {
    force += f;
}

void Particle::clearForce() {
    force *= 0.0f;
}

bool Particle::integrate(float t) {
    // Obtener la aceleración considerando la acumulación de fuerzas
    Vector3 resulting_accel = force * masa;
    vel += resulting_accel * t;
    vel *= powf(damping, t);

    if (rigidDynamic != nullptr) {
        //Vector3 linearVelocity(vel.x, vel.y, vel.z);
        //rigidDynamic->setLinearVelocity(linearVelocity);
        //
        //// Actualizar la posición basada en la velocidad
        currentTransform = rigidDynamic->getGlobalPose();
        //physx::PxTransform newTransform = physx::PxTransform(currentTransform.p + linearVelocity * t, currentTransform.q);
        //rigidDynamic->setGlobalPose(newTransform);
    }
    else {
        currentTransform.p += vel * t;
        duration -= t;
    }
    // Aplicar la velocidad al cuerpo dinámico


    duration -= t;
    clearForce();
    return duration < 0.0;
}

float Particle::gettimer() {
    return timer;
}

Particle* Particle::clone() const {
    // Aquí puedes decidir si deseas implementar o no la función de clonación
    // return new Particle(posicion.p, vel, ac, masa, color, _type);
    return nullptr;  // O simplemente devolver nullptr
}

Particle::~Particle() {

    //if (gPhysics != nullptr ) {
    //    scene->removeActor(*rigidDynamic);
    //    rigidDynamic->release();
    //   // delete(renderItem);
    //}

    //if (renderItem != nullptr) {
    //    DeregisterRenderItem(renderItem);
    //    delete(renderItem);
    //    renderItem = nullptr;
    //}


}
