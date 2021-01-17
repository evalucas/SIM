#include "gravity.hpp"
#include "Particle.hpp"

void ParticleGravity::updateForce(PhysicsObject* particle, float t)
{
	PX_UNUSED(t);
	if (particle->hasInfiniteMass()) return;

	particle->addForce(g * particle->getMass());

}
