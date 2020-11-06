#ifndef _FIREWORK_H_
#define _FIREWORK_H_

#include "Particle.hpp"
const unsigned FW_UNKNOWN_TYPE = static_cast<unsigned>(-1);

class Firework : public Particle
{
	friend class FireworkRule;
	unsigned type;
	float age;

public:
	Firework() : type(FW_UNKNOWN_TYPE), age(0.0f) {}

	void setParameters(unsigned _type, float _age) {
		type = _type;
		age = _age;
	}

	bool isActive() const {
	
		return type != FW_UNKNOWN_TYPE;
	}

	void setInactive() {
		type = FW_UNKNOWN_TYPE;
		setRenderItem(NULL);
	}

	void activate(float radius, const Vector4& color) {
	
		physx::PxShape* newShape = CreateShape(physx::PxSphereGeometry(radius));
		RenderItem* newRenderItem = new RenderItem(newShape, color);
		setRenderItem(newRenderItem);
		newShape->release();
		newRenderItem->release();
	}

	unsigned getType() const { return type; }

	bool update(float t) {
		integrate(t);

		age -= t;
		return (age <= 0.0f);
	}
};

#endif