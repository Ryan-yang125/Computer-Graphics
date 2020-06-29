#ifndef PARTICLE_FOUNTAIN_H
#define PARTICLE_FOUNTAIN_H

#define FOUNTAIN_PARTICLE_LIFETIME 10.0f

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
#include "ParticleEmitter.h"

using namespace glm;

/*
 * This class is a test class for a simple particle system. 
 * Much of the code is lifted from the OpenGL 4.0 Shading Language Cookbook
 */
class ParticleFountain : public ParticleEmitter {

public:
	ParticleFountain(int numParticles);

	void update(float elapsedTime);
};


#endif