// main.cpp : 定义控制台应用程序的入口点。
//

#include "glut.h"
#define PI 3.1415926
float fTranslate = 0.0f;
float fRotate = 0.0f;
float fScale = 1.0f;

/*
draw cube
*/
void Draw_Cube(GLfloat x1 , GLfloat x2 , GLfloat y1 , GLfloat y2 , GLfloat z1 , GLfloat z2){
	//设置立方体的8个顶点坐标
	GLfloat V[8][3]{
		x1 , y1 , z1,
		x1 , y2 , z1,
		x2 , y2 , z1,
		x2 , y1 , z1,
		x2 , y1 , z2,
		x2 , y2 , z2,
		x1 , y2 , z2,
		x1 , y1 , z2,
	};
	//设置立方体的六个面对应顶点
	GLint Planes[6][4]{
		0 , 1 , 2 , 3,
		4 , 5 , 6 , 7,
		2 , 3 , 4 , 5,
		0 , 1 , 6 , 7,
		1 , 2 , 5 , 6,
		0 , 3 , 4 , 7,
	};
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 4; ++j)
			glVertex3fv(V[Planes[i][j]]);
	glEnd();
}
/*
draw table
*/
void Draw_Table() {
	Draw_Cube(0.0, 1.0, 0.0, 0.8, 0.6, 0.8);//Table Top
	//Table Legs
	Draw_Cube(0.1, 0.3, 0.1, 0.3, 0.0, 0.6);
	Draw_Cube(0.1, 0.3, 0.5, 0.7, 0.0, 0.6);
	Draw_Cube(0.5, 0.7, 0.1, 0.3, 0.0, 0.6);
	Draw_Cube(0.5, 0.7, 0.5, 0.7, 0.0, 0.6);
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void redraw()
{
	// If want display in wireframe mode
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	glPushMatrix();
	glTranslatef(-2.8f, 0.0f, -6.0f);		// Place the triangle Left
	glTranslatef(0.0f, fTranslate, 0.0f);	// Translate in Y direction
	Draw_Table();						// Draw Table					
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glTranslatef(0.0f, 0.0f, 0.0f);
											//glRotatef(GLfloat theta, GLfloatx, GLfloat y, GLfloat z);参数为角度和旋转轴
	Draw_Table();				// Draw Table
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0f, 0.0f, -6.0f);			// Place the triangle at Right
	glScalef(fScale, fScale, fScale);	
	// glScalef(GLfloat x, GLfloat y, GLfloatz);参数为各坐标缩放程度
	glTranslatef(-0.5f, 0.0f, 0.0f);
	Draw_Table();				// Draw Table
	glPopMatrix();

	fTranslate += 0.001f;
	fRotate += (0.5/PI);
	fScale -= 0.001f;

	if (fTranslate > 0.9f) fTranslate = 0.0f;
	if (fScale < 0.4f) fScale = 1.0f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Exercise2");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}


