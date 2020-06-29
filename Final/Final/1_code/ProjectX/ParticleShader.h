#pragma once
#include "shader.h"
class ParticleShader : public Shader {
public:
	ParticleShader(void);
	virtual void preLinkSetup();
};

