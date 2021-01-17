
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
	physx::PxTransform* tr = nullptr;
	
public:
	void integrate(float t);
	Particle(physx::PxTransform* T, Vector3 V, Vector3 A, float d,float inv)
		:tr(T), v(V), a(A), damping(d), inverse_mass(inv) {};
};


