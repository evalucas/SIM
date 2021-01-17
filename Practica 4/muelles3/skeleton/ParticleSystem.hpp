#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSTEM_H_

#include "core.hpp"

class ParticleSystem
{
private:
	void createNewParticle();
public:
	ParticleSystem();
	~ParticleSystem();

	void update(float t);

	float generation_rate;
	
	float minAge;
	float maxAge;

	float damping;

	Vector3 axis;

	float minRho;
	float maxRho;
	float minPhi;
	float maxPhi;

	float minSpeed;
	float maxSpeed;

	float minRadius;
	float maxRadius;

	float time_for_next_particle;

	Vector3 position;

	float minMass;
	float maxMass;

	/*ParticleGravity gravity;
	ParticleForceRegistry forceRegistry;*/
};

#endif
