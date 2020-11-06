#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
//#include "RenderUtils.hpp"
//#include "callbacks.hpp"

#include "Particle.hpp"
#include "ParticleSystem.hpp"

using namespace physx;

PxDefaultAllocator			gAllocator;
PxDefaultErrorCallback		gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

//Particle*					p = NULL;
std::vector<Particle*>		vP;

ParticleSystem* gParticleSystem;

void AddParticle(Particle* particle) {
	vP.push_back(particle);
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
	gParticleSystem->maxPhi = 180.0f;

	gParticleSystem->minSpeed = 20.0f;
	gParticleSystem->maxSpeed = 100.0f;
		
	gParticleSystem->minAge = 2.0f;
	gParticleSystem->maxAge = 4.0f;

	gParticleSystem->damping = 0.99f;
	
	gParticleSystem->generation_rate = 0.001f;
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	PX_UNUSED(t);

	gParticleSystem->update(t);

	auto it = vP.begin();
	while (it != vP.end()) {

		Particle* p = (*it);
		bool kill_particle = p->update(t);
		if (kill_particle) {
			it = vP.erase(it);
			delete p;
		}
		else ++it;
	}

}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	for (auto it = vP.begin(); it != vP.end(); it++) {
		Particle* p = (*it);
		delete p;
	}
	vP.clear();

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