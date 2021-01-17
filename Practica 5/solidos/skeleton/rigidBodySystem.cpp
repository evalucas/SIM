#include "rigidBodySystem.hpp"
#include "core.hpp"

extern void AddBody(physx::PxRigidBody* body);
extern void CreateBody(physx::PxTransform* t);

RigidBodySystem::RigidBodySystem() : time_for_next_body(0.0f)
{
	position = Vector3(0.0f, 70.0f, 0.0f);

	minPos = -50.0f;
	maxPos = 50.0f;

	generation_rate = 0.5f;
	max = 20;
}

RigidBodySystem::~RigidBodySystem()
{

}

float randomf(float _min, float _max) {

	float r = static_cast<float>(std::rand()) / RAND_MAX;
	r *= (_max - _min);
	r += _min;

	return r;
}


void RigidBodySystem::update(float t)
{
	time_for_next_body -= t;
	if (time_for_next_body < 0.0f && max > 0) {

		createNewRigidbody();
		time_for_next_body += generation_rate;
		max -= 1;
	}
}


void RigidBodySystem::createNewRigidbody()
{
	position.x = randomf(minPos, maxPos);
	position.z = randomf(minPos, maxPos);

	physx::PxTransform bodyTransform(position);
	CreateBody(&bodyTransform);
}

