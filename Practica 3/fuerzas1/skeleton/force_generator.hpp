#ifndef __FORCE_GENERATOR_H__
#define __FORCE_GENERATOR_H__

class Particle;

class ParticleForceGenerator {
public:
	virtual void updateForce(Particle* particle, float t) = 0;
};
#endif

