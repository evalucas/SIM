#ifndef __FORCE_GENERATOR_H__
#define __FORCE_GENERATOR_H__
#include "PxPhysicsAPI.h"

class PhysicsObject;

class ParticleForceGenerator {
public:
	virtual void updateForce(PhysicsObject* body, float t) = 0;

	virtual void upodate(float t) {}
};
#endif

