#ifndef GRID_H
#define GRID_H

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

using namespace std;
using namespace glm;

class Grid {

public:
	Grid(vec3 matAmbient, vec3 matDiffuse, vec3 matSpecular, float shine);
	bool init(int sizeX, int sizeZ);

	bool draw(Shader &shader,  mat4 &mv, const mat4 &proj);

private:
	Mesh mesh;
};


#endif