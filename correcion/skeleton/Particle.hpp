#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "core.hpp"

class Particle
{
public:
	Particle();
	Particle(Vector3 _p, Vector3 _v, Vector3 _a, float _d,
		RenderItem* _renderitem);

	~Particle();

	void integrate(float t);

	void setPosition(const Vector3& _p) { position = _p; transform = physx::PxTransform(position); }
	void setVelocity(const Vector3& _v) { velocity = _v; }
	void setDamping(float _d) { damping = _d; }
	void setRenderItem(RenderItem* _renderItem);

	const Vector3& getPosition() const { return position; }

private:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float damping;

	RenderItem* renderItem;
	physx::PxTransform transform;
};

#endif
