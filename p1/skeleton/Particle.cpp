#include "Particle.hpp"

Particle::Particle() 
{
	const physx::PxSphereGeometry geo(1);
	physx::PxShape* s = CreateShape(geo);
	physx::PxTransform* t = new physx::PxTransform(1, 1, 1);
	Vector4 c = { 0,255,0,255 };

	const RenderItem* particle = new RenderItem(s, t, c);
}

void Particle::integrate(float t)
{
	// Trivial case, infinite mass --> do nothing
	if (inverse_mass <= 0.0f) return;
	// Update position
	p += v * t;
	// Update linear velocity
	v += a * t;
	// Impose drag (damping)
	v *= powf(damping, t);
}