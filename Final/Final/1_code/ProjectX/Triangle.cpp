#include "Triangle.h"

Triangle::Triangle() {
	Kd = vec3(1.0f, 1.0f, 1.0f);
	
}

bool Triangle::init() {
	// check errors before initialization
	if (Utils::GLReturnedError("Triangle::init - Error on entry"))
		return false;

	// put three vertices in the triangle
	vertices.push_back(VertexData(
		vec3(-1.0f, -1.0f, 0.0f), 
		vec3(1.0f, 1.0f, 1.0f), 
		vec3(0.0f, 0.0f, 1.0f),
		vec2(0.0f, 1.0f)));
	vertices.push_back(VertexData(
		vec3(1.0f, -1.0f, 0.0f), 
		vec3(1.0f, 1.0f, 1.0f), 
		vec3(0.0f, 0.0f, 1.0f),
		vec2(1.0f, 1.0f)));
	vertices.push_back(VertexData(
		vec3(0.0f, 1.0f, 0.0f), 
		vec3(1.0f, 1.0f, 1.0f),
		vec3(0.0f, 0.0f, 1.0f),
		vec2(0.5f, 0.0f)));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	// Get handle for the entire bundle
	glGenVertexArrays(1, &vertexArrayHandle);
	glBindVertexArray(vertexArrayHandle);

	// Generate and move buffer data
	glGenBuffers(1, &vertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(VertexData), &this->vertices[0], GL_STATIC_DRAW);

	// Specify buffer layout
	// 0 - position
	// 1 - color
	// 2 - normal
	// 3 - texture
	glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(VertexData), (GLvoid*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, FALSE, sizeof(VertexData), (GLvoid*) sizeof(vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(VertexData), (GLvoid*) (2 * sizeof(vec3)));
	
	// additional offset due to flat normal
	glVertexAttribPointer(4, 2, GL_FLOAT, FALSE, sizeof(VertexData), (GLvoid*) (4 * sizeof(vec3)));

	// Enable the attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(4);

	// Unbind the buffer and vertex array
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// check errors which occurred in the initialization
	if (Utils::GLReturnedError("Triangle::init - Error on entry"))
		return false;

	return true;
}

bool Triangle::draw(Shader &shader, MatrixStack &mvs, const mat4 &proj, const ivec2 &size, const float time) {
	if (Utils::GLReturnedError("Triangle::draw - Error on entry"))
		return false;
	mvs.push();
	//mvs.active = rotate(mvs.active, time * 90.0f, vec3(0.0f, 1.0f, 0.0f));

	mat4 mvp = proj * mvs.active;
	shader.use();
	shader.setUniform("mvp", mvp);
	shader.setTexture("spriteTexture", 0);
	TextureManager::get()->useTexture("spriteTexture");

	glBindVertexArray(vertexArrayHandle);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &this->indices[0]); 
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);
	TextureManager::get()->unbindTexture();

	if (Utils::GLReturnedError("Triangle::draw - Error on exit"))
		return false;

	mvs.pop();
	return true;
}

void Triangle::takeDown() {

}

