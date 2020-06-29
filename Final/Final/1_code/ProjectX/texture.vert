#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 vertexNormal;
layout (location = 4) in vec2 vertexTexture;

out vec2 texCoord;
out vec3 normal;
out vec3 position;

uniform mat4 mvMat;
uniform mat4 projMat;
uniform mat4 normalMat;
uniform mat4 mvp;

void main() {

    texCoord = vertexTexture;
    normal = normalize(vertexNormal);
    position = vertexPosition;
    // pass along vertex position
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}

//void main() {
    // pass along vertex position
    //gl_Position = mvp * vec4(vertexPosition, 1.0);
//}
