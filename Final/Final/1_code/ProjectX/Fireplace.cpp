#include "Fireplace.h"

Fireplace::Fireplace(vec3 pos, vec3 ambient, vec3 diff, vec3 spec) :
	position(pos),
	cube(ambient, diff, spec, 10.0f, "brick"),
	fire(3000),
	backdrop("brick")
{}

bool Fireplace::initMesh() {
	if (!cube.init()) return false;
	if (!fire.initGL()) return false;
	if (!backdrop.init()) return false;

	return true;
}

bool Fireplace::draw(Shader &shader, MatrixStack &mvs, const mat4 &proj, float time) {
	mvs.push();
	bool success;

	mvs.active = translate(mvs.active, this->position);

	
	// Draw backdrop using squares
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			mvs.push();
			mvs.active = scale(mvs.active, vec3(METERS_PER_INCH, METERS_PER_INCH, METERS_PER_INCH));
			mvs.active = translate(mvs.active, vec3(FP_BLOCK_THICKNESS * j, FP_BLOCK_THICKNESS * i, 0.0f));
			mvs.active = translate(mvs.active, 
				vec3(
				-(FP_WIDTH / 2 - FP_BLOCK_THICKNESS / 2) + FP_BLOCK_THICKNESS, 
				0.5f * FP_BLOCK_THICKNESS, 
				+ 0.01f));
			mvs.active = scale(mvs.active, vec3(FP_BLOCK_THICKNESS, FP_BLOCK_THICKNESS, FP_BLOCK_THICKNESS));
			backdrop.draw(shader, mvs, proj);
			mvs.pop();
		}

	}

	// draw platform
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			mvs.push();
			mvs.active = scale(mvs.active, vec3(METERS_PER_INCH, METERS_PER_INCH, METERS_PER_INCH));
			mvs.active = translate(mvs.active, vec3(FP_BLOCK_THICKNESS * j, 0.0f, FP_BLOCK_THICKNESS * i));
			mvs.active = translate(mvs.active, 
				vec3(
				-(FP_WIDTH / 2 - FP_BLOCK_THICKNESS / 2), 
				0.5 * FP_PLATFORM_HEIGHT, 
				FP_BLOCK_THICKNESS / 2));
			mvs.active = scale(mvs.active, vec3(FP_BLOCK_THICKNESS, FP_PLATFORM_HEIGHT, FP_BLOCK_THICKNESS));
			cube.draw(shader, mvs.active, proj);
			mvs.pop();
		}

	}


	// draw whichever side is further first (to handle wierd transparency issues)

	// if the right side is further from the camera 
	// (0,0,0) > (1,0,0) because positive z points towards us
	mvs.push();
	mvs.active = scale(mvs.active, vec3(METERS_PER_INCH, METERS_PER_INCH, METERS_PER_INCH));
	if ((mvs.active * vec4(0,0,0,1)).z > (mvs.active * vec4(1,0,0,1)).z) {
		success = drawSide(shader, mvs, proj, FP_WIDTH / 2 - FP_BLOCK_THICKNESS / 2);
		if (!success) return false;
	}
	else {
		success = drawSide(shader, mvs, proj, -(FP_WIDTH / 2 - FP_BLOCK_THICKNESS / 2));
		if (!success) return false;
	}
	mvs.pop();
	
	mvs.push();
	mvs.active = translate(mvs.active, vec3(0.0f, FP_PLATFORM_HEIGHT * METERS_PER_INCH, 0.05f));
	fire.draw(*fireShader, mvs, proj, time);
	mvs.pop();

	mvs.active = scale(mvs.active, vec3(METERS_PER_INCH, METERS_PER_INCH, METERS_PER_INCH));

	// draw whichever side wasn't drawn already
	if ((mvs.active * vec4(0,0,0,1)).z > (mvs.active * vec4(1,0,0,1)).z) {
		success = drawSide(shader, mvs, proj, -(FP_WIDTH / 2 - FP_BLOCK_THICKNESS / 2));
		if (!success) return false;
	}
	else {
		success = drawSide(shader, mvs, proj, FP_WIDTH / 2 - FP_BLOCK_THICKNESS / 2);
		if (!success) return false;
	}

	// draw sides of fireplace
	//success = drawSide(shader, mvs, proj, FP_WIDTH / 2 - FP_BLOCK_THICKNESS / 2);
	//if (!success) return false;
	//success = drawSide(shader, mvs, proj, -(FP_WIDTH / 2 - FP_BLOCK_THICKNESS / 2));
	//if (!success) return false;

	// draw top of fireplace
	for (int i = 0; i < 6; i++) {
		mvs.push();
		mvs.active = translate(mvs.active, vec3(FP_BLOCK_THICKNESS * i, 0.0f, 0.0f));
		mvs.active = translate(mvs.active, 
			vec3(-(FP_WIDTH / 2 - FP_BLOCK_THICKNESS / 2), 3.5 * FP_BLOCK_THICKNESS, 0.0f));
		mvs.active = scale(mvs.active, vec3(FP_BLOCK_THICKNESS, FP_BLOCK_THICKNESS, FP_BLOCK_THICKNESS));
		cube.draw(shader, mvs.active, proj);
		mvs.pop();
	}


	// draw chimney
	for (int i = 0; i < 6; i++) {
		mvs.push();
		mvs.active = translate(mvs.active, vec3(0.0f, FP_BLOCK_THICKNESS * i, 0.0f));
		mvs.active = translate(mvs.active, 
			vec3(0.0f, FP_BLOCK_THICKNESS * 4.5, -FP_BLOCK_THICKNESS / 4));
		mvs.active = scale(mvs.active, vec3(FP_CHIMNEY_WIDTH, FP_BLOCK_THICKNESS, FP_BLOCK_THICKNESS / 2));
		cube.draw(shader, mvs.active, proj);
		mvs.pop();

	}


	mvs.pop();
	return true;
}

bool Fireplace::drawSide(Shader &shader, MatrixStack &mvs, const mat4 &proj, float xOffset) {
	mvs.push();

	mvs.active = translate(mvs.active, vec3(xOffset, 0.0f, 0.0f));

	// place the bottom of the side at 0 in the y direction
	for (int i = 0; i < 3; i++) {
		mvs.push();
		mvs.active = translate(mvs.active, vec3(0.0f, FP_BLOCK_THICKNESS / 2, 0.0f));
		mvs.active = translate(mvs.active, vec3(0.0f, FP_BLOCK_THICKNESS * i, 0.0f));
		mvs.active = scale(mvs.active, vec3(FP_BLOCK_THICKNESS, FP_BLOCK_THICKNESS, FP_BLOCK_THICKNESS));
		bool success = cube.draw(shader, mvs.active, proj);
		if (!success) return false;
		mvs.pop();
	}



	mvs.pop();
	return true;
}
