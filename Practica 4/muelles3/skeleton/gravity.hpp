#ifndef __GRAVITY_H__
#define __GRAVITY_H__

#include "force_generator.hpp"
#include "core.hpp"

class ParticleGravity : public ParticleForceGenerator
{

	Vector3 g;

public:
	ParticleGravity(const Vector3& gravity) : g(gravity) {}
	virtual void updateForce(Particle* particle, float f);
};



#endif