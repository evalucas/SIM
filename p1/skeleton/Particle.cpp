#include "Particle.hpp"

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