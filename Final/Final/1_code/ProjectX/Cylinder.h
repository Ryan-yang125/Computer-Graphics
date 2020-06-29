#ifndef CYLINDER_H
#define CYLINDER_H

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
 * A disk shape, possibly with a hole in the middle. The disk may have
 * a height. Make sure that inner radius is smaller than outer radius. If it
 * is not, lighting may be broken.
 */
class Cylinder {

public:
	Cylinder(vec3 matAmbient, vec3 matDiffuse, vec3 matSpecular, float shine);
	virtual bool init(float innerRad, float outerRad, int slices, float height);
	virtual bool draw(Shader &shader, mat4 &mv, const mat4 &proj);

private:
	Mesh mesh;
};

class Disk : public Cylinder {

public:
	Disk(vec3 matAmbient, vec3 matDiffuse, vec3 matSpecular, float shine);
	virtual bool init(float innerRad, float outerRad, int slices);


};




#endif