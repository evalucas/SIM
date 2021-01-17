#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "core.hpp"
#include "physicsobject.h"

class Particle : public PhysicsObject
{
public:
	Particle();
	Particle(Vector3 _p, Vector3 _v, Vector3 _a, float _d, float _age, float _mass,
		RenderItem* _renderitem);

	virtual ~Particle();

	bool update(float t);

	void setPosition(const Vector3& _p) { position = _p; transform = physx::PxTransform(position); }
	void setVelocity(const Vector3& _v) { velocity = _v; }
	void setDamping(float _d) { damping = _d; }
	void setRenderItem(RenderItem* _renderItem);

	const Vector3& getPosition() const { return position; }

	void clearForce();
	void addForce(const Vector3& f);
	
private:

	void integrate(float t);

	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float damping;

	Vector3 force;

	RenderItem* renderItem;
	physx::PxTransform transform;
};

#endif
