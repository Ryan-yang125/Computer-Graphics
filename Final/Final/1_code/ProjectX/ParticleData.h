#ifndef PARTICLE_DATA_H
#define PARTICLE_DATA_H

#include <glm/glm.hpp>

using namespace glm;

/*
 * Holds the data for one vertex
 */
class ParticleData {
public:

	ParticleData(vec3 v, float s);
	
	vec3 velocity;
	float startTime;
	vec3 position;
};


#endif