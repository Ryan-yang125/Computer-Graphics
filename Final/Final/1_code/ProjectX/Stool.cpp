#include "Stool.h"

// construct objects
StoolModel::StoolModel(vec3 ambient, vec3 diffuse, vec3 specular) :
	seatSurface(ambient, diffuse, specular, 50.0f), 
	seatSide(ambient, diffuse, specular, 50.0f),
	largeSkewedDisk(ambient, diffuse, specular, 50.0f),
	smallSkewedDisk(ambient, diffuse, specular, 50.0f),
	stemCylinder(ambient, diffuse, specular, 50.0f),
	stemBottom(ambient, diffuse, specular, 50.0f),
	leg(ambient, diffuse, specular, 50.0f),
	ring(ambient, diffuse, specular, 50.0f),
	topDiskCylinder(ambient, diffuse, specular, 50.0f),
	topDiskSurface(ambient, diffuse, specular, 50.0f),
	bottomDiskCylinder(ambient, diffuse, specular, 50.0f),
	bottomDiskSurface(ambient, diffuse, specular, 50.0f)
{}

// initialize object meshes
bool StoolModel::initMesh() {
	// have to initialize inner radius to some very small value epsilon in order to avoid some weird
	// lighting side effects of having an inner radius of 0
	if (!seatSurface.init(EPSILON, SEAT_DIAM / 2, 16)) return false;	
	if (!seatSide.init(SEAT_DIAM / 2, SEAT_DIAM / 2, 16, SEAT_THICKNESS)) return false;
	if (!largeSkewedDisk.init(SEAT_DIAM / 2 - 2.5f, SEAT_DIAM / 2, 16, 0.5f)) return false;
	if (!smallSkewedDisk.init(STEM_DIAM / 2, STEM_DIAM / 2 + 1, 10, 0.2f)) return false;
	if (!stemCylinder.init(STEM_DIAM / 2, STEM_DIAM / 2, 10, STEM_LENGTH)) return false;
	if (!stemBottom.init(EPSILON, STEM_DIAM / 2, 10)) return false;
	if (!leg.init()) return false;
	if (!ring.init(RING_OUTER_RAD, RING_THICKNESS, 20, 8)) return false;
	if (!topDiskCylinder.init(TOP_DISK_RAD, TOP_DISK_RAD, 16, DISK_THICKNESS)) return false;
	if (!topDiskSurface.init(STEM_DIAM / 2, TOP_DISK_RAD, 16)) return false;	
	if (!bottomDiskCylinder.init(BOT_DISK_RAD, BOT_DISK_RAD, 16, DISK_THICKNESS)) return false;
	if (!bottomDiskSurface.init(STEM_DIAM / 2, BOT_DISK_RAD, 16)) return false;	

	return true;
}

bool StoolModel::draw(Shader &shader, MatrixStack &mvs, const mat4 &proj) {
	mvs.push();
	bool success;

	// position stool with feet on the floor
	mvs.active = translate(mvs.active, vec3(0.0f, STOOL_HEIGHT, 0.0f));

	// seat and stem rendering
	mvs.push();
	mvs.active = translate(mvs.active, vec3(0.0f, heightAdjust, 0.0f));
	success = drawSeatAndStem(shader, mvs, proj);
	if (!success) return false;
	mvs.pop();

	// leg rendering
	success = drawLeg(shader, mvs, proj, 0);
	if (!success) return false;
	success = drawLeg(shader, mvs, proj, 90);
	if (!success) return false;
	success = drawLeg(shader, mvs, proj, 180);
	if (!success) return false;
	success = drawLeg(shader, mvs, proj, 270);
	if (!success) return false;

	// draw lower ring
	success = drawRing(shader, mvs, proj);
	if (!success) return false;

	// draw top and bottom disks
	success = drawDisk(shader, mvs, proj, topDiskSurface, topDiskCylinder, TOP_DISK_HEIGHT);
	if (!success) return false;
	success = drawDisk(shader, mvs, proj, bottomDiskSurface, bottomDiskCylinder, BOT_DISK_HEIGHT);
	if (!success) return false;

	mvs.pop();
	return true;
}

