#include "Particle.hpp"

Particle::Particle() : position(physx::PxIdentity), velocity(physx::PxIdentity), 
acceleration(physx::PxIdentity), damping(1.0f), renderItem(NULL)
{
}

Particle::Particle(Vector3 _p, Vector3 _v, Vector3 _a,float _d,float _age,RenderItem* _renderitem)
	: position(_p), velocity(_v), acceleration(_a), damping(_d), age(_age),renderItem(_renderitem), transform(_p)
{	
		renderItem->addReference();
	renderItem->transform = &transform;
}
Particle::~Particle()
{
	if (renderItem) renderItem->release();
}

void Particle::integrate(float t) {
	position += velocity * t;
	velocity += acceleration * t;
	velocity *= (powf(damping, t));

	transform = physx::PxTransform(position);
}

void Particle::setRenderItem(RenderItem* _renderItem) {
	if (renderItem) renderItem->release();
	renderItem = _renderItem;
	renderItem->addReference();
	renderItem->transform = &transform;

}
bool Particle::update(float t){
	integrate(t);

	age -= t;

	if (age < 0.0f) {
		return true;
	}
	return false;
}