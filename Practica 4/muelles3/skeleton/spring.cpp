#include "spring.hpp"

ParticleSpring::ParticleSpring(Particle* _other, float _k, float _restLength) :
	other(_other), k(_k), restLength(_restLength) {}

void ParticleSpring::updateForce(Particle* p, float t) {
	Vector3 f = p->getPosition();
	f -= other->getPosition();

	float length = f.normalize();

	float deltaL = ( length - restLength );
	float forceMagnitude = -k * deltaL;
	f *= forceMagnitude;
	p->addForce(f);
}

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3* _anchor, float _k, float _restLength) :
	anchor(_anchor), k(_k), restLength(_restLength){}

void ParticleAnchoredSpring::updateForce(Particle* p, float t) {
	Vector3 f = p->getPosition();
	f -= *anchor;

	float lenght = f.normalize();

	f *= -((lenght - restLength) * k);
	p->addForce(f);
}