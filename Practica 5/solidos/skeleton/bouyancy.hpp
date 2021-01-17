#ifndef __BUOYANCY_H__
#define __BUOYANCY_H__

#include "force_generator.hpp"
#include "Particle.hpp"

class ParticleBouyancy : public BodyForceGenerator
{
	float maxDepth;
	float volume;
	float waterHeight;
	float liquidDensity;
public:
	ParticleBouyancy(float _maxDepth, float _volume, float _waterHeight, float _liquidDensity = 1000.0f);

	virtual void updateForce(Particle* particle, float t);
};

#endif