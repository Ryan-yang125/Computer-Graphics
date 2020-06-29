#ifndef FAN_H
#define FAN_H

// FAN MODELED IN INCHES
#define FAN_BASE_HEIGHT 1.5f
#define FAN_RAD_INNER 2.0f
#define FAN_STEM_LENGTH 36.0f
#define FAN_STEM_RAD 0.5f
#define BLADE_LENGTH 8.0f

#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"
#include "Constants.h"
#include "Utils.h"

using namespace std;

class Fan {

public:

	// initialize fan with the given position
	Fan(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

	// return fan position as a glm::vec3
	glm::vec3 getPos() const;

	// set the rotation of the fan blades
	void setRotation(float value);

	// render the fan
	void draw(MatrixStack& mViewStack);
	
	void drawSkewedDisk(MatrixStack& mViewStack, float lowerRad, float upperRad,
		float height, int slices);
	
	void drawPinwheel(MatrixStack& mViewStack, float rotation, int blades, glm::vec3 colors[]);

private:
	void drawBaseAndStem(MatrixStack& mViewStack);
	void drawBlades(MatrixStack& mViewStack);
	glm::vec3 pos;
	glm::vec3 colors[4];
	int blades;
	float rotation;
};


#endif