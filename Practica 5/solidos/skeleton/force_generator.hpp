#ifndef __FORCE_GENERATOR_H__
#define __FORCE_GENERATOR_H__
#include "PxPhysicsAPI.h"


class BodyForceGenerator {
public:
	virtual void updateForce(physx::PxRigidBody* body, float t) = 0;
};
#endif

