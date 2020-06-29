#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <GL/glew.h>
#include <gl/freeglut.h>
#include <SFML/Graphics.hpp>
#include <map>
#include "Utils.h"

using namespace std;

class TextureManager {

public:
	TextureManager(bool global);
	~TextureManager(void);
	GLuint loadTexture(const char *filename, const char *texName);
	void useTexture(const char *id);
	void unbindTexture();

	static TextureManager * get() { return global; }

private:
	map<const char*, GLuint> textures;
	static TextureManager *global;
};

#endif