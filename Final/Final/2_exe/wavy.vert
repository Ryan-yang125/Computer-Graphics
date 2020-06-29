#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 vertexNormal;

out vec3 normal;
out vec3 position;

uniform mat4 mvp;
uniform float time;

// This shader simply sends along the normal to the fragment shader.
// The fragment shader gets the interpolated normal and then does
// the ADS lighting calculation on it to achieve Phong shading.
void main() {
    position = vertexPosition;
    position.y += sin(position.x + time * 2);
    normal = normalize(vertexNormal);
    normal.xy = normalize(normal.xy + vec2(-1 * cos(position.x + time * 2)));

    gl_Position = mvp * vec4(position, 1.0);

}