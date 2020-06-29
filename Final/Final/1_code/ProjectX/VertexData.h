#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include <glm/glm.hpp>

using namespace glm;

/*
 * Holds the data for one vertex
 */
class VertexData {
public:

	VertexData(vec3 &p, vec3 &c, vec3 &n, vec2&t = vec2(0,0));
	
	vec3 position;
	vec3 color;
	vec3 normal;
	vec3 flatNormal;
	vec2 texture;

};


#endif