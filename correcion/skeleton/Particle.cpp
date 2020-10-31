#include "Particle.hpp"

Particle::Particle() : position(physx::PxIdentity), velocity(physx::PxIdentity), 
acceleration(physx::PxIdentity), damping(1.0f), renderItem(NULL)
{
}

Particle::Particle(Vector3 _p, Vector3 _v, Vector3 _a,float _d,RenderItem* _renderitem)
	: position(_p), velocity(_v), acceleration(_a), damping(_d),renderItem(_renderitem), transform(_p)
{	
	////P1
	//if (!_renderitem) {
	//	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
	//	renderItem = new RenderItem(shape, &transform, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	//	shape->release();
	//}
	//else _renderitem->addReference();

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