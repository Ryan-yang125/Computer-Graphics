#include "ParticleFountain.h"

ParticleFountain::ParticleFountain(int numParticles) : 
	ParticleEmitter(numParticles, 6.0f, FOUNTAIN_PARTICLE_LIFETIME, "water_droplet", vec3(0.0f, -0.5f, 0.0f)) {

	vec3 vel(0.0f);
	float velocity, theta, phi;
	float time = 0.0f, rate = 0.000750f;
	for (int i = 0; i < numParticles; i++) {
		//TODO fountain v set
		// get the direction of the initial velocity
		theta = mix(0.0f, PI / 6.0f, float(rand()) / RAND_MAX);
		phi = mix(0.0f, 2.0f * PI, float(rand()) / RAND_MAX);
		vel.x = sinf(theta) * cosf(phi);
		vel.y = cosf(theta);
		vel.z = sinf(theta) * sinf(phi);

		// scale to get the magnitude of the initial velocity
		velocity = mix(1.25f, 1.5f, float(rand() / RAND_MAX));
		vel = vel * velocity;

		// push back the particle with the given velocity and start time
//		particles.push_back(ParticleData(vel, time));
		positions.push_back(vec3(0,0,0));
		velocities.push_back(vel);
		startTimes.push_back(time);
		time += rate;
	}

}

void ParticleFountain::update(float elapsedTime) {

}
