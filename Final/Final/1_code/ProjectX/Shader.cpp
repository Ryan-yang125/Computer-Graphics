/*
 * Copied from online shader example
 */

#include "Shader.h"
#include <assert.h>

using namespace std;
using namespace glm;

#define BAD_GL_VALUE GLuint(-1)

Shader::Shader()
{
	uniforms["mvp"] = BAD_GL_VALUE;
	uniforms["proj"] = BAD_GL_VALUE;
	uniforms["mv"] = BAD_GL_VALUE;
	uniforms["size"] = BAD_GL_VALUE;
	this->vertex_shader_id = BAD_GL_VALUE;
	this->fragment_shader_id = BAD_GL_VALUE;
	this->program_id = BAD_GL_VALUE;
}

Shader::~Shader() {
	this->takeDown();
}



/*	This Shader() class implements or assumes a basic set of uniforms will be
	provided to all shaders derived from it. These are listed below. 
	Shader::CommonSetup() can be used by call derived classes to send the 
	common values to the shader. Values unique to the derived class can be
	loaded with the CustomShader() function.
*/
void Shader::commonSetup(const float time, const vec2 &size, const mat4 &mvp)
{
	setUniform("time", time);
	setUniform("size", size);
	setUniform("mvp", mvp);
}

void Shader::use()
{
	assert(this->program_id != BAD_GL_VALUE);
	glUseProgram(this->program_id);
}

/*	The shader initialization code is lifted liberally from the GLSL 4.0 Cookbook.
*/
bool Shader::init(char * vertex_shader_file, char * fragment_shader_file)
{
	GLint check_value;

	if (Utils::GLReturnedError("Shader::Initialize - on entrance"))
		return false;

	this->vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	this->loadShader(vertex_shader_file, this->vertex_shader_id);
	glCompileShader(this->vertex_shader_id);
	glGetShaderiv(this->vertex_shader_id, GL_COMPILE_STATUS, &check_value);
	if (check_value != GL_TRUE)
	{
		cerr << this->getShaderLog(vertex_shader_id).str();
		cerr << "GLSL compilation failed - vertex shader: " << vertex_shader_file << endl;
		return false;
	}

	if (Utils::GLReturnedError("Shader::Initialize - after processing vertex shader"))
		return false;

	this->fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	this->loadShader(fragment_shader_file, this->fragment_shader_id);
	glCompileShader(this->fragment_shader_id);
	glGetShaderiv(this->fragment_shader_id, GL_COMPILE_STATUS, &check_value);
	if (check_value != GL_TRUE)
	{
		cerr << this->getShaderLog(fragment_shader_id).str();
		cerr << "GLSL compilation failed - fragment shader: " << fragment_shader_file << endl;
		return false;
	}

	this->program_id = glCreateProgram();
	glAttachShader(this->program_id, this->vertex_shader_id);
	glAttachShader(this->program_id, this->fragment_shader_id);

	// used for transform feedback
	preLinkSetup();
	
	glLinkProgram(program_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	this->getUniformLocation("mvMat");
	this->getUniformLocation("projMat");
	this->getUniformLocation("normalMat");
	this->getUniformLocation("mvp");
	this->getUniformLocation("size");
	this->getUniformLocation("time");

	return !Utils::GLReturnedError("Shader::Initialize - on exit");
}

void Shader::customSetup() {
}


void Shader::takeDown()
{
	GLint temp;
	GLsizei size;

	if (this->program_id == (GLuint) -1)
		return;

	glGetProgramiv(this->program_id, GL_ATTACHED_SHADERS, &temp);
	if (temp > 0)
	{
		GLuint * shader_list = new GLuint[temp];
		glGetAttachedShaders(this->program_id, temp, &size, shader_list);
		for (GLsizei i = 0; i < size; i++)
		{
			glDetachShader(this->program_id, shader_list[i]);
			// The shaders were marked for deletion
			// immediately after they were created.
		}
		delete [] shader_list;
	}

	glDeleteProgram(this->program_id);
	this->program_id = (GLuint) -1;
}

/*
	This function is adapted from OpenGL 4.0 Shading Language Cookbook by David Wolff.
*/
bool Shader::loadShader(const char * file_name, GLuint shader_id)
{
	assert(file_name != NULL);
	if (Utils::GLReturnedError("Shader::LoadShader - on entrance"))
		return false;

	FILE * file_handle = NULL;
	fopen_s(&file_handle, file_name, "rb");
	if (file_handle == NULL)
	{
		cerr <<  "Cannot open shader: " << file_name << endl;
		return false;
	}
	fseek(file_handle, 0, SEEK_END);
	int length = ftell(file_handle);
	fseek(file_handle, 0, SEEK_SET);
	GLubyte * buffer = new GLubyte[length + 1];
	fread(buffer, sizeof(GLubyte), length, file_handle);
	fclose(file_handle);
	buffer[length] = 0;
	glShaderSource(shader_id, 1, (const char **) &buffer, NULL);
	delete [] buffer;

	return !Utils::GLReturnedError("Shader::LoadShader - on exit");
}

/*
	This function is adapted from OpenGL 4.0 Shading Language Cookbook by David Wolff.
*/
stringstream Shader::getShaderLog(GLuint shader_id)
{
	stringstream s;
	GLint log_length;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length <= 0)
		s << "No shader log information available." << endl;
	else
	{
		GLchar * buffer = new GLchar[log_length];
		glGetShaderInfoLog(shader_id, log_length, NULL, buffer);
		s << "Shader log:" << endl;
		s << buffer << endl;
		delete [] buffer;
	}
	return s;
}

