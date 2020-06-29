#ifndef SQUARE_H
#define SQUARE_H

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

class Square {
public:
	Square(const char *texture);
	bool init();
	bool draw(Shader &shader, MatrixStack &mvs, const mat4 &proj);
	void takeDown();

private:
	GLuint vertexArrayHandle;
	GLuint vertexBufferHandle;
	vector<VertexData> vertices;

	const char *texture;
};

#endif