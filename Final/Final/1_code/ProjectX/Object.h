#ifndef OBJECT_H
#define OBJECT_H

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

class Object {

public:
	Object(vec3 matAmbient, vec3 matDiffuse, vec3 matSpecular, float shine);
	virtual ~Object();
	virtual bool draw(Shader &shader, mat4 &mv, const mat4 &proj) = 0;
	virtual void takeDown();

protected:
	GLuint vertexArrayHandle;
	GLuint vertexBufferHandle;
	vector<VertexData> vertices;

	vec3 materialAmbient;
	vec3 materialDiffuse;
	vec3 materialSpecular;
	float shine;

};


#endif