#include "Object.h"

Object::Object(vec3 matAmbient, vec3 matDiffuse, vec3 matSpecular, float shine) : 
	materialAmbient(matAmbient), materialDiffuse(matDiffuse), 
	materialSpecular(matSpecular), shine(shine) {}

Object::~Object() {
	this->takeDown();
}



void Object::takeDown() {
	if (this->vertexArrayHandle != GLuint(-1)) {
		glDeleteVertexArrays(1, &this->vertexArrayHandle);
	}

	if (this->vertexBufferHandle != GLuint(-1)) {
		glDeleteBuffers(1, &this->vertexBufferHandle);
	}

	this->vertexArrayHandle = this->vertexBufferHandle = GLuint(-1);
}