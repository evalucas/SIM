#include "force_registry.hpp"
#include "force_generator.hpp"
#include "gravity.hpp"

void ParticleForceRegistry::add(PhysicsObject* body, ParticleForceGenerator* fg)
{
	ParticleForceRegistration reg(body, fg);	
	registrations.push_back(reg);
}

void ParticleForceRegistry::remove(PhysicsObject* body, ParticleForceGenerator* fg)
{
	for (auto it = registrations.begin(); it != registrations.end(); ++it) {
		if (it->fg == fg && it->body == body) {
			registrations.erase(it);
			return;
		}
	}
}

void ParticleForceRegistry::remove(PhysicsObject* body)
{
	auto it = registrations.begin();
	while (it != registrations.end()) {
		if (it->body == body)
			it = registrations.erase(it);
		else
			++it;
	}
}

void ParticleForceRegistry::remove(ParticleForceGenerator* fg)
{
	auto it = registrations.begin();
	while (it != registrations.end()) {
		if (it->fg == fg)
			it = registrations.erase(it);
		else
			++it;
	}
}

void ParticleForceRegistry::clear()
{
	registrations.clear();
}

void ParticleForceRegistry::updateForces(float t)
{
	for (auto it = registrations.begin(); it != registrations.end(); ++it) {
		
		it->fg->updateForce(it->body, t);	
		
	}
}
