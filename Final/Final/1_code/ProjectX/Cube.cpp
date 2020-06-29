#include "Cube.h"

Cube::Cube(vec3 matAmbient, vec3 matDiffuse, vec3 matSpecular, float shine, const char *texture) : 
	Object(matAmbient, matDiffuse, matSpecular, shine),
	texture(texture)
{}

bool Cube::init() {
	// first, check for entry errors
	if (Utils::GLReturnedError("Cube::init - Error on entry"))
		return false;

	initVertices();

	// get handle for whole bundle
	glGenVertexArrays(1, &vertexArrayHandle);
	glBindVertexArray(vertexArrayHandle);

	// allocate a GPU buffer
	glGenBuffers(1, &vertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), &vertices[0], GL_STATIC_DRAW);

	// setup buffer layout
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) sizeof(vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) (2 * sizeof(vec3)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) (3 * sizeof(vec3)));
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) (4 * sizeof(vec3)));

	// enable vertex attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	// unbind vertex and buffer handles
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// check for exit errors
	if (Utils::GLReturnedError("Cube::init - Error on entry"))
		return false;

	return true;
}

void Cube::initVertices() {
	// front face
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, 0.5f), color, vec3(0, 0, 1.0f), vec2(0.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), color, vec3(0, 0, 1.0f), vec2(1.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, 0.5f), color, vec3(0, 0, 1.0f), vec2(0.0f, 0.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), color, vec3(0, 0, 1.0f), vec2(1.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), color, vec3(0, 0, 1.0f), vec2(1.0f, 0.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, 0.5f), color, vec3(0, 0, 1.0f), vec2(0.0f, 0.0f)));

	// back face
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), color, vec3(0, 0, -1.0f), vec2(1.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), color, vec3(0, 0, -1.0f), vec2(1.0f, 0.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, -0.5f), color, vec3(0, 0, -1.0f), vec2(0.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, -0.5f), color, vec3(0, 0, -1.0f), vec2(0.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), color, vec3(0, 0, -1.0f), vec2(1.0f, 0.0f)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, -0.5f), color, vec3(0, 0, -1.0f), vec2(0.0f, 0.0f)));

	// top face
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, 0.5f), color, vec3(0, 1.0f, 0), vec2(0.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), color, vec3(0, 1.0f, 0), vec2(1.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), color, vec3(0, 1.0f, 0), vec2(0.0f, 0.0f)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), color, vec3(0, 1.0f, 0), vec2(1.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, -0.5f), color, vec3(0, 1.0f, 0), vec2(1.0f, 0.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), color, vec3(0, 1.0f, 0), vec2(0.0f, 0.0f)));

	// bottom face
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, 0.5f), color, vec3(0, -1.0f, 0), vec2(1.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), color, vec3(0, -1.0f, 0), vec2(1.0f, 0.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), color, vec3(0, -1.0f, 0), vec2(0.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), color, vec3(0, -1.0f, 0), vec2(0.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), color, vec3(0, -1.0f, 0), vec2(1.0f, 0.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, -0.5f), color, vec3(0, -1.0f, 0), vec2(0.0f, 0.0f)));

	// right face
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), color, vec3(1.0f, 0, 0), vec2(0.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, -0.5f), color, vec3(1.0f, 0, 0), vec2(1.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, -0.5f), color, vec3(1.0f, 0, 0), vec2(1.0f, 0.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), color, vec3(1.0f, 0, 0), vec2(0.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, -0.5f), color, vec3(1.0f, 0, 0), vec2(1.0f, 0.0f)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), color, vec3(1.0f, 0, 0), vec2(0.0f, 0.0f)));

	// left face
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, 0.5f), color, vec3(-1.0f, 0, 0), vec2(1.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), color, vec3(-1.0f, 0, 0), vec2(0.0f, 0.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), color, vec3(-1.0f, 0, 0), vec2(0.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, 0.5f), color, vec3(-1.0f, 0, 0), vec2(1.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, 0.5f), color, vec3(-1.0f, 0, 0), vec2(0.0f, 0.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), color, vec3(-1.0f, 0, 0), vec2(1.0f, 0.0f)));
}

bool Cube::draw(Shader &shader, mat4 &mv, const mat4 &proj) {
	// first, check for entry errors
	if (Utils::GLReturnedError("Cube::init - Error on entry"))
		return false;

	mat4 mvp = proj * mv;

	// push uniforms to the shader
	shader.use();
	shader.setUniform("mvMat", mv);
	shader.setUniform("projMat", proj);
	shader.setUniform("normalMat", transpose(inverse(mv)));
	shader.setUniform("mvp", mvp);

	if (texture != NULL) {
		shader.setTexture("spriteTexture", 0);
		TextureManager::get()->useTexture(texture);
	}
	else {
		shader.setUniform("Kd", materialDiffuse);
		shader.setUniform("Ka", materialAmbient);
		shader.setUniform("Ks", materialSpecular);
		shader.setUniform("shine", shine);
	}


	glBindVertexArray(vertexArrayHandle);

	if (Mesh::drawPoints)
		glDrawArrays(GL_POINTS, 0, vertices.size());
	else
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);
	
	// check for exit errors
	if (Utils::GLReturnedError("Cube::init - Error on entry"))
		return false;

	return true;
}


