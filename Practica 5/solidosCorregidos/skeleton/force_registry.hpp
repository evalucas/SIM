#ifndef  _FORCE_REGISTRY_H__
#define _FORCE_REGISTRY_H__

#include <vector>
#include "PxPhysicsAPI.h"
#include "physicsobject.h"

class ParticleForceGenerator;

class ParticleForceRegistry 
{
protected:

	struct ParticleForceRegistration 
	{
		PhysicsObject* body;
		ParticleForceGenerator* fg;
		ParticleForceRegistration(PhysicsObject* _b, ParticleForceGenerator* _fg) : body(_b), fg(_fg) {}
	};

	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registrations;

public:
	void add(PhysicsObject* body, ParticleForceGenerator* fg);

	void remove(PhysicsObject* body, ParticleForceGenerator* fg);
	void remove(PhysicsObject* body);
	void remove(ParticleForceGenerator* fg);

	void clear();

	void updateForces(float t);
};

#endif 


