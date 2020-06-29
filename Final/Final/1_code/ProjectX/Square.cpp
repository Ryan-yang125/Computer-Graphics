#include "Square.h"

Square::Square(const char *texture) : texture(texture) 
{}

bool Square::init() {
	// check errors before initialization
	if (Utils::GLReturnedError("Square::init - Error on entry"))
		return false;

	// put vertices in the rectangle

	// bottom left
	vertices.push_back(VertexData(
		vec3(-0.5f, -0.5f, 0.0f), 
		vec3(1.0f, 1.0f, 1.0f), 
		vec3(0.0f, 0.0f, 1.0f),
		vec2(0.0f, 1.0f)));
	// bottom right
	vertices.push_back(VertexData(
		vec3(0.5f, -0.5f, 0.0f), 
		vec3(1.0f, 1.0f, 1.0f), 
		vec3(0.0f, 0.0f, 1.0f),
		vec2(1.0f, 1.0f)));
	// top left
	vertices.push_back(VertexData(
		vec3(-0.5f, 0.5f, 0.0f), 
		vec3(1.0f, 1.0f, 1.0f),
		vec3(0.0f, 0.0f, 1.0f),
		vec2(0.0f, 0.0f)));
	// top left
	vertices.push_back(VertexData(
		vec3(-0.5f, 0.5f, 0.0f), 
		vec3(1.0f, 1.0f, 1.0f),
		vec3(0.0f, 0.0f, 1.0f),
		vec2(0.0f, 0.0f)));
	// bottom right
	vertices.push_back(VertexData(
		vec3(0.5f, -0.5f, 0.0f), 
		vec3(1.0f, 1.0f, 1.0f), 
		vec3(0.0f, 0.0f, 1.0f),
		vec2(1.0f, 1.0f)));
	// top right
	vertices.push_back(VertexData(
		vec3(0.5f, 0.5f, 0.0f), 
		vec3(1.0f, 1.0f, 1.0f),
		vec3(0.0f, 0.0f, 1.0f),
		vec2(1.0f, 0.0f)));

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
	// 4 - texture
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
	if (Utils::GLReturnedError("Square::init - Error on entry"))
		return false;

	return true;
}

bool Square::draw(Shader &shader, MatrixStack &mvs, const mat4 &proj) {
	if (Utils::GLReturnedError("Square::draw - Error on entry"))
		return false;
	mvs.push();

	mat4 mvp = proj * mvs.active;
	shader.use();
	shader.setUniform("mvMat", mvs.active);
	shader.setUniform("projMat", proj);
	shader.setUniform("normalMat", transpose(inverse(mvs.active)));
	shader.setUniform("mvp", mvp);
	if (texture != NULL) {
		shader.setTexture("spriteTexture", 0);
		TextureManager::get()->useTexture(texture);
	}
	glBindVertexArray(vertexArrayHandle);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &this->indices[0]); 
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);
	TextureManager::get()->unbindTexture();

	if (Utils::GLReturnedError("Square::draw - Error on exit"))
		return false;

	mvs.pop();
	return true;
}

void Square::takeDown() {

}
