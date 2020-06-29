// glutEx1.cpp : 定义控制台应用程序的入口点。
//


#include <stdlib.h>
#include "glut.h"

float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f
//环境光位置
GLfloat light_x = 0.0;
GLfloat light_y = 0.0;
GLfloat light_z = 0.0;
//聚光灯朝向和角度
GLfloat spotangle = 3.1415;
GLfloat lightDir_x = 0.0;
GLfloat lightDir_y = -1.0;
GLfloat lightDir_z = 0.0;

bool bPersp = false;
bool bAnim = false;
bool bWire = false;
bool bcolor = false;

int wHeight = 0;
int wWidth = 0;

void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}
void Draw_Table() {
	/* JADE*/
	/*
		*GLfloat amb[] = { 0.135f,0.2225f,0.1575f,1.0f };
		GLfloat diff[] = { 0.54f,0.89f,0.63f,1.0f };
		GLfloat spec[] = { 0.316228f,0.316228f,0.316228f,1.0f };
		GLfloat shine = 12.8f;
		*/
	GLfloat color[] = { 1, 0, 0 ,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();
}
void Draw_Leg1() {
	/* EMERALD*/
	/*
		*GLfloat amb[] = { 0.0215f,0.1745f,0.0215f,1.0f };
		GLfloat diff[] = { 0.07568f,0.61424f,0.07568f,1.0f };
		GLfloat spec[] = { 0.633f,0.727811f,0.633f,1.0f };
		GLfloat shine = 76.8f;
		*/

	GLfloat color[] = { 0, 1, 0 ,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();
}
void Draw_Leg2() {
	/* OBSIDIAN*/
	/*
		*GLfloat amb[] = { 0.05375f,0.05f,0.06625f,1.0f };
		GLfloat diff[] = { 0.18275f,0.17f,0.22525f,1.0f };
		GLfloat spec[] = { 0.332741f,0.328634f,0.346435f,1.0f };
		GLfloat shine = 38.4f;
		*/
	
	GLfloat color[] = { 1, 1, 0 ,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();
}
void Draw_Leg3() {
	/* PERL*/
	/*
		*GLfloat amb[] = { 0.25f,0.20725f,0.20725f,1.0f };
		GLfloat diff[] = { 1.0f,0.829f,0.829f,1.0f };
		GLfloat spec[] = { 0.296648f,0.296648f,0.296648f,1.0f };
		GLfloat shine = 11.264f;
		*/
	
	GLfloat color[] = { 0, 1, 1 ,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
}
void Draw_Leg4() {
	/* TURQUOISE*/
	/*
		*GLfloat amb[] = { 0.1f,0.18725f,0.1745f,1.0f };
		GLfloat diff[] = { 0.396f,0.74151f,0.69102f,1.0f };
		GLfloat spec[] = { 0.297254f,0.30829f,0.306678f,1.0f };
		GLfloat shine = 12.8f;
		*/

	GLfloat color[] = { 0, 0, 1 ,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
}
void Draw_Teapot() {

	/* GOLD*/
	GLfloat amb[] = { 0.24725f,0.1995f,0.0745f,1.0f };
	GLfloat diff[] = { 0.85f, 0.65f, 0.2f, 1.0f };
	GLfloat spec[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat shine = 50.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

	glPushMatrix();
	glTranslatef(0, 0, 4 + 1);
	glRotatef(90, 1, 0, 0);
	glutSolidTeapot(1);
	glPopMatrix();
}
void Draw_Triangle() // This function draws a triangle with RGB colors
{
	Draw_Teapot();
	Draw_Table();
	Draw_Leg1();
	Draw_Leg2();
	Draw_Leg3();
	Draw_Leg4();
}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	if (bPersp) {
		gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
		//glFrustum(-3, 3, -3, 3, 3,100);
	}
	else {
		glOrtho(-3, 3, -3, 3, -100, 100);
	}

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; break; }

	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }
	case 'u': {bcolor = !bcolor; break; }
	case 'a': {
		eye[0] -= 0.2f;
		center[0] -= 0.2f;
		break;
	}
	case 'd': {
		eye[0] += 0.2f;
		center[0] += 0.2f;
		break;
	}
	case 'w': {
		eye[1] -= 0.2f;
		center[1] -= 0.2f;
		break;
	}
	case 's': {
		eye[1] += 0.2f;
		center[1] += 0.2f;
		break;
	}
	case 'z': {
		eye[2] -= 0.2f;
		center[2] -= 0.2f;
		break;
	}
	case 'c': {
		eye[2] += 0.2f;
		center[2] += 0.2f;
		break;
	}

	case 'j': {//左
		light_x += 0.2f;
		break;
	}
	case 'l': {//右
		light_x -= 0.2f;
		break;
	}
	case 'i': {//上
		light_y += 0.2f;
		break;
	}
	case 'k': {//下
		light_y -= 0.2f;
		break;
	}
	case 'n': {//前
		light_z += 0.2f;
		break;
	}
	case 'm': {//后
		light_z -= 0.2f;
		break;
	}
	case '4': {
		lightDir_x += 0.2f;
		break;
	}
	case '6': {
		lightDir_x -= 0.2f;
		break;
	}
	case '8': {
		lightDir_y += 0.2f;
		break;
	}
	case '2': {
		lightDir_y -= 0.2f;
		break;
	}
	case '1': {
		lightDir_z += 0.2f;
		break;
	}
	case '3': {
		lightDir_z -= 0.2f;
		break;
	}
	case '+': {
		spotangle += 0.2f;
		break;
	}
	case '-': {
		spotangle -= 0.2f;
		if (spotangle <= 1.0f)	spotangle = 1.0f;
		break;
	}
	}

	updateView(wHeight, wWidth);
}


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat green[] = { 0.0,1.0,0.0,1.0 };//环境光颜色
	GLfloat light_pos[] = {5 + light_x, 5 + light_y, 5 + light_z , 1};//环境光位置
	//GLfloat light_pos[] = { light_x, light_y, light_z , 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	//glLightfv(GL_LIGHT0, GL_SMOOTH, white);
	if (!bcolor)
		glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	else
		glLightfv(GL_LIGHT0, GL_AMBIENT, green);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glEnable(GL_LIGHT0);

	GLfloat position[] = {0, 5.0, 0, 1.0 };
	GLfloat lightDir[] = { lightDir_x, lightDir_y, lightDir_z,1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, white);             //设置环境光成分
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);                    //设置镜面光成分
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);                     //设置漫射光成分

	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotangle);             //裁减角度
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir);          //光源方向
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);                    //聚集度
	glEnable(GL_LIGHT1);

	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Triangle();						// Draw triangle

	if (bAnim) fRotate += 0.5f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


