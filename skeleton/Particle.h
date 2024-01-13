#pragma once
#include "PxPhysics.h"
#include "PxShape.h"
#include <PxPhysicsAPI.h>

#include "RenderUtils.hpp"
const float damping = 0.998;
using namespace physx;
class Particle
{
public:
    Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c,int size);
    Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c, PxScene* scene, PxPhysics* gPhysics,int size );
    Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c, physx::PxGeometry GEO, PxScene* scene, PxPhysics* gPhysics,int size );
    Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c, physx::PxGeometry GEO, int size);
    ~Particle();
    void CreateRigidDynamic(int size, Vector3 Pos, Vector4 color);
    bool integrate(float t);
    float gettimer();
    inline PxRigidDynamic* GetPxRigidDynamic() { return rigidDynamic; };
    inline void setTimer(float t) { timer = t; };
    inline void setVel(Vector3 v) { vel = v; };
    const inline Vector3 getVel() { return vel; };
    inline void setMasa(int m) { masa = m; };
    inline RenderItem* getRenderItem() { return renderItem; };
    inline PxShape* getShape() { return shape_ad; };
    inline PxTransform getTrans() { return currentTransform; };
   inline void setPos(Vector3 p) { currentTransform.p = PxVec3(p.x, p.y, p.z); };
    inline Vector3 GetPos() { return Vector3(currentTransform.p.x, currentTransform.p.y, currentTransform.p.z); }
    inline bool getCuhete() { return cuehete; };
    inline float getDuration()const {
        return duration;
    }

    inline void setDuration(float d) {
        duration = d;
    }
    inline float getMasa()const { return masa; }
    virtual Particle* clone() const;
    void AddForce(Vector3 const v) {
        if(rigidDynamic!=nullptr)rigidDynamic->addForce(v);
       
    }
    void SetLinearVelocity(Vector3 const v) {
        if (rigidDynamic != nullptr) rigidDynamic->setLinearVelocity(v);
    }
    void setRigid() {
        rigidDynamic = nullptr;
    }
    void release() {
        save->release();
    }
    // Type
    unsigned _type;
    // Add force to apply in the next integration only
    void addForce(const Vector3& f);
protected:
    float duration = 5.0f;
    bool cuehete;
    float timer = 0;
    int masa;
    RenderItem* renderItem;
    Vector3 ac;
    Vector3 vel;
    
    physx::PxRigidDynamic* rigidDynamic=nullptr;  // Cambiado de PxTransform a PxRigidDynamic
    physx::PxRigidDynamic* save = nullptr;
    Vector4 color;
    PxShape* shape_ad;
    // Accumulated force
    Vector3 force;
    PxScene* scene=nullptr; PxPhysics* gPhysics=nullptr;
    physx::PxTransform currentTransform;
    // Clears accumulated force
    void clearForce();
};
