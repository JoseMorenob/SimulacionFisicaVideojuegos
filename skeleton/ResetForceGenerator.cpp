//#include "ResetForceGenerator.h"
//void ResetForceGenerator::updateForce(Particle* particle, double t) {
//    Vector3 pos = particle->GetPos();
//
//    // Añadir fuerza cuando la posición en el eje y es inferior a -10
//    if (pos.y < -10.0) {
//        particle->addForce(Vector3(0, 1.0, 0));  // Puedes ajustar la magnitud y dirección según sea necesario
//    }
//
//    // Añadir fuerza hacia el punto (0,0,0)
//    Vector3 forceTowardsOrigin = -pos.normalized();  // Dirección opuesta a la posición
//    particle->addForce(forceTowardsOrigin);
//
//    // Resto de tu código para calcular la fuerza de arrastre
//    Vector3 vel_result = (f + particle->getVel());
//    Vector3 dragF = _k1 * vel_result + _k2 * vel_result * vel_result.magnitude();
//    particle->addForce(dragF);
// }
//void ResetForceGenerator::UpdateForce(Particle* particle, double t) {
//
//
// }