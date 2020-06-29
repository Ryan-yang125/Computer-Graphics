#include "Cylinder.h"

// Just initialize the lighting components of the mesh
Cylinder::Cylinder(vec3 matAmbient, vec3 matDiffuse, vec3 matSpecular, float shine) :
	mesh(Mesh(matAmbient, matDiffuse, matSpecular, shine)) {}


// initialize the grid for this skewed disk's mesh
bool Cylinder::init(float innerRad, float outerRad, int slices, float height) {

	vector<VertexData> data;

	// create inner circle
	for (float theta = 0.0f; theta < 2 * PI; theta += 2 * PI / slices) {
		data.push_back(VertexData(
			vec3(innerRad * std::cos(theta), height, innerRad * std::sin(theta)), 
			vec3(0,0,0), 
			vec3(0,1,0)));
	}
	// one more for continuity
	data.push_back(VertexData(
		vec3(innerRad * std::cos(0.0f), height, innerRad * std::sin(0.0f)), 
		vec3(0,0,0), 
		vec3(0,1,0)));

	// create outer circle
	for (float theta = 0.0f; theta < 2 * PI; theta += 2 * PI / slices) {
		data.push_back(VertexData(
			vec3(outerRad * std::cos(theta), 0.0f, outerRad * std::sin(theta)), 
			vec3(0,0,0), 
			vec3(0,1,0)));
	}
	// one more for continuity
	data.push_back(VertexData(
		vec3(outerRad * std::cos(0.0f), 0.0f, outerRad * std::sin(0.0f)), 
		vec3(0,0,0), 
		vec3(0,1,0)));



	// slices + 1 to take care of the extra vertex for continuity in each row
	return mesh.init(data, 2, slices + 1, true);
}

bool Cylinder::draw(Shader &shader, mat4 &mv, const mat4 &proj) {

	return mesh.draw(shader, mv, proj);
}

/*
 * A disk is simply a cylinder with height of 0.
 */
Disk::Disk(vec3 matAmbient, vec3 matDiffuse, vec3 matSpecular, float shine) :
	Cylinder(matAmbient, matDiffuse, matSpecular, shine) {}

bool Disk::init(float innerRad, float outerRad, int slices) {
	return Cylinder::init(innerRad, outerRad, slices, 0.0f);
}
