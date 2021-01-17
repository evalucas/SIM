#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "core.hpp"

class Particle
{
public:
	Particle();
	Particle(Vector3 _p, Vector3 _v, Vector3 _a, float _d, float _age,
		RenderItem* _renderitem);

	~Particle();

	bool update(float t);

	void setPosition(const Vector3& _p) { position = _p; transform = physx::PxTransform(position); }
	void setVelocity(const Vector3& _v) { velocity = _v; }
	void setAcceleration(const Vector3& _a) { acceleration = _a; }
	void setDamping(float _d) { damping = _d; }
	void setMass(float _m) { inverseMass = 1.0f/_m; }
	void setRenderItem(RenderItem* _renderItem);

	const Vector3& getPosition() const { return position; }
	const Vector3& getVelocity() const { return velocity; }
	const Vector3& getAcceleration() const { return acceleration; }


protected:

	void integrate(float t);

	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float damping;

	float inverseMass;

	float age;

	RenderItem* renderItem;
	physx::PxTransform transform;
};

#endif
