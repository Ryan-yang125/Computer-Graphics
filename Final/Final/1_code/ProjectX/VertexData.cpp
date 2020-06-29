#include "VertexData.h"

VertexData::VertexData(vec3 &p, vec3 &c, vec3 &n, vec2 &t) :
	position(p), color(c), normal(n), flatNormal(n), texture(t) {}