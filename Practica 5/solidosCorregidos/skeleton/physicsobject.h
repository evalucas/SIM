#pragma once
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "core.hpp"

class PhysicsObject {

public:
	PhysicsObject() {
		inverseMass = 0.0f;
		//age = std::numeric_limits<float>::max();
	}

	PhysicsObject(float _mass, float _age) {
		setMass(_mass);
		age = _age;
	}

	virtual ~PhysicsObject() {}

	virtual const Vector3& getPosition() const = 0;
	virtual void addForce(const Vector3& f) =0;
	virtual void addTorque(const Vector3& t) {}

	virtual bool update(float t) {
		integrate(t);

		age -= t;

		if (age < 0.0f) {
			return true;
		}
		return false;
	}

	void setMass(float _mass) {
		if (_mass > 0.0f) {
			inverseMass = 1.0f / _mass;
		}
		else
			inverseMass = FLT_MAX;
	}

	float getMass() const {
		if (inverseMass <= 0.0f) {
			return FLT_MAX;
		}
		return 1.0f / inverseMass;
	}

	void setInverseMass(float _inverseMass) { inverseMass = _inverseMass; }
	bool hasInfiniteMass() const { return inverseMass <= 0.0f; }

protected:
	virtual void integrate(float t) {}
	float age;
	float inverseMass;
};