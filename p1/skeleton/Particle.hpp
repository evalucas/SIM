
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "core.hpp"

class Particle
{
private:
	// Position in world space
	Vector3 p;
	// Linear velocity in world space
	Vector3 v;
	// Linear acceleration in world space
	Vector3 a;

	float damping;

	float inverse_mass;
public:
	void integrate(float t);
	Particle();
};