/*
 * Get a uniform location for this named uniform. Also stores the handle
 * in a map, accessible by the uniform name. Handles using and un-using
 * the shader program internally.
 */
GLuint Shader::getUniformLocation(const char *name) {
	// check for GL errors
	Utils::GLReturnedError("Shader::getUniformLocation - on entry");

	glUseProgram(this->program_id);

	GLuint handle = glGetUniformLocation(program_id, (const GLchar*)name);

	this->uniforms[name] = handle;

	glUseProgram(0);

	// check for GL errors
	Utils::GLReturnedError("Shader::getUniformLocation - on exit");

	return handle;
}

/*
 * Get the uniform location for the specified texture
 */
GLuint Shader::getTextureLocation(const char *name) {

	Utils::GLReturnedError("Shader::getTextureLocation - on entry");

	glUseProgram(this->program_id);

	GLuint handle = glGetUniformLocation(program_id, name);

	this->uniforms[name] = handle;

	glUseProgram(0);

	Utils::GLReturnedError("Shader::getTextureLocation - on exit");

	return handle;
}

/*
 * Get a subroutine location for this named uniform. Also stores the handle
 * in a map, accessible by the uniform name. Handles using and un-using
 * the shader program internally
 */
GLuint Shader::getSubroutineLocation(GLenum shaderType, const char *name) {
	Utils::GLReturnedError("Shader::getSubroutineLocation - on entry");

	glUseProgram(this->program_id);

	GLuint handle = glGetSubroutineIndex(program_id, shaderType, name);

	this->uniforms[name] = handle;

	glUseProgram(0);

	Utils::GLReturnedError("Shader::getSubroutineLocation - on exit");

	return handle;
}

void Shader::setTexture(const char *name, int slot) {
	// check for GL errors
	Utils::GLReturnedError("Shader::setSubroutine - on entry");

	glUniform1i(uniforms[name], slot);

	// check for GL errors
	Utils::GLReturnedError("Shader::setSubroutine - on exit");
	
}

void Shader::setSubroutine(GLenum shaderType, const char *name) {
	// check for GL errors
	Utils::GLReturnedError("Shader::setSubroutine - on entry");

	glUniformSubroutinesuiv(shaderType, 1, &uniforms[name]);

	// check for GL errors
	Utils::GLReturnedError("Shader::setSubroutine - on exit");
}


/*
 * The following methods set the named uniform to whatever is passed in as
 * the second parameter. The program must be in use to use these methods
 */
void Shader::setUniform(const char *name, const vec2 &v) {
	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(vec2) - on entry");
	
	glUniform2fv(uniforms[name], 1, value_ptr(v));

	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(vec2) - on exit");
}
void Shader::setUniform(const char *name, const ivec2 &v) {
	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(ivec2) - on entry");
	
	glUniform2iv(uniforms[name], 1, value_ptr(v));

	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(ivec2) - on exit");
}
void Shader::setUniform(const char *name, const vec3 &v) {
	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(vec3) - on entry");
	
	glUniform3fv(uniforms[name], 1, value_ptr(v));

	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(vec3) - on exit");
}
void Shader::setUniform(const char *name, const vec4 &v) {
	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(vec4) - on entry");
	
	glUniform4fv(uniforms[name], 1, value_ptr(v));

	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(vec4) - on exit");
}

void Shader::setUniform(const char *name, const mat4 &m) {
	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(mat4) - on entry");
	
	glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, value_ptr(m)); 

	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(mat4) - on exit");
}

void Shader::setUniform(const char *name, float val) {
	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(float) - on entry");
	
	glUniform1f(uniforms[name], val);

	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(float) - on exit");
}

void Shader::setUniform(const char *name, int val) {
	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(int) - on entry");
	
	glUniform1i(uniforms[name], val);

	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(int) - on exit");
}

void Shader::setUniform(const char *name, bool val) {
	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(bool) - on entry");
	
	glUniform1i(uniforms[name], val);

	// check for GL errors
	Utils::GLReturnedError("Shader::setUniform(bool) - on exit");
}