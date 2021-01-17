#include "Particle.hpp"
#include "spring.hpp"
#include "core.hpp"

extern void AddParticle(Particle* particle);
extern void AddForceGenerator(ParticleForceGenerator* forceGen, Particle* particle);

RenderItem* anchorRenderItem = NULL;
physx::PxTransform anchorTransform;
ParticleSpring* anchoredSpring1;
ParticleSpring* anchoredSpring2;
Vector3 anchorPosition;

void initSpringDemo() {
	//Vector3 particlePosition(0.0f, 20.0f, 0.0f);
	////Particula
	//physx::PxShape* newShape = CreateShape(physx::PxSphereGeometry(2.0f));
	//RenderItem* newRenderItem = new RenderItem(newShape, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	//Particle* newParticle1 = new Particle(particlePosition,Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.99f, FLT_MAX, 2.0f, newRenderItem);
	//newShape->release();
	//newRenderItem->release();
	//AddParticle(newParticle1);
	//
	////Particula
	//newShape = CreateShape(physx::PxSphereGeometry(2.0f));
	//newRenderItem = new RenderItem(newShape, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	//Particle* newParticle2 = new Particle(particlePosition, Vector3(0.0f, 10.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.99f, FLT_MAX, 2.0f, newRenderItem);
	//newShape->release();
	//newRenderItem->release();
	//AddParticle(newParticle2);


	//anchoredSpring1 = new ParticleSpring(newParticle1, 2.0f, 12.0f);
	//AddForceGenerator(anchoredSpring1, newParticle2);

	//anchoredSpring2 = new ParticleSpring(newParticle2, 2.0f, 12.0f);
	//AddForceGenerator(anchoredSpring2, newParticle1);
}

void endSpringDemo() {
	if (anchorRenderItem) {
		anchorRenderItem->release();
		anchorRenderItem = NULL;		
	}
}

void keyPressedSpringDemo(unsigned char key, const physx::PxTransform& camera) {

	PX_UNUSED(camera);
	switch (toupper(key))
	{
	case '+': {

		//anchoredSpring->setElasticity(anchoredSpring->getElasticity() + 0.5f);
		break;
	}
	case '-': {

		//anchoredSpring->setElasticity(anchoredSpring->getElasticity() - 0.5f);
		break;
	}
	default:
		break;
	}
}
