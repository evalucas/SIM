#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "force_registry.hpp"
#include "gravity.hpp"
#include "wind.hpp"

using namespace physx;

PxDefaultAllocator			gAllocator;
PxDefaultErrorCallback		gErrorCallback;

PxFoundation*				gFoundation = NULL;
PxPhysics*					gPhysics = NULL;


PxMaterial*					gMaterial = NULL;

PxPvd*						gPvd = NULL;

std::vector<Particle*>		gParticles;

ParticleSystem*				gParticleSystem;

ParticleForceRegistry forceRegistry;
ParticleGravity gravity(Vector3(0.0f, -1.0f, 0.0f));
ParticleGravity gravity2(Vector3(0.0f, -20.0f, 0.0f));

RenderItem* windRenderItem = NULL;
RenderItem* windAreaRenderItem = NULL;
physx::PxTransform windTransform;
ParticleWind* wind = NULL;


void AddParticle(Particle* particle) 
{
	forceRegistry.add(particle, &gravity);
	forceRegistry.add(particle, wind);
	gParticles.push_back(particle);
}

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	gParticleSystem = new ParticleSystem();
	gParticleSystem->position = Vector3(0.0f, 0.0f, 0.0f);
	gParticleSystem->axis = Vector3(0.0f, 1.0f, 0.0f);
	gParticleSystem->minRho = 0.0f;
	gParticleSystem->maxRho = 30.0f;
	gParticleSystem->minPhi = 0.0f;
	gParticleSystem->maxPhi = 30.0f;

	gParticleSystem->minSpeed = 10.0f;
	gParticleSystem->maxSpeed = 40.0f;

	gParticleSystem->minAge = 0.5f;
	gParticleSystem->maxAge = 10.0f;

	gParticleSystem->damping = 0.99f;

	gParticleSystem->generation_rate = 0.1f;

	gParticleSystem->minMass = 0.1f;
	gParticleSystem->maxMass = 2.0f;

	Vector3 windPos = Vector3(0.0f, 50.0f, 0.0f);
	Vector3 windForce = Vector3(-30.0f, 0.0f, 0.0f);
	float windRadius = 20.0f;
	windTransform = physx::PxTransform(windPos);
	physx::PxShape* newShape = CreateShape(physx::PxSphereGeometry(0.5f));
	windRenderItem = new RenderItem(newShape, &windTransform, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	newShape->release();

	newShape = CreateShape(physx::PxSphereGeometry(windRadius));
	windAreaRenderItem = new RenderItem(newShape, &windTransform, Vector4(1.0f, 1.0f, 0.0f, 0.2f));
	newShape->release();

	wind = new ParticleWind(windForce, windPos, windRadius);

}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	PX_UNUSED(t);

	forceRegistry.updateForces(t);
	gParticleSystem->update(t);

	auto it = gParticles.begin();
	while (it != gParticles.end()) 
	{
		Particle* particle = (*it);
		bool kill_particle = particle->update(t);
		if (kill_particle)
		{
			it = gParticles.erase(it);
			forceRegistry.remove(particle);
			delete particle;
		}
		else 
			++it;
	}	
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	for (auto it = gParticles.begin(); it != gParticles.end(); it++) {
		Particle* p = (*it);
		delete p;
	}
	gParticles.clear();

	if (windRenderItem) windRenderItem->release();
	if (windAreaRenderItem) windAreaRenderItem->release();
	delete wind;

	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (toupper(key))
	{
		//case 'B': break;
		//case ' ':	break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}