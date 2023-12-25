#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class SinusoidalForceGenerator : public ForceGenerator {
public:
    SinusoidalForceGenerator(double amplitude, double frequency, double phaseOffset);
    virtual void updateForce(Particle* particle, double t) override;
    virtual void UpdateForce(Particle* particle, double t) override;

    inline void setAmplitude(double amplitude) { _amplitude = amplitude; }
    inline void setFrequency(double frequency) { _frequency = frequency; }
    inline void setPhaseOffset(double phaseOffset) { _phaseOffset = phaseOffset; }

    virtual ~SinusoidalForceGenerator() {}

protected:
    double _amplitude;
    double _frequency;
    double _phaseOffset;
};

