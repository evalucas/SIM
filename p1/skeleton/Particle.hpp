
#include "PxPhysicsAPI.h"
#include "core.hpp"

class Particle
{
	// Position in world space
	Vector3 p;
	// Linear velocity in world space
	Vector3 v;
	// Linear acceleration in world space
	Vector3 a;

	float damping;

	float inverse_mass;

	void integrate(float t);
};


