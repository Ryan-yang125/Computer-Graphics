#include "Table.h"

TableModel::TableModel(vec3 ambient, vec3 diffuse, vec3 specular) :
	cube(ambient, diffuse, specular, 15.0f)
{}


bool TableModel::initMesh() {
	bool success = cube.init();
	if (!success) return false;
	
	return true;
}

bool TableModel::draw(Shader &shader, MatrixStack &mvs, mat4 proj) {
	mvs.push();

	// position table with feet on the floor
	mvs.active = translate(mvs.active, vec3(0.0f, TABLE_HEIGHT - TABLE_TOP_THICKNESS / 2, 0.0f));

	// draw table top
	mvs.push();
	mvs.active = scale(mvs.active, vec3(TABLE_WIDTH, TABLE_TOP_THICKNESS, TABLE_LENGTH));
	bool success = cube.draw(shader, mvs.active, proj);	
	if (!success) return false;
	mvs.pop();

	// draw legs
	drawLeg(shader, mvs, proj,
		(TABLE_WIDTH - TABLE_LEG_THICKNESS) / 2, 
		(TABLE_LENGTH - TABLE_LEG_THICKNESS) / 2);
	drawLeg(shader, mvs, proj,
		(TABLE_WIDTH - TABLE_LEG_THICKNESS) / 2, 
		-(TABLE_LENGTH - TABLE_LEG_THICKNESS) / 2);
	drawLeg(shader, mvs, proj,
		-(TABLE_WIDTH - TABLE_LEG_THICKNESS) / 2, 
		(TABLE_LENGTH - TABLE_LEG_THICKNESS) / 2);
	drawLeg(shader, mvs, proj,
		-(TABLE_WIDTH - TABLE_LEG_THICKNESS) / 2, 
		-(TABLE_LENGTH - TABLE_LEG_THICKNESS) / 2);

	// draw table sides
	drawSide(shader, mvs, proj,
		(TABLE_WIDTH - TABLE_SIDE_THICKNESS) / 2, 0.0f, 1.0f, 
		TABLE_WIDTH - 2 * TABLE_LEG_THICKNESS);
	drawSide(shader, mvs, proj,
		-(TABLE_WIDTH - TABLE_SIDE_THICKNESS) / 2, 0.0f, 1.0f, 
		TABLE_WIDTH - 2 * TABLE_LEG_THICKNESS);
	drawSide(shader, mvs, proj,
		0.0f, (TABLE_WIDTH - TABLE_SIDE_THICKNESS) / 2,
		TABLE_WIDTH - 2 * TABLE_LEG_THICKNESS, 1.0f);
	drawSide(shader, mvs, proj,
		0.0f, -(TABLE_WIDTH - TABLE_SIDE_THICKNESS) / 2,
		TABLE_WIDTH - 2 * TABLE_LEG_THICKNESS, 1.0f);



	mvs.pop();
	return true;
}

bool TableModel::drawLeg(Shader &shader, MatrixStack &mvs, mat4 proj, float xOffset, float zOffset) {
	mvs.push();
	mvs.active = translate(mvs.active, vec3(xOffset, -(TABLE_HEIGHT) / 2, zOffset));

	mvs.active = scale(mvs.active, vec3(
		TABLE_LEG_THICKNESS,				// x
		TABLE_HEIGHT - TABLE_TOP_THICKNESS, // y 
		TABLE_LEG_THICKNESS));				// z

	bool success = cube.draw(shader, mvs.active, proj);
	if (!success) return false;

	mvs.pop();
	return true;
}


bool TableModel::drawSide(Shader &shader, MatrixStack &mvs, mat4 proj, float xOffset, float zOffset, 
						  float xScale, float zScale) {

	mvs.push();
	mvs.active = translate(mvs.active, vec3(
		xOffset, 
		-(TABLE_LEG_THICKNESS + TABLE_TOP_THICKNESS) / 2, 
		zOffset));
	mvs.active = scale(mvs.active, vec3(xScale, TABLE_LEG_THICKNESS, zScale));

	bool success = cube.draw(shader, mvs.active, proj);
	if (!success) return false;

	mvs.pop();
	return true;
}
