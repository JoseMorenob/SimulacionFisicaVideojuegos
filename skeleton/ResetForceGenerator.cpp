//#include "ResetForceGenerator.h"
//void ResetForceGenerator::updateForce(Particle* particle, double t) {
//    Vector3 pos = particle->GetPos();
//
//    // A�adir fuerza cuando la posici�n en el eje y es inferior a -10
//    if (pos.y < -10.0) {
//        particle->addForce(Vector3(0, 1.0, 0));  // Puedes ajustar la magnitud y direcci�n seg�n sea necesario
//    }
//
//    // A�adir fuerza hacia el punto (0,0,0)
//    Vector3 forceTowardsOrigin = -pos.normalized();  // Direcci�n opuesta a la posici�n
//    particle->addForce(forceTowardsOrigin);
//
//    // Resto de tu c�digo para calcular la fuerza de arrastre
//    Vector3 vel_result = (f + particle->getVel());
//    Vector3 dragF = _k1 * vel_result + _k2 * vel_result * vel_result.magnitude();
//    particle->addForce(dragF);
// }
//void ResetForceGenerator::UpdateForce(Particle* particle, double t) {
//
//
// }