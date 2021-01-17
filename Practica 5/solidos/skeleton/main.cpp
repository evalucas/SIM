#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "force_registry.hpp"
#include "gravity.hpp"
#include "wind.hpp"
#include "explosion.hpp"
#include "rigidBodySystem.hpp"

using namespace physx;
	
PxDefaultAllocator			gAllocator;
PxDefaultErrorCallback		gErrorCallback;

PxFoundation*				gFoundation = NULL;
PxPhysics*					gPhysics	= NULL;


PxMaterial*					gMaterial	= NULL;

PxPvd*						gPvd        = NULL;

PxDefaultCpuDispatcher*		gDispatcher = NULL;
PxScene*					gScene      = NULL;
ContactReportCallback		gContactReportCallback;

std::vector<Particle*>		gParticles;

ParticleSystem*				gParticleSystem;

BodyForceRegistry		forceRegistry;
//ParticleGravity				gravity(Vector3(0.0f, -1.0f, 0.0f));
//ParticleGravity gravity2(Vector3(0.0f, -20.0f, 0.0f));

RenderItem*					windRenderItem = NULL;
RenderItem*					windAreaRenderItem = NULL;
physx::PxTransform			windTransform;
ParticleWind*				wind = NULL;

RenderItem*					explosionRenderItem = NULL;
RenderItem*					explosionAreaRenderItem = NULL;
physx::PxTransform			explosionTransform;
BodyExplosion*			explosion = NULL;
float explosionAge = -1.0f;

RenderItem*					floorRenderItem = NULL;
RenderItem*					ballRenderItem = NULL;

std::vector<PxRigidBody*>	gBodies;
RigidBodySystem*			gBodySystem;

void AddParticle(Particle* particle) 
{
	/*forceRegistry.add(particle, &gravity);
	if(wind)
		forceRegistry.add(particle, wind);
	if(explosion)
		forceRegistry.add(particle, explosion);
	gParticles.push_back(particle);*/
}

void AddBody(PxRigidBody* body) {
	if (explosion)
		forceRegistry.add(body, explosion);
	
	gBodies.push_back(body);
	gScene->addActor(*body);
}

void CreateBody(physx::PxTransform* t) 
{
	physx::PxRigidDynamic* body = gPhysics->createRigidDynamic(*t);
	physx::PxShape* newShape = CreateShape(physx::PxSphereGeometry(5.0f));
	body->attachShape(*newShape);

	RenderItem* ballRenderItem = new RenderItem(newShape, body, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	newShape->release();

	PxRigidBodyExt::updateMassAndInertia(*body, 0.1f);

	AddBody(body);

}


void AddForceGenerator(BodyForceGenerator* forceGen, PxRigidBody* body) {
	forceRegistry.add(body, forceGen);
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
	
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);


	Vector3 floorPosition(0.0f, 20.0f, 0.0f);
	physx::PxTransform floorTransform(floorPosition);
	PxRigidStatic* floor =	gPhysics->createRigidStatic(floorTransform);
	physx::PxShape* newShape = CreateShape(physx::PxBoxGeometry(100.0f, 1.0f, 100.0f));
	floor->attachShape(*newShape);
	floorRenderItem = new RenderItem(newShape,floor,Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	newShape->release();
	gScene->addActor(*floor);

	gBodySystem = new RigidBodySystem();
	gBodySystem->position = Vector3(0.0f, 70.0f, 0.0f);

	gBodySystem->minPos = -50.0f;
	gBodySystem->maxPos = 50.0f;

	gBodySystem->generation_rate = 0.5f;
	gBodySystem->max = 200;

	/*gParticleSystem = new ParticleSystem();
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
	gParticleSystem->maxMass = 2.0f;*/

	/*Vector3 windPos = Vector3(0.0f, 50.0f, 0.0f);
	Vector3 windForce = Vector3(-30.0f, 0.0f, 0.0f);
	float windRadius = 20.0f;
	windTransform = physx::PxTransform(windPos);
	physx::PxShape* newShape = CreateShape(physx::PxSphereGeometry(0.5f));
	windRenderItem = new RenderItem(newShape, &windTransform, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	newShape->release();

	newShape = CreateShape(physx::PxSphereGeometry(windRadius));
	windAreaRenderItem = new RenderItem(newShape, &windTransform, Vector4(1.0f, 1.0f, 0.0f, 0.2f));
	newShape->release();

	wind = new ParticleWind(windForce, windPos, windRadius);*/

}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	PX_UNUSED(t);

	gScene->simulate(t);
	gScene->fetchResults(true);

	forceRegistry.updateForces(t);
	if(gParticleSystem)gParticleSystem->update(t);
	if (gBodySystem)gBodySystem->update(t);
	
	auto it = gParticles.begin();
	while (it != gParticles.end()) 
	{
		Particle* particle = (*it);
		bool kill_particle = particle->update(t);
		if (!kill_particle) {
			float dist = particle->getPosition().magnitude();
			if (dist != dist || dist > 1000.0f) 
			{
				kill_particle = true;
			}
		}
		if (kill_particle)
		{
			it = gParticles.erase(it);
			//forceRegistry.remove(particle);
			delete particle;
		}
		else 
			++it;
	}	

	if (explosionAge >= 0.0f) {
		explosionAge -= t;
		if (explosionAge < 0.0f) {
			
			
			forceRegistry.remove(explosion);
			explosion = NULL;
			if (explosionRenderItem)
				explosionRenderItem->release();
			if (explosionAreaRenderItem)
				explosionAreaRenderItem->release();
			delete explosion;
		
		}
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


	for (auto it = gBodies.begin(); it != gBodies.end(); it++) {
		PxRigidBody* p = (*it);
		p->release();
	}
	gBodies.clear();


	if (windRenderItem) windRenderItem->release();
	if (windAreaRenderItem) windAreaRenderItem->release();
	if (wind) delete wind;

	if (explosion) delete explosion;
	if (explosionRenderItem) explosionRenderItem->release();
	if (explosionAreaRenderItem) explosionAreaRenderItem->release();

	if (floorRenderItem) floorRenderItem->release();
	if (ballRenderItem) ballRenderItem->release();


	gScene->release();
	gDispatcher->release();

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
		if (explosion) 
		{
			delete explosion;
			forceRegistry.remove(explosion);
			if (explosionRenderItem) explosionRenderItem->release();
			if (explosionAreaRenderItem) explosionAreaRenderItem->release();

		}
		Vector3 expPos(0.0f, 30.0f, 0.0f);
		float expRadius = 30.0f;
		explosion = new BodyExplosion(3000.0f, expPos, expRadius);
		explosionAge = 5.0f;

		explosionTransform = physx::PxTransform(expPos);
		physx::PxShape* newShape = CreateShape(physx::PxSphereGeometry(0.5f));
		explosionRenderItem = new RenderItem(newShape, &explosionTransform, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
		newShape->release();

		newShape = CreateShape(physx::PxSphereGeometry(expRadius));
		explosionAreaRenderItem = new RenderItem(newShape, &explosionTransform, Vector4(1.0f, 1.0f, 0.0f, 0.2f));
		newShape->release();

		for (auto it = gBodies.begin(); it != gBodies.end(); ++it) {
			PxRigidBody* body = (*it);
			forceRegistry.add(body, explosion);
		}

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