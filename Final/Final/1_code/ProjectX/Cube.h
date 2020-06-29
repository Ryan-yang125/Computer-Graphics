#ifndef CUBE_H
#define CUBE_H

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
#include "Object.h"
#include "TextureManager.h"

using namespace std;
using namespace glm;

class Cube : Object {

public:
	Cube(vec3 matAmbient, vec3 matDiffuse, vec3 matSpecular, float shine, const char *texture = NULL);
	bool init();
	virtual bool draw(Shader &shader, mat4 &mv, const mat4 &proj);

private:
	void initVertices();
	vec3 color;
	const char *texture;
};


#endif