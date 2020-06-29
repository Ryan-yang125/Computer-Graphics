#ifndef STOOL_H
#define STOOL_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MatrixStack.h"
#include "Constants.h"
#include "Shader.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Torus.h"

// All measurements
#define STOOL_HEIGHT 24.75f

#define SEAT_THICKNESS 0.5f
#define SEAT_DIAM 11.75f
#define STEM_LENGTH 10.5f
#define STEM_DIAM 1.05f

#define LEG_LENGTH 23.75f
#define LEG_THICKNESS 1.25f
#define LEG_HORIZ_OFFSET 8.8125f
#define SHEAR_DIST 5.98f

#define RING_OUTER_RAD 6.40f
#define RING_THICKNESS 0.35f
#define RING_HEIGHT 7.0f

#define TOP_DISK_RAD 2.8f
#define TOP_DISK_HEIGHT 23.75f
#define BOT_DISK_RAD 3.3f
#define BOT_DISK_HEIGHT 21.25f
#define DISK_THICKNESS 0.8f

using namespace std;
using namespace glm;


/*
 * A class which holds the model for a stool.
 * This class is to hold the rendering information and shoud not actually
 * be place into a scene. To place a stool, create an instance of the Stool
 * class instead.
 */
class StoolModel {

public:
	StoolModel(vec3 ambient, vec3 diffuse, vec3 specular);
	bool draw(Shader &shader, MatrixStack &mvs, const mat4 &proj);

	// adjust the height of the stool (up or down)
	void adjustHeight(float amount);

	// initialize the meshes of the ojbects making up this stool.
	bool initMesh();
private:
	bool drawSeatAndStem(Shader &shader, MatrixStack &mvs, const mat4 &proj);
	bool drawLeg(Shader &shader, MatrixStack &mvs, const mat4 &proj, float rotation);
	bool drawRing(Shader &shader, MatrixStack &mvs, const mat4 &proj);
	bool drawDisk(Shader &shader, MatrixStack &mvs, const mat4 &proj, float radius, float height);
	bool drawDisk(Shader &shader, MatrixStack &mvs, const mat4 &proj, Disk &surface, Cylinder &cylinder, float height);

	// seat and stem
	Disk seatSurface;
	Cylinder seatSide;
	Cylinder largeSkewedDisk;
	Cylinder smallSkewedDisk;
	Cylinder stemCylinder;
	Disk stemBottom;
	// legs
	Cube leg;
	// ring
	Torus ring;
	// disks
	Cylinder topDiskCylinder;
	Disk topDiskSurface;
	Cylinder bottomDiskCylinder;
	Disk bottomDiskSurface;

	// height adjustment
	float heightAdjust;
};

/*
 * A wrapper class for StoolModel that allows you to position stools
 * and place them around the scene.
 */
class Stool {

public: 
	Stool(StoolModel *model, vec3 position);
	bool draw(Shader &shader, MatrixStack &mvs, const mat4 &proj);

	vec3 position;
private:
	StoolModel *model;
};



#endif