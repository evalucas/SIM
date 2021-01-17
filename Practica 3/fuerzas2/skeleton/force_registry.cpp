#include "force_registry.hpp"
#include "force_generator.hpp"

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg)
{
	ParticleForceRegistration reg(particle, fg);
	registrations.push_back(reg);
}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg)
{
	for (auto it = registrations.begin(); it != registrations.end(); ++it) {
		if (it->fg == fg && it->particle == particle) {
			registrations.erase(it);
			return;
		}
	}
}

void ParticleForceRegistry::remove(Particle* particle)
{
	auto it = registrations.begin();
	while (it != registrations.end()) {
		if (it->particle == particle)
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
		it->fg->updateForce(it->particle, t);
	}
}
