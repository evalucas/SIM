#ifndef _RIGIDBODY_SYSTEM_H_
#define _RIGIDBODY_SYSTEM_H_

#include "core.hpp"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"

class RigidBodySystem
{
private:
	void createNewRigidbody();
public:
	RigidBodySystem();
	~RigidBodySystem();

	void update(float t);

	float generation_rate;

	float time_for_next_body;

	Vector3 position;
	float minPos;
	float maxPos;

	float max;
};

#endif
