#include "Particle.hpp"

Particle::Particle() : position(physx::PxIdentity), velocity(physx::PxIdentity), 
acceleration(physx::PxIdentity), damping(1.0f),renderItem(NULL)
{
	clearForce();
}

Particle::Particle(Vector3 _p, Vector3 _v, Vector3 _a,float _d,float _age, float _mass ,RenderItem* _renderitem)
	: PhysicsObject(_mass, _age), position(_p), velocity(_v), acceleration(_a), damping(_d), renderItem(_renderitem), transform(_p)
{	
	renderItem->addReference();
	renderItem->transform = &transform;
	clearForce();
}
Particle::~Particle()
{
	if (renderItem) renderItem->release();
}

void Particle::integrate(float t) {
	if (hasInfiniteMass()) return;
	
	position += velocity * t;

	acceleration = force * inverseMass;
	velocity += acceleration * t;
	velocity *= (powf(damping, t));

	transform = physx::PxTransform(position);

	clearForce();
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

void Particle::clearForce() {
	force = Vector3(0.0f, 0.0f, 0.0f);
}
void Particle::addForce(const Vector3& f) {
	force += f;
}