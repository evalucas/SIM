#include "explosion.hpp"
#include "Particle.hpp"
#include "physicsobject.h"

void ParticleExplosion::updateForce(PhysicsObject* body, float t)
{
	Vector3 pp = body->getPosition();
	Vector3 f = pp - origin;
	float dist = f.normalize();
	float factor = 100.0f / dist;
	f *= factor * strength;

	body->addForce(f);


}
