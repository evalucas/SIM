#include "ParticleSystem.hpp"
#include "Particle.hpp"
#include "core.hpp"
#include "random.cpp"

extern void AddParticle(Particle* particle);
ParticleSystem::ParticleSystem() : time_for_next_particle(0.0f)
{
	position = Vector3(0.0f, 0.0f, 0.0f);
	axis = Vector3(0.0f, 1.0f, 0.0f);
	minRho = 0.0f;
	maxRho = 0.0f;
	minPhi = 0.0f;
	maxPhi = 0.0f;

	minSpeed = 0.0f;
	maxSpeed = 0.0f;

	minAge = 0.0f;
	maxAge = 0.0f;

	damping = 0.99f;

	generation_rate = 0.5f;

	minMass = 0.0f;
	maxMass = 0.0f;
}

ParticleSystem::~ParticleSystem()
{

}

float randomf(float _min, float _max) {

	float r = static_cast<float>(std::rand()) / RAND_MAX;
	r *= (_max - _min);
	r += _min;

	return r;
}

Vector3 Polar2Cartesian(float r, float rho, float phi) 
{
	float x = r * sin(rho) * cos(phi);
	float y = r * sin(rho) * sin(phi);
	float z = r * cos(rho);
	return Vector3(x, y, z);
}

void ParticleSystem::update(float t)
{
	time_for_next_particle -= t;
	if (time_for_next_particle < 0.0f) {
		
		createNewParticle();
		time_for_next_particle += generation_rate;
	}
}

physx::PxQuat getRotationTo(const Vector3& src, const Vector3& dst) {
	physx::PxQuat q;
	float d = src.dot(dst);
	if (d >= 1.0f) {
		return physx::PxIdentity;
	}
	if (d < (0.001 - 1.0f)) {
		return physx::PxIdentity;

	}
	else {
		float s = sqrtf((1 + d) * 2);
		float inv = 1.0f / s;
		Vector3 c = src.cross(dst);
		q.x = c.x * inv;
		q.y = c.y * inv;
		q.z = c.z * inv;
		q.w = s * 0.5f;
		q.normalize();
	}
	return q;
}

void ParticleSystem::createNewParticle()
{
	float rho = randomf(minRho, maxRho) * 3.14f / 180.0f;
	float phi = randomf(minPhi, maxPhi) * 3.14f / 180.0f;

	Vector3 dir = Polar2Cartesian(1.0f, rho, phi);
	float speed = randomf(minSpeed, maxSpeed);

	float age = randomf(minAge, maxAge);

	physx::PxQuat quat = getRotationTo(Vector3(0.0f, 0.0f, 1.0f), axis);

	physx::PxTransform rotation(quat);
	dir = rotation.transform(dir);

	float mass = randomf(minMass, maxMass);

	physx::PxShape* newShape = CreateShape(physx::PxSphereGeometry(mass));
	RenderItem* newRenderItem = new RenderItem(newShape, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	Particle* newParticle = new Particle(position, speed * dir, Vector3(0.0f, 0.0f, 0.0f), damping, age, mass,newRenderItem);
	newShape->release();
	AddParticle(newParticle);
	newRenderItem->release();

	//forceRegistry.add(newParticle, &gravity);
}