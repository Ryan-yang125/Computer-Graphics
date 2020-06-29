/*
 * YANG Rui
 * CG Project Final
 */
#include <iostream>
#include <assert.h>
#include <vector>



#include <gl/glew.h>

#include <gl/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene.h"
#include "Shader.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Utils.h"
#include "TextureManager.h"
#define NUM_VIEWS 7

using namespace std;
using namespace glm;

struct Window {
	int window_handle;//if we have over one window
	ivec2 size;//size of the window
	float window_aspect;
	vector<string> instructions;
	float fov;//fovy
} window;

struct Options {
	int shader;//switch between shaders
	float rotX, rotY;
	bool wireframe;
	bool fountain_drawing;
	bool lightmove;
	bool lightset;
	bool bowlrotate;
	int view;
	Shader* currentShader;
	float oldTime;
	float startTime;
	float picture_size;
	float firesize;
} options;

vector<char*> viewStrings;
Shader* textureShader;

struct Camera {
	vec3 position;
	vec3 up;
	vec3 right;
} camera;


Scene scene;
vector<Shader*> shaders;
MatrixStack mvs;
string filePath = "bookcase.obj";


void DisplayInstructions();


void DisplayFunc() {

	if (window.window_handle == -1)
		return;

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, options.wireframe ? GL_LINE : GL_FILL);
	glViewport(0, 0, window.size.x, window.size.y);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	mvs.push();
	// time since start of program
	float newTime = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f - options.startTime;
	// time since last frame
	float elapsedTime = newTime - options.oldTime;
	options.oldTime = newTime;
	//scene.setFanRotation(elapsedTime * 360.0);
	
	mat4 projection = perspective(window.fov, window.window_aspect, 0.1f, 1000.0f);

	// PERFORM CAMERA TRANSFORMS
	mvs.active = translate(mvs.active, vec3(0.0f, -1.0f, -3.0f));
	mvs.active = rotate(mvs.active, options.rotX, vec3(1.0f, 0.0f, 0.0f));
	mvs.active = rotate(mvs.active, options.rotY, vec3(0.0f, 1.0f, 0.0f));
	// END CAMERA TRANSFORMS

	// setup the current shader
	options.currentShader = shaders[options.shader];
	options.currentShader->use();
	options.currentShader->setUniform("view", options.view);
	textureShader->use();
	textureShader->setUniform("view", options.view);

	// update the scene with the amount of time since the last frame
	scene.update(elapsedTime);
	
	// draw the scene using the total elapsed time
	
	scene.draw(*options.currentShader, mvs, projection, window.size, newTime, 
				options.picture_size, options.fountain_drawing, options.firesize, 
				options.lightmove, options.lightset, options.bowlrotate);
	
	mvs.pop();

	glutSwapBuffers();
	glutPostRedisplay();
}


void ReshapeFunc(int w, int h) {
	if (window.window_handle != -1 &&  h > 0)
	{
		window.size = ivec2(w, h);
		window.window_aspect = float(w) / float(h);
	}
}

void KeyboardFunc(unsigned char c, int x, int y) {
	if (window.window_handle == -1)
		return;

	switch (c) {
	case 'j':
		scene.adjustStoolHeight(-0.2f);
		break;
	case 'k':
		scene.adjustStoolHeight(0.2f);
		break;
	case 'i':
		window.fov--;
		break;
	case 'o':
		window.fov++;
		break;
	case 'p':
		Mesh::drawPoints = !Mesh::drawPoints;
		break;
	case 's':
		options.shader = (options.shader + 1) % shaders.size();
		break;
	case 'w':
		options.wireframe = !options.wireframe;
		break;
	case 'n':
		options.picture_size += 0.05f;
		break;
	case 'm':
		options.picture_size -= 0.05f;
		break;
	case 'b':
		options.fountain_drawing = !options.fountain_drawing;
		break;
	case 'c':
		options.firesize -= 0.05f;
		break;
	case 'v':
		options.firesize += 0.05f;
		break;
	case 'z':
		options.lightmove = !options.lightmove;
		break;
	case 'x':
		options.lightset = !options.lightset;
		break;
	case 'a':
		options.bowlrotate = !options.bowlrotate;
		break;
	case 27:
		glutLeaveMainLoop();
		return;
	}
}

