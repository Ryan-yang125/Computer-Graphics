#version 400

in float transparency;

uniform sampler2D spriteTexture;

layout (location = 0) out vec4 fragColor;

void main() {
    vec4 color = texture(spriteTexture, gl_PointCoord);

    fragColor = vec4(color);
    fragColor.a *= transparency;
}