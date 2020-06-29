#ifndef PARTICLE_FIRE_H
#define PARTICLE_FIRE_H

#define FIRE_PARTICLE_LIFETIME 1.5f

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
class ParticleFire : public ParticleEmitter {

public:
	ParticleFire(int numParticles);

	void update(float elapsedTime);

};


#endif