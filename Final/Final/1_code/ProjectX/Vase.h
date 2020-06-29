#ifndef VASE_H
#define VASE_H

#include <iostream>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"
#include "Constants.h"
#include "Mesh.h"
#include "VertexData.h"
#include "Cylinder.h"

#define VASE_VSTEP_SIZE 2.0f
#define VASE_RSTEP_SIZE 0.1f * PI

using namespace glm;

/*
 * The Vase class draws what is basically a cylinder, augmented by 
 * a sine wave. This allows for some interesting and realistic 
 * looking curvatures, used to model various curved, vase-like
 * objects.
 */
class VaseModel {
public:

	/* Creates a vase.
	 *
	 * curveMag: adjusts the magnitude of the curvature
	 * curveFreq: adjusts the frequency of the curvature
	 * curveOffset: shifts the curvature up or down
	 * slices: number of horizontal slices
	 * stacks: number of vertical stacks
	 */
	VaseModel(vec3 ambient,
		vec3 diffuse,
		vec3 specular,
		float height,
		float radius,
		float curveMag, 
		float curveFreq, 
		float curveOffset,
		int slices,
		int stacks);

	bool initMesh();

	bool draw(Shader &shader, MatrixStack &mvs, mat4 proj);

private:
	float height, cMag, cFreq, cOffset, rad;
	int slices, stacks;
	float r, g, b;

	Mesh mesh;
	Disk base;

};


#endif