#include "force_registry.hpp"
#include "force_generator.hpp"
#include "gravity.hpp"

void BodyForceRegistry::add(physx::PxRigidBody* body, BodyForceGenerator* fg)
{
	BodyForceRegistration reg(body, fg);	
	registrations.push_back(reg);
}

void BodyForceRegistry::remove(physx::PxRigidBody* body, BodyForceGenerator* fg)
{
	for (auto it = registrations.begin(); it != registrations.end(); ++it) {
		if (it->fg == fg && it->body == body) {
			registrations.erase(it);
			return;
		}
	}
}

void BodyForceRegistry::remove(physx::PxRigidBody* body)
{
	auto it = registrations.begin();
	while (it != registrations.end()) {
		if (it->body == body)
			it = registrations.erase(it);
		else
			++it;
	}
}

void BodyForceRegistry::remove(BodyForceGenerator* fg)
{
	auto it = registrations.begin();
	while (it != registrations.end()) {
		if (it->fg == fg)
			it = registrations.erase(it);
		else
			++it;
	}
}

void BodyForceRegistry::clear()
{
	registrations.clear();
}

void BodyForceRegistry::updateForces(float t)
{
	for (auto it = registrations.begin(); it != registrations.end(); ++it) {
		
		it->fg->updateForce(it->body, t);	
		
	}
}
