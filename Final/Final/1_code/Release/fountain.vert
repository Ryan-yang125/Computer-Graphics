#version 400

// This shader is used to simulate a particle fountain. It was taken from
// the OpenGL 4.0 Shading Language Cookbook.

subroutine void renderPassType();
subroutine uniform renderPassType renderPass;

// Initial velocity and start time
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexVelocity;
layout (location = 2) in float vertexStartTime;
layout (location = 3) in vec3 vertexInitVel;

out vec3 position;
out vec3 velocity;
out float startTime;
out float transparency;

uniform float time;             // total time elapsed
uniform float elapsedTime;      // time elapsed since last frame
uniform vec3 gravity;           // world coords
uniform float particleLifetime; // max particle particleLifetime

uniform mat4 mvp;

subroutine(renderPassType)
void update() {

    position = vertexPosition;
    velocity = vertexVelocity;
    startTime = vertexStartTime;

    // particle doesn't exist until the start time
    if (time >= startTime) {
        float age = time - startTime;

        // if particle has lived its full life, recycle it
        if (age > particleLifetime) {
            //position = vec3(0.0);
            position.y = 0.0;
            velocity = vertexInitVel;
            startTime = vertexStartTime + 1.5;
        }
        // update the living particle
        else {
            position += elapsedTime * velocity;
            velocity += elapsedTime * gravity;
        }
    }
    gl_Position = mvp * vec4(position, 1.0);
}

subroutine(renderPassType)
void render() {
    float age = time - vertexStartTime;
    transparency = 1.0 - age / particleLifetime;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}

void main() {
    renderPass();
}