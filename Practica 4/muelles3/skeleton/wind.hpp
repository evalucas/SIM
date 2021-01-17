#ifndef __WIND_H__
#define __WIND_H__

#include "force_generator.hpp"
#include "core.hpp"

class ParticleWind : public ParticleForceGenerator
{
	Vector3 force;
	Vector3 origin;
	float radius;

public:
	ParticleWind(const Vector3& _f, const Vector3& _o, float _r) :
		force(_f), origin(_o), radius(_r) {}

	//virtual void updateForce(Particle* particle, float t);
};

#endif