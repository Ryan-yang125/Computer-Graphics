#ifndef TORUS_H
#define TORUS_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexData.h"
#include "Utils.h"
#include "Shader.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Constants.h"

/**
 * A donut-shaped object with a hole in the middle. A torus may be specified
 * with an radius and a thickness component. The thickness component specifies
 * the radius of the solid portion of the torus, while the radius specifies 
 * the radius from the center of the torus to the center of the solid portion.
 */
class Torus {

public:
	Torus(vec3 matAmbient, vec3 matDiffuse, vec3 matSpecular, float shine);
	virtual bool init(float radius, float thickness, int bigSlices, int littleSlices);
	virtual bool draw(Shader &shader, mat4 &mv, const mat4 &proj);

private:
	Mesh mesh;
};

#endif