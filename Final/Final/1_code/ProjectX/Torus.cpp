#include "Torus.h"

// Just initialize the lighting components of the mesh
Torus::Torus(vec3 matAmbient, vec3 matDiffuse, vec3 matSpecular, float shine) :
	mesh(Mesh(matAmbient, matDiffuse, matSpecular, shine)) {}


bool Torus::init(float radius, float thickness, int bigSlices, int littleSlices) {

	vector<VertexData> data;

	// outer loop goes around the solid portion of the torus
	// wrapped backwards so that it is lit correctly
	// one extra vertex added for continuity
	// > 0.01 instead of 0.0 to handle the imprecisions of floating-point arithmetic causing anomalies
	for (float theta = 2.0f * PI + 2.0f * PI / littleSlices; theta > 0.01f; theta -= 2.0f * PI / littleSlices) {

		// inner loop goes around the big loop of the torus
		// one extra vertex added for continuity
		// > 0.01 instead of 0.0 to handle the imprecisions of floating-point arithmetic causing anomalies
		for (float phi = 0.01f; phi < 2.0f * PI + 2.0f * PI / bigSlices; phi += 2.0f * PI / bigSlices) {
			data.push_back(VertexData(vec3(
				(radius + std::cos(theta) * thickness) * std::cos(phi), 
				std::sin(theta) * thickness, 
				(radius + std::cos(theta) * thickness) * std::sin(phi)),
				vec3(0,0,0),
				vec3(0,0,0)));
		}
	}
	// one added to each due to the extra vertex
	return mesh.init(data, littleSlices + 1, bigSlices + 1, true, true);
}


bool Torus::draw(Shader &shader, mat4 &mv, const mat4 &proj) {

	return mesh.draw(shader, mv, proj);
}