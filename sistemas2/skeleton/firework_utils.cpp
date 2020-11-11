#pragma once
#include "firework_utils.hpp"
#include "random.hpp"
const Vector3 GRAVITY(0.0f, -10.0f, 0.0f);

std::vector<Firework*> fireworks;
std::vector<FireworkRule*> rules;

std::vector<FireworkRule*>& getFireworksRules() { return rules; }


void FireworkRule::create(Firework* firework, const Firework* parent) {

	firework->type = type;
	firework->age = randomf(minAge, maxAge);

	Vector3 vel;
	if (parent) {
		firework->setPosition(parent->getPosition());
		vel += parent->getVelocity();
	}
	else {

		int x = randomf(0.0, 3.0f) - 1;
		Vector3 start(5.0f * x, 0.0f, 0.0f);
		firework->setPosition(start);
	}

	vel += randomv(minVelocity, maxVelocity);
	//vel += maxVelocity;

	firework->setVelocity(vel);

	firework->setMass(1);
	firework->setDamping(damping);
	firework->setAcceleration(GRAVITY);
	firework->activate(radius, color);

}

FireworkRule* GetRuleFromType(unsigned type) {
	for (auto it = rules.begin(); it != rules.end(); ++it) {
	
		FireworkRule* rule = (*it);
		if (rule->getType() == type)
			return rule;
	}
	return NULL;
}

Firework* AllocNewFirework() {
	if (fireworks.capacity() == 0) {
		fireworks.reserve(2000);
	}
	for (auto it = fireworks.begin(); it != fireworks.end(); ++it) {

		Firework* f = (*it);
		if (f->isActive()) {
			return f;
		}
	}

	if (fireworks.size() < 2000) {
		Firework* f = new Firework();
		fireworks.push_back(f);
		return f;
	}
	else return NULL;

}


void FireworksCreate(unsigned type, Firework* parent) {
	FireworkRule* rule = GetRuleFromType(type);
	if (!rule)
		return;

	Firework* newFirework = AllocNewFirework();
	if (!newFirework)
		return;
	rule->create(newFirework, parent);
}

void create(unsigned type, unsigned count, Firework* parent) {
	for (unsigned int i = 0; i < count; i++) {
		FireworksCreate(type, parent);
	}
}

void FireworksUpdate(float t) {
	for (auto it = fireworks.begin(); it != fireworks.end(); ++it) {
	
		Firework* f = (*it);
		if (f->isActive()) {
			if (f->update(t)) {
				FireworkRule* rule = GetRuleFromType(f->getType());

				for (auto itPayload = rule->getPayloads().begin(); itPayload != rule->getPayloads().end(); ++itPayload) {
					Payload& p = (*itPayload);
					create(p.type, p.count, f);
				}
				f->setInactive();
			}
		}
	}
}
