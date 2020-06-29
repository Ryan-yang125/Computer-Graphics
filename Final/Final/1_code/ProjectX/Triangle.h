#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexData.h"
#include "Utils.h"
#include "Shader.h"
#include "MatrixStack.h"
#include "TextureManager.h"

using namespace std;
using namespace glm;

class Triangle {
public:
	Triangle();
	bool init();
	bool draw(Shader &shader, MatrixStack &mvs, const mat4 &proj, const ivec2 &size, const float time);
	void takeDown();

private:
	Shader texShader;
	GLuint vertexArrayHandle;
	GLuint vertexBufferHandle;
	vector<VertexData> vertices;
	vector<GLuint> indices;

	vec3 Kd;
};


#endif