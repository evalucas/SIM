#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.hpp"
#include "Shot.h"

using namespace physx;

PxDefaultAllocator			gAllocator;
PxDefaultErrorCallback		gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

//Particle*					p = NULL;
std::vector<Particle*>		vP;
std::vector<Shot*>			gShots;
#define SHOT_INITIAL_SPEED 100.0f;

void shootShot() {
	Shot* newShot = new Shot();
	Vector3 shotDir = GetCamera()->getDir();
	shotDir *= SHOT_INITIAL_SPEED;
	Vector3 shotPos = GetCamera()->getEye();
	shotPos += shotDir * 0.2f;
	newShot->particle.setPosition(shotPos);
	newShot->particle.setVelocity(shotDir);
	newShot->startTime = GetLastTime();

	PxShape* shape = gPhysics->createShape(physx::PxSphereGeometry(2.0f), *gMaterial);
	RenderItem* renderItem = new RenderItem(shape, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	newShot->particle.setRenderItem(renderItem);
	renderItem->release();
	shape->release();

	gShots.push_back(newShot);
}


//void createParticle() {
//	PxShape* shape = gPhysics->createShape(physx::PxSphereGeometry(2.0f), *gMaterial);
//	RenderItem* renderItem = new RenderItem(shape, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
//	Particle* p = new Particle(PxVec3(0.0f, 40.0f, 10.0f), PxVec3(10.0f, 0.0f, 0.0f), renderItem);
//	shape->release();
//
//	vP.push_back(p);
//
//}

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

}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	PX_UNUSED(t);

	////P2
	/*for (auto it = vP.begin(); it != vP.end(); it++) {
		Particle* obj = (*it);
		obj->integrate(t);
	}*/

	auto it = gShots.begin();
	while (it != gShots.end()) {
		Shot* shot = (*it);
		shot->particle.integrate(t);
		if (shot->particle.getPosition().y < 0.0f ||
			shot->startTime + 5000 < GetLastTime() ||
			shot->particle.getPosition().z > 200.0f)
		{
			it = gShots.erase(it);
			delete shot;
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

	//for (auto it = vP.begin(); it != vP.end(); it++) {
	//	Particle* obj = (*it);
	//	delete obj;
	//}
	//vP.clear();

	for (auto it = gShots.begin(); it != gShots.end(); it++) {
		Shot* obj = (*it);
		delete obj;
	}
	gShots.clear();

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
		shootShot();
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