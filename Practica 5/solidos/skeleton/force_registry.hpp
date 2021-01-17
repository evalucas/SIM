#ifndef  _FORCE_REGISTRY_H__
#define _FORCE_REGISTRY_H__

#include <vector>
#include "PxPhysicsAPI.h"

class BodyForceGenerator;

class BodyForceRegistry 
{
protected:

	struct BodyForceRegistration 
	{
		physx::PxRigidBody* body;
		BodyForceGenerator* fg;
		BodyForceRegistration(physx::PxRigidBody* _b, BodyForceGenerator* _fg) : body(_b), fg(_fg) {}
	};

	typedef std::vector<BodyForceRegistration> Registry;
	Registry registrations;

public:
	void add(physx::PxRigidBody* body, BodyForceGenerator* fg);

	void remove(physx::PxRigidBody* body, BodyForceGenerator* fg);
	void remove(physx::PxRigidBody* body);
	void remove(BodyForceGenerator* fg);

	void clear();

	void updateForces(float t);
};

#endif 


