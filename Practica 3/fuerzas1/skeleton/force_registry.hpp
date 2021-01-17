#ifndef  _FORCE_REGISTRY_H__
#define _FORCE_REGISTRY_H__

class Particle;
class ParticleForceGenerator;

#include <vector>

class ParticleForceRegistry 
{
protected:

	struct ParticleForceRegistration 
	{
		Particle* particle;
		ParticleForceGenerator* fg;
		ParticleForceRegistration(Particle* _p, ParticleForceGenerator* _fg) : particle(_p), fg(_fg) {}
	};

	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registrations;

public:
	void add(Particle* particle, ParticleForceGenerator* fg);

	void remove(Particle* particle, ParticleForceGenerator* fg);
	void remove(Particle* particle);

	void clear();

	void updateForces(float t);
};

#endif 