void SpecialFunc(int c, int x, int y) {
	if (window.window_handle == -1)
		return;

	switch (c) {
	case GLUT_KEY_RIGHT:
		//scene.moveLight(1.0f, 0.0f);
		options.rotY--;
		break;
	case GLUT_KEY_LEFT:
		//scene.moveLight(-1.0f, 0.0f);
		options.rotY++;
		break;
	case GLUT_KEY_UP:
		//scene.moveLight(0.0f, -1.0f);
		options.rotX = std::min(89.0f, options.rotX + 1.0f);
		break;
	case GLUT_KEY_DOWN:
		//scene.moveLight(0.0f, 1.0f);
		options.rotX = std::max(-17.0f, options.rotX - 1.0f);
		break;
	// F1 cycles views
	case GLUT_KEY_F1:
		options.view = (options.view + 1) % NUM_VIEWS;
		cout << viewStrings[options.view] << endl;
		break;
	// F2 resets to the finished view
	case GLUT_KEY_F2:
		options.view = 0;
		break;
	}

}

void DisplayInstructions() {
	if (window.window_handle == -1)
		return;

	vector<string> * s = &window.instructions;
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window.size.x, 0, window.size.y, 1, 10);
	glViewport(0, 0, window.size.x, window.size.y);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(10, (s->size()), -5.5);
	glScaled(0.1, 0.1, 1.0);
	for (auto i = s->begin(); i < s->end(); ++i)
	{
		glPushMatrix();
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *) (*i).c_str());
		glPopMatrix();
		glTranslated(0, -150, 0);
	}
}
/*
Init diffrent shaders:flat, Phong, gouraud, wavy
*/
void initShaders() {
	Shader *flatShader =  new Shader();
	flatShader->init("flat.vert", "flat.frag");
	flatShader->getUniformLocation("lightPosition");
	flatShader->getUniformLocation("Kd"); 
	flatShader->getUniformLocation("Ld"); 
	flatShader->getUniformLocation("Ka");
	flatShader->getUniformLocation("La");
	flatShader->getUniformLocation("Ks");
	flatShader->getUniformLocation("Ls");
	flatShader->getUniformLocation("shine");
	flatShader->getUniformLocation("view");
	flatShader->getUniformLocation("time");
	shaders.push_back(flatShader);

	Shader *gouraudShader = new Shader();
	gouraudShader->init("gouraud.vert", "gouraud.frag");
	gouraudShader->getUniformLocation("lightPosition");
	gouraudShader->getUniformLocation("Kd");
	gouraudShader->getUniformLocation("Ld");
	gouraudShader->getUniformLocation("Ka");
	gouraudShader->getUniformLocation("La");
	gouraudShader->getUniformLocation("Ks");
	gouraudShader->getUniformLocation("Ls");
	gouraudShader->getUniformLocation("shine");
	gouraudShader->getUniformLocation("view");
	shaders.push_back(gouraudShader);

	Shader *phongShader =  new Shader();
	phongShader->init("phong.vert", "phong.frag");
	phongShader->getUniformLocation("lightPosition");
	phongShader->getUniformLocation("Kd");
	phongShader->getUniformLocation("Ld");
	phongShader->getUniformLocation("Ka");
	phongShader->getUniformLocation("La");
	phongShader->getUniformLocation("Ks");
	phongShader->getUniformLocation("Ls");
	phongShader->getUniformLocation("shine");
	phongShader->getUniformLocation("view");
	shaders.push_back(phongShader);

	Shader *wavyShader = new Shader();
	wavyShader->init("wavy.vert", "phong.frag");
	wavyShader->getUniformLocation("lightPosition");
	wavyShader->getUniformLocation("Kd");
	wavyShader->getUniformLocation("Ld");
	wavyShader->getUniformLocation("Ka");
	wavyShader->getUniformLocation("La");
	wavyShader->getUniformLocation("Ks");
	wavyShader->getUniformLocation("Ls");
	wavyShader->getUniformLocation("shine");
	wavyShader->getUniformLocation("view");
	shaders.push_back(wavyShader);

}
void initTextures() {
	TextureManager *textureManager = new TextureManager(true);	
	TextureManager::get()->loadTexture("brick.png", "brick");
	TextureManager::get()->loadTexture("water_droplet.png", "water_droplet");
	TextureManager::get()->loadTexture("fire.png", "fire");
	TextureManager::get()->loadTexture("floor.jpg", "floorpaper");
	TextureManager::get()->loadTexture("wallnear.jpg", "wallnear");
	TextureManager::get()->loadTexture("wallnear.jpg", "wallfar");
	TextureManager::get()->loadTexture("wallleft.jpg", "wallright");
	TextureManager::get()->loadTexture("wallleft.jpg", "wallleft");
	TextureManager::get()->loadTexture("ceiling.png", "ceilingpaper");
	//TextureManager::get()->loadTexture("starrynight.png", "current_painting");
	//TextureManager::get()->loadTexture("monet.bmp", "current_painting");

	textureShader = new Shader();
	textureShader->init("texture.vert", "texture.frag");
	textureShader->getTextureLocation("spriteTexture");
	textureShader->getUniformLocation("lightPosition");
	textureShader->getUniformLocation("Ld");
	textureShader->getUniformLocation("La");
	textureShader->getUniformLocation("Ls");
	textureShader->getUniformLocation("view");
	scene.setTextureShader(textureShader);
}


