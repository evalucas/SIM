#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "force_generator.hpp"
#include "core.hpp"

class BodyExplosion : public BodyForceGenerator
{
	float strength;
	Vector3 origin;
	float radius;
public:
	BodyExplosion(float _s, const Vector3& _o, float _r) :
		strength(_s), origin(_o), radius(_r) {}

	virtual void updateForce(physx::PxRigidBody* body, float t);
};

#endif