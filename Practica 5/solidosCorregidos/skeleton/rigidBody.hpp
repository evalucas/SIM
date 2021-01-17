#pragma once

#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "core.hpp"
#include "physicsobject.h"

using namespace physx;

class RigidBody : public PhysicsObject
{
public:
	RigidBody(PxShape* _shape, PxTransform* t, Vector3& v, float _mass, float _age, float disableTime = -1.0f);

	virtual ~RigidBody() {
		if (renderItem)
			renderItem->release();
	}

	const Vector3& getPosition() const override;

	virtual void addForce(const Vector3& f) override;
	virtual void addTorque(const Vector3& t) override;

	bool update(float f) override;

protected:
	PxRigidDynamic* body;
	RenderItem* renderItem;
	float disableCollisionTime;
};

