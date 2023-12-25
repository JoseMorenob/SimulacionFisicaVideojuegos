#include "SinusoidalForceGenerator.h"
#include <cmath>
#include <numbers>  // Necesario para std::numbers::pi
SinusoidalForceGenerator::SinusoidalForceGenerator(double amplitude, double frequency, double phaseOffset)
    : _amplitude(amplitude), _frequency(frequency), _phaseOffset(phaseOffset) {}

void SinusoidalForceGenerator::updateForce(Particle* particle, double t) {
    // Genera fuerza sinusoidal en el eje x
    double forceX = _amplitude * std::sin(2 * 3.1415 * _frequency * t + _phaseOffset);

    // Genera fuerza sinusoidal en el eje z
    double forceZ = _amplitude * std::sin(2 * 3.1415 * _frequency * t + _phaseOffset);

    // Aplica la fuerza a la part�cula
    particle->addForce(Vector3(forceX, 0.0, forceZ));
}

void SinusoidalForceGenerator::UpdateForce(Particle* particle, double t) {
    // En este ejemplo, la implementaci�n de UpdateForce es la misma que updateForce
    // Puedes personalizarla seg�n tus necesidades espec�ficas.
   // Genera fuerza sinusoidal en el eje x
    double forceX = _amplitude * std::cos(2 * 3.1415 * _frequency * t + _phaseOffset);

    // Genera fuerza sinusoidal en el eje z
    double forceZ = _amplitude * std::cos(2 * 3.1415 * _frequency * t + _phaseOffset);

    // Aplica la fuerza a la part�cula
    particle->AddForce(Vector3(forceX, 0.0, forceZ));
}
