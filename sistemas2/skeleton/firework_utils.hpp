#ifndef _FIREWORK_UTILS_H_
#define _FIREWORK_UTILS_H_

#include "core.hpp"
#include <vector>
#include "firework.hpp"

void create(unsigned type, unsigned count, Firework* parent);
std::vector<FireworkRule*>& getFireworksRules();
void FireworksUpdate(float t);

struct Payload {
	Payload(unsigned _type, unsigned _count) :type(_type), count(_count) {}

	unsigned type; 
	unsigned count;

	void set(unsigned _type, unsigned _count)
	{
		type = _type;
		count = _count;
	}

};

class FireworkRule {

	unsigned type;

	float minAge;
	float maxAge;

	Vector3 minVelocity;
	Vector3 maxVelocity;

	float damping;
	float radius;

	Vector4 color;

	std::vector<Payload> payloads;
public:
	void setParameters(unsigned _type, float _minAge, float _maxAge, Vector3 _minVelocity, Vector3 _maxVelocity,
		float _damping, float _radius, Vector4 _color) {
		type = _type;
		minAge=_minAge;
		maxAge=_maxAge;
		minVelocity=_minVelocity;
		maxVelocity=_maxVelocity;
		damping = _damping;
		radius=_radius;
		color=_color;
	}

	unsigned getType() const { return type; }
	std::vector<Payload>& getPayloads() { return payloads; }
	void AddPlayload(const Payload& _payload) {
		payloads.push_back(_payload);
	}

	void create(Firework* firework, const Firework* parent = NULL);
};
#endif
