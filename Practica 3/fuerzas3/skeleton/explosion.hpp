#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "force_generator.hpp"
#include "core.hpp"

class ParticleExplosion : public ParticleForceGenerator
{
	float strength;
	Vector3 origin;
	float radius;
public:
	ParticleExplosion(float _s, const Vector3& _o, float _r) :
		strength(_s), origin(_o), radius(_r) {}

	virtual void updateForce(Particle* particle, float t);
};

#endif