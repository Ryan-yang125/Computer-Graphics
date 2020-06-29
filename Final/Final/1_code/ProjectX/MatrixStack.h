#ifndef MATRIX_STACK_H
#define MATRIX_STACK_H

#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

class MatrixStack {
public:
	// initialized to identity
	glm::mat4 active;

	// Active matrix is left as the identity matrix
	MatrixStack();

	// push the current active matrix onto the top of the stack
	void push();	

	// pop the top matrix off the stack and set it as the active matrix
	void pop();

private:
	std::stack<glm::mat4> matStack;
};


#endif