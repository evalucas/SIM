#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "firework.hpp"
#include "firework_utils.hpp"
using namespace physx;

PxDefaultAllocator			gAllocator;
PxDefaultErrorCallback		gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

std::vector<Particle*>		gParticles;

void initRules() {
	std::vector<FireworkRule*>& rules = getFireworksRules();
	FireworkRule* rule = new FireworkRule();
	rule->setParameters(
		1,
		0.5f, 3.4f,
		Vector3(-5, -15, -5), Vector3(5, 18, 5),
		0.9,
		0.5f,
		Vector4(1.0f, 0.0f, 0.0f, 1.0f)
		);
	rule->AddPlayload(Payload(1, 2));
	rule->AddPlayload(Payload(2, 5));
	rules.push_back(rule);

	FireworkRule* rule2 = new FireworkRule();
	rule2->setParameters(
		2,
		3.5f, 5.4f,
		Vector3(-5, -25, -5), Vector3(5, 28, 5),
		0.9,
		1.5f,
		Vector4(0.0f, 0.0f, 1.0f, 1.0f)
	);
	rule2->AddPlayload(Payload(3, 25));
	rule2->AddPlayload(Payload(1, 2));
	rules.push_back(rule2);

	FireworkRule* rule3 = new FireworkRule();
	rule3->setParameters(
		3,
		0.5f, 10.0f,
		Vector3(-5, 45, -5), Vector3(5, 48, 5),
		0.9,
		1.5f,
		Vector4(0.0f, 1.0f, 0.0f, 1.0f)
	);
	rules.push_back(rule3);

	FireworkRule* rule4 = new FireworkRule();
	rule4->setParameters(
		4,
		5.0f, 5.0f,
		Vector3(-5, 45, -5), Vector3(5, 48, 5),
		0.9,
		1.5f,
		Vector4(0.0f, 1.0f, 1.0f, 1.0f)
	);
	rule4->AddPlayload(Payload(1, 15));
	rules.push_back(rule4);
}

void AddParticle(Particle* particle) {
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

	initRules();
	create(4, 1, NULL);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	PX_UNUSED(t);

	FireworksUpdate(t);
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