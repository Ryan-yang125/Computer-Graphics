#include "Vase.h"

VaseModel::VaseModel(vec3 ambient, vec3 diffuse, vec3 specular, float height, float radius, float curveMag, float curveFreq, 
					 float curveOffset, int slices, int stacks) :
					height(height), rad(radius), cMag(curveMag), 
					cFreq(curveFreq), cOffset(curveOffset), slices(slices), stacks(stacks),
					mesh(ambient, diffuse, specular, 50.0f),
					base(ambient, diffuse, specular, 50.0f)
{}


bool VaseModel::initMesh() {
	vector<VertexData> data;

	for (float y = 0; y < height + height / stacks; y += height / stacks) {
		for (float theta = 0; theta <= 2 * PI; theta +=  2 * PI / slices) {
			data.push_back(VertexData(vec3(
				(rad + cMag * sin((y + cOffset) * cFreq)) * sin(theta), 
				y, 
				(rad + cMag * sin((y + cOffset) * cFreq)) * cos(theta)), vec3(0,0,0), vec3(0,0,0)));
			//glVertex3f(
			//	(rad + cMag * sin((y + cOffset + height / stacks) * cFreq)) * sin(theta), 
			//	y + height / stacks, 
			//	(rad + cMag * sin((y + cOffset + height / stacks) * cFreq)) * cos(theta));
		}
		// two more vertices at beginning for continuity
		data.push_back(VertexData(vec3(
			(rad + cMag * sin((y + cOffset) * cFreq)) * sin(0.0f), 
			y, 
			(rad + cMag * sin((y + cOffset) * cFreq)) * cos(0.0f)), vec3(0,0,0), vec3(0,0,0)));
		//glVertex3f(
		//	(rad + cMag * sin((y + cOffset + height / stacks) * cFreq)) * sin(0.0f), 
		//	y + height / stacks, 
		//	(rad + cMag * sin((y + cOffset + height / stacks) * cFreq)) * cos(0.0f));
	}

	if (!base.init(EPSILON, rad - 0.002f, 32)) return false;

	return mesh.init(data, stacks + 1, slices + 1, true);
}


bool VaseModel::draw(Shader &shader, MatrixStack &mvs, mat4 proj) {
	mvs.push();
	// move it up a tiny bit so that it doesn't get mixed up with rendering
	// whatever is under it
	mvs.active = translate(mvs.active, vec3(0.0f, 0.01, 0.0f));
	bool success = base.draw(shader, mvs.active, proj);
	if (!success) return false;
	mvs.pop();

	mvs.push();
	success = mesh.draw(shader, mvs.active, proj);
	if (!success) return false;
	mvs.pop();	

	return true;
}
