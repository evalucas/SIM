#pragma once

#define NOMINMAX

#include "random.hpp"
#include "core.hpp"

//float randomf(float _min, float _max) {
//
//	float r = static_cast<float>(std::rand()) / RAND_MAX;
//	r *= (_max - _min);
//	r += _min;
//
//	return r;
//}
//
//Vector3 randomv(const Vector3& _min, const Vector3& _max) {
//	Vector3 res;
//	res.x = randomf((std::min)(_min.x, _max.x), (std::max)(_min.x, _max.x));
//	res.y = randomf((std::min)(_min.y, _max.y), (std::max)(_min.y, _max.y));
//	res.z = randomf((std::min)(_min.z, _max.z), (std::max)(_min.z, _max.z));
//	return res;
//}