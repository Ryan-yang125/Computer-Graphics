#include "MatrixStack.h"

MatrixStack::MatrixStack() {}

void MatrixStack::push() {
	matStack.push(active);
}

void MatrixStack::pop() {
	active = matStack.top();
	matStack.pop();
}