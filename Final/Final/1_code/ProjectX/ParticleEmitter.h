#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MatrixStack.h"
#include "ParticleData.h"
#include "Utils.h"
#include "Shader.h"
#include "ParticleShader.h"
#include "Constants.h"
#include "TextureManager.h"

using namespace glm;

/*
 * This class is a test class for a simple particle system. 
 * Much of the code is lifted from the OpenGL 4.0 Shading Language Cookbook
 */
class ParticleEmitter {

public:
	ParticleEmitter(
		int numParticles, 
		float particleSize, 
		float lifetime, 
		const char *texture, 
		vec3 acceleration);

	virtual void update(float elapsedTime);

	virtual bool draw(ParticleShader &shader, MatrixStack &mvs, mat4 proj, float time);
	virtual bool initGL();

protected:
	vector<vec3> positions;
	vector<vec3> velocities;
	vector<GLfloat> startTimes;

	float particleLifetime, particleSize;
	const char *texture;
	vec3 acceleration; // how much the particles accelerate per second
	//vector<ParticleData> particles;

	GLuint particleArray[2];
	GLuint feedback[2];
	GLuint posBuf[2];
	GLuint velBuf[2];
	GLuint startBuf[2];
	GLuint initVelBuf;
	GLuint drawBuf;

	GLuint vertexArrayHandle;
	GLuint vertexBufferHandle;
};


#endif