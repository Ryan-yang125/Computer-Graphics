#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 vertexNormal;

out vec3 normal;
out vec3 position;

uniform mat4 mvp;

// This shader simply sends along the normal to the fragment shader.
// The fragment shader gets the interpolated normal and then does
// the ADS lighting calculation on it to achieve Phong shading.
void main() {
    normal = normalize(vertexNormal);
    position = vertexPosition;

    gl_Position = mvp * vec4(vertexPosition, 1.0);

}