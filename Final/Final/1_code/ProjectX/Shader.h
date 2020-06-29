/*	Professor Perry Kivolowitz - University of Wisconsin - Madison 
	Computer Sciences Department

	A sample hello world like program demonstrating modern
	OpenGL techniques. 

	Created:	2/25/13
	Updates:
*/

#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils.h"

using namespace std;
using namespace glm;

/*
 * Holds the info and setup for a shader program. This class is augmented from
 * the in-class shader demo.
 */
class Shader {
public:
	Shader();
	virtual ~Shader();
	void takeDown();
	void use();
	virtual bool init(char * vertex_shader_file, char * fragment_shader_file);
	virtual void preLinkSetup() {}
	virtual void customSetup();
	void commonSetup(const float time, const vec2 &size, const mat4 &mvp);
	std::stringstream getShaderLog(GLuint shader_id);

	GLuint getUniformLocation(const char *name);
	GLuint getTextureLocation(const char *name);
	GLuint getSubroutineLocation(GLenum shaderType, const char *name);
	void setTexture(const char *name, int slot);
	void setSubroutine(GLenum shaderType, const char *name);
	void setUniform(const char *name, const vec2 &v);
	void setUniform(const char *name, const ivec2 &v);
	void setUniform(const char *name, const vec3 &v);
	void setUniform(const char *name, const vec4 &v);
	void setUniform(const char *name, const mat4 &m);
	void setUniform(const char *name, float val);
	void setUniform(const char *name, int val);
	void setUniform(const char *name, bool val);

	GLuint vertex_shader_id;
	GLuint fragment_shader_id;
	GLuint program_id;

protected:
	map<string, GLuint> uniforms;

	bool loadShader(const char * file_name, GLuint shader_id);

private:
	typedef Shader super;
};
