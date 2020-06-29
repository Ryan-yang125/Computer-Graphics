#include "Fan.h"

Fan::Fan(glm::vec3 position) : pos(position), rotation(0.0f), blades(4) {

	float r, g, b;

	for (int i = 0; i < blades; i++) {
		r = (rand() / float(RAND_MAX) * 0.5f) + 0.5f;
		g = (rand() / float(RAND_MAX) * 0.5f) + 0.5f;
		b = (rand() / float(RAND_MAX) * 0.5f) + 0.5f;
		colors[i] = glm::vec3(r, g, b);
	}
}

glm::vec3 Fan::getPos() const {
	return pos;
}

void Fan::setRotation(float value) {
	rotation = value;
}

void Fan::drawSkewedDisk(MatrixStack& mViewStack, float lowerRad, float upperRad,
	float height, int slices) {
	mViewStack.push();

	glLoadMatrixf(glm::value_ptr(mViewStack.active));

	// Specify color outside function
	//glColor4f(0.1f, 0.4f, 0.4f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	for (float theta = 0; theta <= 2 * PI; theta += 2 * PI / slices) {
		glVertex3f(lowerRad * cos(theta), -height, lowerRad * sin(theta));
		glVertex3f(upperRad * cos(theta), 0.0f, upperRad * sin(theta));
	}
	// two more vertices at beginning for continuity
	glVertex3f(lowerRad * cos(0.0f), -height, lowerRad * sin(0.0f));
	glVertex3f(upperRad * cos(0.0f), 0.0f, upperRad * sin(0.0f));
	glEnd();
	mViewStack.pop();
}

void Fan::drawPinwheel(MatrixStack& mViewStack, float rotation, int blades, glm::vec3 colors[]) {
	mViewStack.push();


	// Set rotation of entire pinwheel
	mViewStack.active = glm::rotate(mViewStack.active, rotation, glm::vec3(0.0f, 1.0f, 0.0f));

	// draw individual blades
	for (int i = 0; i < blades; i++) {
		glColor3f(colors[i].r, colors[i].g, colors[i].b);

		mViewStack.active = glm::rotate(mViewStack.active, 360.0f / blades,
			glm::vec3(0.0f, 1.0f, 0.0f));

		glLoadMatrixf(glm::value_ptr(mViewStack.active));
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(BLADE_LENGTH, -1.0f, 5.0f);
		glVertex3f(3 * BLADE_LENGTH / 4.0f, 0.0f, -0.0f);
		glEnd();

	}
	mViewStack.pop();
}
// Modeled in inches
void Fan::draw(MatrixStack& mViewStack) {
	mViewStack.push();


	// model everything starting at the top of the base
	mViewStack.active = glm::translate(mViewStack.active,
		glm::vec3(0.0f, FAN_BASE_HEIGHT, 0.0f));

	drawBaseAndStem(mViewStack);
	drawBlades(mViewStack);
	mViewStack.pop();
}

void Fan::drawBaseAndStem(MatrixStack& mViewStack) {
	mViewStack.push();

	GLUquadric* q = gluNewQuadric();

	// draw base of fan
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor3f(0.4f, 0.8f, 0.8f);
	drawSkewedDisk(mViewStack, 6.0f, FAN_RAD_INNER, FAN_BASE_HEIGHT, 20);

	mViewStack.push();
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor3f(0.3f, 0.6f, 0.6f);
	gluDisk(q, 0.0f, FAN_RAD_INNER, 20, 1);
	mViewStack.pop();

	// draw stem of fan
	mViewStack.push();
	mViewStack.active = glm::rotate(mViewStack.active, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glColor3f(0.2f, 0.4f, 0.4f);
	gluCylinder(q, FAN_STEM_RAD, FAN_STEM_RAD, FAN_STEM_LENGTH, 6, 1);
	mViewStack.pop();

	gluDeleteQuadric(q);
	mViewStack.pop();
}

void Fan::drawBlades(MatrixStack& mViewStack) {
	mViewStack.push();

	// move blades up to the top of the stem
	mViewStack.active = glm::translate(mViewStack.active,
		glm::vec3(0.0f, FAN_STEM_LENGTH, 0.0f));

	// draw arm to which blades are connected
	mViewStack.push();
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, 0.0f, 0.5f));
	mViewStack.active = glm::scale(mViewStack.active, glm::vec3(1.0f, 1.0f, 2.0f));
	glLoadMatrixf(glm::value_ptr(mViewStack.active));
	glutSolidCube(1.0f);
	mViewStack.pop();

	// draw draw blades
	mViewStack.active = glm::translate(mViewStack.active, glm::vec3(0.0f, 0.0f, 2.0f));
	mViewStack.active = glm::rotate(mViewStack.active, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	drawPinwheel(mViewStack, rotation, blades, colors);

	mViewStack.pop();
}
