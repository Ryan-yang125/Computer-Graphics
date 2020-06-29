#ifndef FIREPLACE_H
#define FIREPLACE_H

#ifndef METERS_PER_INCH
#define METERS_PER_INCH 0.0254f
#endif

// all units measured
#define FP_SIDE_HEIGHT 36.0f
#define FP_BLOCK_THICKNESS 12.0f
#define FP_WIDTH 72.0f
#define FP_CHIMNEY_HEIGHT 100.0f
#define FP_CHIMNEY_WIDTH 20.0f
#define FP_PLATFORM_HEIGHT 4.0f

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MatrixStack.h"
#include "Constants.h"
#include "Shader.h"
#include "Cube.h"
#include "ParticleFire.h"
#include "Square.h"

/*
 * A class which holds the model for a fireplace, fire included. This may be
 * placed around the scene, but should be positioned against a wall for best
 * effect. The fireplace will be modeled and the fire will be
 * modeled in meters.
 */
class Fireplace {

public:
	Fireplace(vec3 pos, vec3 ambient, vec3 diff, vec3 spec);

	// initialize the cube mesh
	bool initMesh();

	bool draw(Shader &shader, MatrixStack &mvs, const mat4 &proj, float time);

	vec3 getPos() { return position; }
	void setFireShader(ParticleShader *shader) { fireShader = shader; }

private:
	bool drawSide(Shader &shader, MatrixStack &mvs, const mat4 &proj, float xOffset);
	Cube cube;
	Square backdrop;
	ParticleFire fire;
	vec3 position;
	ParticleShader *fireShader;


};


#endif