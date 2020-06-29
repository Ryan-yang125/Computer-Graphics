#include "TextureManager.h"

TextureManager *TextureManager::global = nullptr;

TextureManager::TextureManager(bool global) {
	if (global)
		TextureManager::global = this;
}


TextureManager::~TextureManager(void) {
}

GLuint TextureManager::loadTexture(const char *filename, const char* texName) {
	if (Utils::GLReturnedError("TextureManager::loadTexture - on entry")) return -1;

	sf::Image image;
	if (!image.loadFromFile(filename))
		return -1;


	// set up GL texture
	glActiveTexture(GL_TEXTURE0);
	GLuint tid;
	// generate and bind a texure
	glGenTextures(1, &tid);
	glBindTexture(GL_TEXTURE_2D, tid);

	// load the data into the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, 
		image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*) image.getPixelsPtr());

	// set up texture scaling parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// set up texture repeat parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);


	textures[texName] = tid;

	glBindTexture(GL_TEXTURE_2D, 0);

	if (Utils::GLReturnedError("TextureManager::loadTexture - on exit")) return -1;

	return tid;
}

void TextureManager::useTexture(const char *id) {
	// set the active texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[id]);
}

void TextureManager::unbindTexture() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
