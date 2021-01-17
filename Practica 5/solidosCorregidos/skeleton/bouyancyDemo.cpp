#include "bouyancy.hpp"
#include "core.hpp"

extern void AddParticle(Particle* particle);
extern void AddForceGenerator(ParticleForceGenerator* forceGen, Particle* particle);

RenderItem* waterRenderItem = NULL;
physx::PxTransform waterTransform;
ParticleBouyancy* bouyancySpring = NULL;

void initBouyancyDemo() {

	//float boxHeight = 5.0f;
	//float boxWidth = 5.0f;
	//float boxDepth = 5.0f;
	//Vector3 particlePosition(0.0f, 60.0f, 0.0f);


	////Particula
	//physx::PxShape* newShape = CreateShape(physx::PxBoxGeometry(boxWidth, boxHeight, boxDepth));
	//RenderItem* newRenderItem = new RenderItem(newShape, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	//Particle* newParticle = new Particle(particlePosition, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.99f, FLT_MAX, 0.5f, newRenderItem);
	//newShape->release();
	//newRenderItem->release();
	//AddParticle(newParticle);

	//Vector3 waterPosition = particlePosition + Vector3(0.0f, 5.0f, 0.0f);
	//physx::PxShape* waterShape = CreateShape(physx::PxBoxGeometry(500.f, 0.01f, 500.0f));
	//waterTransform = physx::PxTransform(waterPosition);
	//waterRenderItem = new RenderItem(waterShape, &waterTransform, Vector4(0.0f, 0.0f, 1.0f, 1.0f));



	//bouyancySpring = new ParticleBouyancy(boxHeight, 0.001f, waterPosition.y, 3000);
	//AddForceGenerator(bouyancySpring, newParticle);

}

void endBouyancyDemo() {
	if (waterRenderItem) {
		waterRenderItem->release();
		waterRenderItem = NULL;
	}
}

void keyPressedBouyancyDemo(unsigned char key, const physx::PxTransform& camera) {

	PX_UNUSED(camera);
	switch (toupper(key))
	{
	case '+': {

		break;
	}
	case '-': {

		break;
	}
	default:
		break;
	}
}
