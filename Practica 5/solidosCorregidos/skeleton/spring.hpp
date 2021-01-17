#ifndef __SPRING_H__
#define __SPRING_H__
#include "force_generator.hpp"
#include "Particle.hpp"

class ParticleSpring : public ParticleForceGenerator
{
	Particle* other;

	float k;
	float restLength;

public:
	ParticleSpring(Particle* _other, float _k, float _restLength);
	//virtual void updateForce(Particle* particle, float f);

	float getElasticity() const { return k; }
	void setElasticity(float _k) { k = _k; }
};

class ParticleAnchoredSpring : public ParticleForceGenerator {
	Vector3* anchor;

	float k;
	float restLength;

public:
	ParticleAnchoredSpring(Vector3* _other, float _k, float _restLength);
	//virtual void updateForce(Particle* particle, float f);

	float getElasticity() const { return k; }
	void setElasticity(float _k) { k = _k; }
};

#endif