void initScene() {
	scene.init();//init mesh

	ParticleShader *fountainShader = new ParticleShader();
	fountainShader->init("fountain.vert", "fountain.frag");
	fountainShader->getUniformLocation("particleLifetime");
	fountainShader->getUniformLocation("elapsedTime");
	fountainShader->getUniformLocation("gravity");
	fountainShader->getSubroutineLocation(GL_VERTEX_SHADER, "update");
	fountainShader->getSubroutineLocation(GL_VERTEX_SHADER, "render");
	fountainShader->getTextureLocation("spriteTexture");
	scene.setFountainShader(fountainShader);
}

void setViewStrings() {
	viewStrings.push_back("View 0 - Finished View (Ambient + Diffuse + Specular)");
	viewStrings.push_back("View 1 - Ambient + Diffuse");
	viewStrings.push_back("View 2 - Ambient");
	viewStrings.push_back("View 3 - Diffuse");
	viewStrings.push_back("View 4 - Specular");
	viewStrings.push_back("View 5 - Normal relative to eye");
	viewStrings.push_back("View 6 - Specular Dot Product");
}

void setWindowInstructions() {
	window.instructions.push_back("YANG Rui - CG Project Final");
}


int main(int argc, char * argv[]) {
	setWindowInstructions();

	options.shader = 2;
	options.rotX = 0.0f;
	options.rotY = -45.0f;
	options.wireframe = false;
	options.view = 0;
	options.oldTime = 0.0f;
	options.picture_size = 1.0f;
	options.fountain_drawing = false;
	options.lightmove = false;
	options.lightset = false;
	options.bowlrotate = false;
	options.firesize = 1.0f;
	window.fov = 50.0f;
	
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	window.window_handle = glutCreateWindow("My House");
	glutReshapeFunc(ReshapeFunc);
	glutDisplayFunc(DisplayFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);

	window.instructions.push_back("YANG Rui - CG Project Final");

	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW failed to initialize." << endl;
		return 0;
	}
	initShaders();
	initTextures();
	initScene();
	setViewStrings();

	options.startTime = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;
	glutMainLoop();
}
