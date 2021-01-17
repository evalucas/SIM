#include "bouyancy.hpp"

ParticleBouyancy::ParticleBouyancy(float _maxDepth, float _volume, float _waterHeight, float _liquidDensity) :
	maxDepth(_maxDepth), volume(_volume), waterHeight(_waterHeight), liquidDensity(_liquidDensity){}
	
void ParticleBouyancy::updateForce(Particle* particle, float t) {
	float depth = particle->getPosition().y;

	if (depth > (waterHeight + maxDepth))
		return;

	Vector3 f(0.0f, 0.0f, 0.0f);
	if (depth <= (waterHeight - maxDepth)) {
		f.y = liquidDensity * volume;
	}
	else {
		float depthExterior = waterHeight + maxDepth;
		float volumeFactor = (depth - depthExterior) / (2 * maxDepth);
		f.y = liquidDensity * volumeFactor * volume;
	}

	//f.y *= 10.0f;
	particle->addForce(f);
}