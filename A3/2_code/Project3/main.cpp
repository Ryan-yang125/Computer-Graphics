// This assignment may cost you some efferts, so I give you some important HINTS, hope that may help you.
// Enjoy the coding and thinking, do pay more attention to the library functions used in OPENGL, such as how they are used? what are the parameters used? and why?

// 实验报告里面多写点感想，即对函数的理解，以及调用的顺序，步骤等。思考为什么是这样子调用的，为什么参数是这样子设置的？。。。等等你觉得值得研究的问题。
#include <stdlib.h>
#include "glut.h"


float fTranslate;
float fRotate = 0.0f;
float fScale = 1.0f;	// set inital scale value to 1.0f
float tRotate = 0.0f;

bool bPersp = true;
bool bAnim = false;
bool bWire = false;
bool tAnim = false;

int wHeight = 0;
int wWidth = 0;

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };
float tplace[] = { 0, 0, 0 };
GLfloat x, y;
GLfloat x_angle = 0, y_angle = 0;
void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void Draw_Scene()
{
	//glMatrixMode(GL_MODELVIEW);
	//draw teapoat
	glPushMatrix();
	glTranslatef(0, 0, 4 + 1);
	glTranslatef(tplace[0], tplace[1], tplace[2]);
	glRotatef(90, 1, 0, 0); //notice the rotation here, you may have a TRY removing this line to see what it looks like.
	glRotatef(tRotate, 0, 1, 0);//todo; hint: when operate the teapot, you may need to change some parameters
	glutSolidTeapot(1);
	glPopMatrix();

	//table
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();
	// four legs
	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

}
void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	if (bPersp) {
		gluPerspective(45, whRatio, 1, 100);
		//todo when 'p' operation, hint: use FUNCTION gluPerspective
		/*void APIENTRY gluPerspective (
			GLdouble fovy,
			GLdouble aspect,
			GLdouble zNear,
			GLdouble zFar);*/
	}
	else
		glOrtho(-3, 3, -3, 3, -100, 100);
	/*glOrtho (GLdouble left, GLdouble right, GLdouble bottom,
				GLdouble top, GLdouble zNear, GLdouble zFar);*/

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

	updateView(wHeight, wWidth);//update view 
}

void idle()
{
	if (bAnim) fRotate += 0.5f;
	if (tAnim) tRotate += 0.5f;
	glutPostRedisplay();//call the current draw
}

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
		//case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth); break; }

	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }

	case 'a': {
		eye[0] += 0.08f;
		center[0] += 0.08f;//todo, hint: eye[] and center[] are the keys to solve the problems
		break;
	}
	case 'd': {
		eye[0] -= 0.08f;
		center[0] -= 0.08f;//todo
		break;
	}
	case 'w': {
		eye[1] -= 0.08f;
		center[1] -= 0.08f;//todo
		break;
	}
	case 's': {
		eye[1] += 0.08f;
		center[1] += 0.08f;//todo
		break;
	}
	case 'z': {
		eye[2] -= 0.08f;
		//center[2] -= 0.08f;
		//todo
		break;
	}
	case 'c': {
		eye[2] += 0.08f;
		//todo
		break;
	}

			  //茶壶相关操作
	case 'l': {
		tplace[0] += 0.08f;
		if (tplace[0] >= 1.5f) tplace[0] = 1.5f;//todo, hint:use the ARRAY that you defined, and notice the teapot can NOT be moved out the range of the table.
		break;
	}
	case 'j': {//todo
		tplace[0] -= 0.08f;
		if (tplace[0] <= -1.5f) tplace[0] = -1.5f;
		break;
	}
	case 'i': {
		tplace[1] += 0.08f;//todo
		if (tplace[1] >= 1.5f) tplace[1] = 1.5f;
		break;
	}
	case 'k': {
		tplace[1] -= 0.08f;//todo
		if (tplace[1] <= -1.5f) tplace[1] = -1.5f;
		break;
	}
	case 'e': {
		tAnim = !tAnim;//todo
		break;
	}
	}
}

void mouse(int button, int state, int x1, int y1)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x = x1;//当左键按下时记录鼠标坐标
		y = y1;
	}
}

void motion(int x1, int y1)
{
	GLint dx = x - x1;
	GLint dy = y - y1;
	x_angle -= 360 * (GLfloat)dy / (GLfloat)wHeight;//根据屏幕上鼠标滑动的距离来设置旋转的角度
	y_angle -= 360 * (GLfloat)dx / (GLfloat)wWidth;
	x = x1;//记录此时的鼠标坐标，更新鼠标坐标
	y = y1;
	//glutPostRedisplay();
}

void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);			// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5,5,5,1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);/*void glLightfv(
		 GLenum  light,
		 GLenum  pname,
   const GLfloat *params
);*/
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);
	//glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	glRotatef(x_angle, 1.0, 0.0, 0.0);
	glRotatef(y_angle, 0.0, 1.0, 0.0);
	Draw_Scene();						// Draw Scene

	glutSwapBuffers();
}



int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(960, 960);
	int windowHandle = glutCreateWindow("Ex 3");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	//glutMouseWheelFunc(mouseWheel);glut用不了
	glutIdleFunc(idle);

	glutMainLoop();//enter event queue
	return 0;
}


