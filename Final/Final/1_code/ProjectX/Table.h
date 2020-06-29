#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"
#include "Cube.h"

// measurements
#define TABLE_HEIGHT 37.325f
#define TABLE_WIDTH 43.25f
#define TABLE_LENGTH 43.25f
#define TABLE_LEG_THICKNESS 2.5f
#define TABLE_TOP_THICKNESS 1.0f
#define TABLE_SIDE_THICKNESS 1.0f

using namespace std;
using namespace glm;

// Contains position and rendering data for a table
class TableModel {

public:
	// initialize table with the given color
	TableModel(vec3 ambient, vec3 diffuse, vec3 specular);

	bool initMesh();

	// render the stool
	bool draw(Shader &shader, MatrixStack &mvs, mat4 proj);

private:
	Cube cube;
	bool drawLeg(Shader &shader, MatrixStack &mvs, mat4 proj, float xOffset, float zOffset);
	bool drawSide(Shader &shader, MatrixStack &mvs, mat4 proj, float xOffset, float zOffset, 
		float xScale, float zScale);
	glm::vec3 pos;
};

#endif