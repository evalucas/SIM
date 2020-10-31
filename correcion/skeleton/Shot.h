#pragma once
#ifndef _SHOT_H_
#define _SHOT_H_

#include "Particle.hpp"

class Shot {
public: 
	Shot();
	~Shot();

	Particle particle;
	double startTime;
	unsigned type;
};
#endif 
