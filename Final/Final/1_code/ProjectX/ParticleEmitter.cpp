#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(int numParticles, 
								 float particleSize, 
								 float lifetime, 
								 const char *texture, 
								 vec3 acceleration) : 

	drawBuf(1), 
	particleLifetime(lifetime), 
	particleSize(particleSize), 
	texture(texture), 
	acceleration(acceleration) {}


// initialize OpenGL buffers for this particle fountain
bool ParticleEmitter::initGL() {
	if (Utils::GLReturnedError("ParticleEmitter::initGL - on entry")) return false;

	// generate handles for whole bundle
	glGenVertexArrays(2, particleArray);

	// generate two buffers for each attribute (to be used with transform feedback)
	glGenBuffers(2, posBuf);
	glGenBuffers(2, velBuf);
	glGenBuffers(2, startBuf);
	glGenBuffers(1, &initVelBuf);

	// set up bundles 0 and 1
	for (int i = 0; i < 2; i++) {
		// bind bundle
		glBindVertexArray(particleArray[i]);

		// set up position buffer
		glBindBuffer(GL_ARRAY_BUFFER, posBuf[i]);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(vec3), &positions[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

		// set up velocity buffer
		glBindBuffer(GL_ARRAY_BUFFER, velBuf[i]);
		glBufferData(GL_ARRAY_BUFFER, velocities.size() * sizeof(vec3), &velocities[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
		// set up initial velocity buffer

		// set up start time buffer
		glBindBuffer(GL_ARRAY_BUFFER, startBuf[i]);
		glBufferData(GL_ARRAY_BUFFER, startTimes.size() * sizeof(GLfloat), &startTimes[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), 0);

		// set up initial velocity buffer
		glBindBuffer(GL_ARRAY_BUFFER, initVelBuf);
		glBufferData(GL_ARRAY_BUFFER, velocities.size() * sizeof(vec3), &velocities[0], GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
	}

	// unbind handles
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// set up transform feedback objects
	glGenTransformFeedbacks(2, feedback);

	// transform feedback 0 and 1
	for (int i = 0; i < 2; i++) {
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, posBuf[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, velBuf[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 2, startBuf[i]);
	}

	if (Utils::GLReturnedError("ParticleEmitter::initGL - on exit")) return false;

	return true;
}


void ParticleEmitter::update(float elapsedTime) {

}

bool ParticleEmitter::draw(ParticleShader &shader, MatrixStack &mvs, mat4 proj, float time) {
	shader.use();
	// set up fountain drawing
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(particleSize);


	// set up subroutine call
	shader.setSubroutine(GL_VERTEX_SHADER, "update");

	// set uniforms
	mat4 mvp = proj * mvs.active;
	shader.setUniform("time", time);
	shader.setUniform("particleLifetime", particleLifetime);
	shader.setUniform("gravity", acceleration);
	shader.setUniform("mvp", mvp);
	shader.setTexture("spriteTexture", 0);
	TextureManager::get()->useTexture(texture);

	// Update pass 
	{
		// disable rastering for the update pass
		glEnable(GL_RASTERIZER_DISCARD);

		// bind the feedback object for the buffers to be drawn next
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[drawBuf]);

		// draw points from input buffer with transform feedback
		glBeginTransformFeedback(GL_POINTS);
		glBindVertexArray(particleArray[1 - drawBuf]);
		glDrawArrays(GL_POINTS, 0, positions.size());
		glEndTransformFeedback();
	}
	
	////////// Render pass //////////
	{

		// enable rendering
		glDisable(GL_RASTERIZER_DISCARD);
		glEnable(GL_POINT_SPRITE);

		shader.setSubroutine(GL_VERTEX_SHADER, "render");

		// unbind the feedback object
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

		// draw the fountain
		glBindVertexArray(particleArray[drawBuf]);
		glDrawArrays(GL_POINTS, 0, positions.size());

		// swap buffers
		drawBuf = 1 - drawBuf;
		glDisable(GL_POINT_SPRITE);
	}
	// take down fountain setup
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glBindVertexArray(0);

	if (Utils::GLReturnedError("ParticleFountain::draw - on exit")) return false;
	return true;
}
