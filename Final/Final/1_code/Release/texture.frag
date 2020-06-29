#version 400

in vec2 texCoord;
in vec3 normal;
in vec3 position;

uniform sampler2D spriteTexture;
uniform vec4 lightPosition;
uniform vec3 La; // light ambient intensity
uniform vec3 Ld; // light diffuse intensity
uniform vec3 Ls; // light specular intensity
uniform float shine = 10.0;

uniform mat4 mvMat;
uniform mat4 normalMat;
uniform int view = 0;

layout (location = 0) out vec4 fragColor;

void main() {
    vec3 color = vec3(texture(spriteTexture, texCoord));

    vec3 norm = normal;
    if (!gl_FrontFacing) {
        norm = -norm;
    }
    // convert normal and position to eye coordinates
    vec3 eyeNorm = vec3(normalize(mat3(normalMat) * norm));
    //vec3 eyeNorm = vec3(vec4(normal, 1.0));
    vec4 eyePos = mvMat * vec4(position, 1.0);

    // get the vector from the surface to the light
    vec3 vxToLight = normalize(vec3(lightPosition - eyePos));
    vec3 vxToEye = normalize(-eyePos.xyz);
    vec3 lightReflect = reflect(-vxToLight, eyeNorm);

    // add ambient light
    vec3 ambient = La * 0.3 * color;

    // apply the diffuse equation
    float normDotLight = max(dot(vxToLight, eyeNorm), 0.0);
    vec3 diffuse = Ld * 0.6 * color * normDotLight;

    vec3 specular = vec3(0.0);
    // if the light is shining on the surface, get the specular component
    if (normDotLight > 0.0) {
        specular = Ls * 0.3 * color * pow(max(dot(lightReflect, vxToEye), 0.0), shine);
    }
    
    vec3 lightIntensity;
    switch (view) {
    case 0:
        lightIntensity = ambient + diffuse + specular;
        break;
    case 1:
        lightIntensity = ambient + diffuse;
        break;
    case 2:
        lightIntensity = ambient;
        break;
    case 3:
        lightIntensity = diffuse;
        break;
    case 4:
        lightIntensity = specular;
        break;
    case 5:
        lightIntensity = eyeNorm;
        break;
    case 6:
        lightIntensity = vec3(dot(lightReflect, vxToEye));
        break;
    }

    fragColor = vec4(lightIntensity, 1.0);
}
