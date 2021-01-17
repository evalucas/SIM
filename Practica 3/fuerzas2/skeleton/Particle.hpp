#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "core.hpp"

class Particle
{
public:
	Particle();
	Particle(Vector3 _p, Vector3 _v, Vector3 _a, float _d, float _age, float _mass,
		RenderItem* _renderitem);

	~Particle();

	bool update(float t);

	void setPosition(const Vector3& _p) { position = _p; transform = physx::PxTransform(position); }
	void setVelocity(const Vector3& _v) { velocity = _v; }
	void setDamping(float _d) { damping = _d; }
	void setRenderItem(RenderItem* _renderItem);

	const Vector3& getPosition() const { return position; }

	void clearForce();
	void addForce(const Vector3& f);

	void setInverseMass(float _inverseMass) { inverseMass = _inverseMass; }
	bool hasInfiniteMass() const { return inverseMass <= 0.0f; }

	void setMass(float _m) 
	{ 
		if (_m > 0.0f) inverseMass = 1.0f / _m;
		else inverseMass = FLT_MAX;
	}

	float getMass() const 
	{
		if (inverseMass <= 0.0f) return FLT_MAX;
		else return 1.0f / inverseMass;
	}


private:

	void integrate(float t);

	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float damping;

	float age;
	float inverseMass;

	Vector3 force;

	RenderItem* renderItem;
	physx::PxTransform transform;
};

#endif
