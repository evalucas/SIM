#include "explosion.hpp"
#include "Particle.hpp"

void ParticleExplosion::updateForce(Particle* particle, float t)
{
	Vector3 pp = particle->getPosition();
	Vector3 f = pp - origin;
	float dist = f.normalize();
	float factor = 1.0f / dist;
	f *= factor * strength;

	particle->addForce(f);
}