bool StoolModel::drawSeatAndStem(Shader &shader, MatrixStack &mvs, const mat4 &proj) {
	mvs.push();
	bool success;

	// draw top of stool seat
	// no translation needed since top height is at 0
	success = seatSurface.draw(shader, mvs.active, proj);
	if (!success) return false;

	mvs.push();
	// move down and draw the seat side
	// we don't need to draw the bottom of the seat because it is hidden by the
	// skewed disks anyway.
	mvs.active = translate(mvs.active, vec3(0.0f, -SEAT_THICKNESS, 0.0f));
	success = seatSide.draw(shader, mvs.active, proj);
	if (!success) return false;

	// draw skewed disks below seat
	mvs.push();
	// large skewed disk
	mvs.push();
	mvs.active = scale(mvs.active, vec3(-1.0f, -1.0f, -1.0f));
	success = largeSkewedDisk.draw(shader, mvs.active, proj);
	if (!success) return false;
	mvs.pop();
	
	// small skewed disk and connecting disk
	mvs.push();
	mvs.active = translate(mvs.active, vec3(0.0f, -0.5f, 0.0f));
	mvs.active = scale(mvs.active, vec3(-1.0f, -1.0f, -1.0f));
	success = smallSkewedDisk.draw(shader, mvs.active, proj);
	if (!success) return false;

	// use the same disk as the seat surface for the connecting disk, but scale it accordingly
	float scaleFactor = (SEAT_DIAM / 2 - 2.5f) / (SEAT_DIAM / 2);
	mvs.active = scale(mvs.active, vec3(scaleFactor, scaleFactor, scaleFactor));
	success = seatSurface.draw(shader, mvs.active, proj);
	if (!success) return false;
	mvs.pop();

	mvs.pop();

	// move down and draw the seat stem and stem cap
	mvs.active = translate(mvs.active, vec3(0.0f, -STEM_LENGTH, 0.0f));
	success = stemCylinder.draw(shader, mvs.active, proj);
	if (!success) return false;
	// invert the facing direction of the stem cap so that its normal is facing downwards
	mvs.active = scale(mvs.active, vec3(-1.0f, -1.0f, -1.0f));
	success = stemBottom.draw(shader, mvs.active, proj);
	if (!success) return false;

	mvs.pop();

	mvs.pop();
	return true;
}

/*
 * Draws a single leg, rotated about the stool and sheared appropriately
 */
bool StoolModel::drawLeg(Shader &shader, MatrixStack &mvs, const mat4 &proj, float rotation) {
	bool success;
	mat4 shearMat;
	vec4 shearVec(-SHEAR_DIST / (LEG_LENGTH), 1.0f, 0.0f, 0.0f);
	shearMat[1] = shearVec;

	mvs.push();

	// rotate the leg to position it on the stool
	mvs.active = rotate(mvs.active, rotation, vec3(0.0f, 1.0f, 0.0f));

	// stretch it, position it on the ground, and shear it
	mvs.active = mvs.active * shearMat;
	mvs.active = translate(mvs.active,  
		vec3(LEG_HORIZ_OFFSET - SHEAR_DIST, -STOOL_HEIGHT + LEG_LENGTH / 2, 0.0f));
	mvs.active = scale(mvs.active, 
		vec3(LEG_THICKNESS, LEG_LENGTH, LEG_THICKNESS));
	
	success = leg.draw(shader, mvs.active, proj);
	if (!success) return false;

	mvs.pop();
	return true;
}

/*
 * Draw the support ring near the bottom of the stool.
 */
bool StoolModel::drawRing(Shader &shader, MatrixStack &mvs, const mat4 &proj) {
	bool success;

	mvs.push();
	mvs.active = translate(mvs.active, vec3(0.0f, -(STOOL_HEIGHT - RING_HEIGHT), 0.0f));

	success = ring.draw(shader, mvs.active, proj);
	if (!success) return false;

	mvs.pop();
	return true;
}

/*
 * Draw one of the two disk-like objects near the top of the stool.
 * This process is very similar to drawing the seat.
 */
bool StoolModel::drawDisk(Shader &shader, MatrixStack &mvs, const mat4 &proj, 
							 Disk &surface, Cylinder &cylinder, float height) {
	bool success;
	mvs.push();

	// position disk vertically
	mvs.active = translate(mvs.active, vec3(0.0f, -STOOL_HEIGHT + height, 0.0f));

	// draw top side of disk
	// no translation needed since top is at height 0
	success = surface.draw(shader, mvs.active, proj);
	if (!success) return false;

	// move down and draw cylinder and bottom side of disk
	mvs.active = translate(mvs.active, vec3(0.0f, -DISK_THICKNESS, 0.0f));
	success = cylinder.draw(shader, mvs.active, proj);
	if (!success) return false;

	// scale by -1 so that bottom face's normal is correct
	mvs.active = scale(mvs.active, vec3(-1.0f, -1.0f, -1.0f));
	success = surface.draw(shader, mvs.active, proj);
	if (!success) return false;

	mvs.pop();
	return true;
}

void StoolModel::adjustHeight(float amount) {
	heightAdjust += amount;
	heightAdjust = std::max(0.2f, heightAdjust);
	heightAdjust = std::min(heightAdjust, 4.575f);
}


/////////// STOOL METHODS ///////////

/*
 * Initialize the stool to have a given model and position.
 * Note: the model should exist before you try to create a stool to use it.
 */
Stool::Stool(StoolModel *model, vec3 position) : model(model), position(position) {}

/*
 * Draw the stool's model at the stool's location
 */
bool Stool::draw(Shader &shader, MatrixStack &mvs, const mat4 &proj) {
	mvs.push();
	mvs.active = translate(mvs.active, position);
	bool success = model->draw(shader, mvs, proj);
	mvs.pop();

	return success;
}
