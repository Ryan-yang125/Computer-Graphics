#include "ParticleShader.h"


ParticleShader::ParticleShader() : Shader() {}

void ParticleShader::preLinkSetup() {
	// set up transform feedback varyings
	const char *outputNames[] = {"position", "velocity", "startTime"};
	glTransformFeedbackVaryings(program_id, 3, outputNames, GL_SEPARATE_ATTRIBS);

}
