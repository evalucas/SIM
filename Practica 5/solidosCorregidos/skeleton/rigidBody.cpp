#include "rigidBody.hpp"

using namespace physx;

extern PxPhysics* gPhysics;
extern PxScene* gScene;

RigidBody::RigidBody(PxShape* _shape, PxTransform* t, Vector3& v, float _mass, float _age, float disableTime) : PhysicsObject(_mass, _age),
disableCollisionTime(disableTime)
{
	body = gPhysics->createRigidDynamic(*t);
	body->attachShape(*_shape);
	PxRigidBodyExt::updateMassAndInertia(*body, 10.f);
	gScene->addActor(*body);
	renderItem = new RenderItem(_shape, body, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	body->setLinearVelocity(v);

	if (disableTime > 0.0f) {
		body->setMaxContactImpulse(0.0f);
	}
}

const Vector3& RigidBody::getPosition() const {
	return body->getGlobalPose().p;
}

void RigidBody::addForce(const Vector3& f) {
	body->addForce(f);
}

void RigidBody::addTorque(const Vector3& t) {
	body->addTorque(t);
}

bool RigidBody::update(float t) {
	if (disableCollisionTime > 0.0f) {

		disableCollisionTime -= t;
		if (disableCollisionTime <= 0.0f) {
			PxShape* shapes[1];
			body->getShapes(shapes, 1);
			body->setMaxContactImpulse(3000.0f);
		}
	}

	return PhysicsObject::update(t);
}