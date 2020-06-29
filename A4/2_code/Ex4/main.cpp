// glutEx1.cpp : 定义控制台应用程序的入口点。
//
//注意FPS函数的应用

#include <stdlib.h>
#include "glut.h"
#include <stdio.h>
#include <string.h>

#include "stanford_bunny.h"

float eye[] = {0, 4, 6};
float center[] = {0, 0, 0};
//float bunny_place[][3] = { {2.0,4.5,-1.5} ,{2.0,4.5,-2.5} };

float fDistance = 0.2f;
float fRotate = 0;
bool bAnim = false;

bool bDrawList = false;
GLint tableList=0;
int count = 1;
int ox = 0, oy = 0, oz = 0;
int px = 0, py = 0, pz = 0;


void DrawTable()
{
	//table
	glPushMatrix();
	glTranslatef(0, 3.5, 0);
	glScalef(5, 1, 4);
	glutSolidCube(1.0);
	glPopMatrix();
	//legs
	glPushMatrix();
	glTranslatef(1.5, 1.5, 1);
	glScalef(1, 3, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1.5, 1);
	glScalef(1, 3, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1.5, -1);
	glScalef(1, 3, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1.5, -1);
	glScalef(1, 3, 1);
	glutSolidCube(1.0);
	glPopMatrix();
}

GLint GenTableList()
{
	GLint lid = glGenLists(2);//创建空列表并返回第一个列表索引
	
	glNewList(lid, GL_COMPILE);
	DrawBunny();
	glEndList();

	glNewList(lid + 1, GL_COMPILE);
	DrawTable();
	glEndList();
	return lid;
}

void Draw_Table_List()
{
	glPushMatrix();
	glTranslatef(2.0, 4.5, -1.5);
	glScalef(2, 2, 2);
	for (int i = 0; i < count; i++) {
		glCallList(tableList);//调用兔子的列表
		if (i == 3 || i == 7 || i == 11)
			glTranslatef(-0.6, 0, -1.5);
		else glTranslatef(0, 0, 0.5);
	}
	glPopMatrix();

	glCallList(tableList + 1);//调用桌子的列表
}

void DrawScene()
{
	glPushMatrix();
	glTranslatef(2.0, 4.5, -1.5);
	glScalef(2, 2, 2);
	for (int i = 0; i < count; i++) {
		DrawBunny();
		if (i == 3 || i == 7 || i == 11)
			glTranslatef(-0.6, 0, -1.5);
		else glTranslatef(0, 0, 0.5);
	}    
	glPopMatrix();

	DrawTable();
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width/(GLfloat)height;
	gluPerspective(45, whRatio, 1, 1000);	

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void idle()
{
	if (bAnim)
		fRotate += 0.5f;
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27:
	case 'q': {exit(0); break; }

	case 'a': 
		{
			eye[0] += fDistance; 
			center[0] += fDistance;
			break;
		}
	case 'd': 
		{
			eye[0] -= fDistance;
			center[0] -= fDistance;
			break;
		 }
	case 'w': 
		{
			eye[1] -= fDistance;
			center[1] -= fDistance; 
			break;
		}
	case 's': 
		{
			eye[1] += fDistance;
			center[1] += fDistance;
			break;
		}
	case 'z': 
		{
			eye[2] *= 0.95;
			break; 
		}
	case 'c': 
		{
			eye[2] *= 1.05;
			break;
		 }
	case 'l':
		{
			bDrawList = !bDrawList;	// 切换显示列表和非显示列表绘制方式
			break;
		}
	case ' ':
		{
			bAnim = !bAnim; 
			break;
		}
	case 'i':
		{
			count++;
			if (count >= 16) count = 16;
			break;
		}
	case 'k':
		{
			count--;
			if (count <= 0)	count = 0;
		}
	default: break;
	}
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		px = x;
		py = y;
	}
}

void motion(int x, int y) {
	GLint dx = px - x;
	GLint dy = py - y;
	ox -= 360 * (GLfloat)dy / (GLfloat)480;
	oy -= 360 * (GLfloat)dx / (GLfloat)480;
	px = x;
	py = y;
}

void getFPS()
{
	static int frame = 0, time, timebase = 0;
	static char buffer[256];

	char mode[64];
	if (bDrawList)
		strcpy(mode, "display list");
	else
		strcpy(mode, "naive");

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(buffer,"FPS:%4.2f %s",
			frame*1000.0/(time-timebase), mode);
		timebase = time;		
		frame = 0;
	}
	char *c;
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
	glPushMatrix();               // 保存原矩阵
	glLoadIdentity();             // 装入单位矩阵
	glOrtho(0,480,0,480,-1,1);    // 位置正投影
	glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
	glPushMatrix();               // 保存原矩阵
	glLoadIdentity();             // 装入单位矩阵
	glRasterPos2f(10,10);
	for (c=buffer; *c != '\0'; c++) {		
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
	glPopMatrix();                // 重置为原保存矩阵
	glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
	glPopMatrix();                // 重置为原保存矩阵
	glEnable(GL_DEPTH_TEST);	
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0.5, 0, 1);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0, 5, 50)，Y轴向上

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat gray[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light_pos[] = {10, 10, 10, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,gray);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glEnable(GL_LIGHT0);

	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis

	glScalef(0.4, 0.4, 0.4);
	//glLoadIdentity();
	glRotated(ox, 1.0, 0.0, 0.0);
	glRotated(oy, 0.0, 1.0, 0.0);
	glRotated(oz, 0.0, 0.0, 1.0);
	//glTranslatef(px, py, pz);
	if(!bDrawList)
		DrawScene();						// old way
	else 
		Draw_Table_List();                  // new way

	getFPS();
	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480,480);
	int windowHandle = glutCreateWindow("Exercise 4");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(idle);

	tableList = GenTableList();

	glutMainLoop();
	return 0;
}


