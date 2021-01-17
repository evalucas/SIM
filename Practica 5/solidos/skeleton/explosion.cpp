#include "explosion.hpp"
#include "Particle.hpp"

void BodyExplosion::updateForce(physx::PxRigidBody* body, float t)
{
	Vector3 pp = body->getGlobalPose().p;
	Vector3 f = pp - origin;
	float dist = f.normalize();
	float factor = 100.0f / dist;
	f *= factor * strength;

	body->addForce(f);


}
