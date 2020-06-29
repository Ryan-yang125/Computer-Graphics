#include "ObjLoader.h"
#include "glut.h"
#include <iostream>
//模型路径
string filePath;

ObjLoader objModel;
//实现移动鼠标观察模型所需变量
static float c = 3.1415926 / 180.0f;
static float r = 1.0f;
static int degree = 90;
static int oldPosY = -1;
static int oldPosX = -1;

//安置光源
void setLightRes() {
    GLfloat lightPosition[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHTING); //启用光源
    glEnable(GL_LIGHT0);   //使用指定灯光
}

//初始化
void init() {
    //cout << "Input model numbers : " << endl;
    //int n;
    //cin >> n;
    std::cout << "Input filepath ： " << endl;
    std::cin >> filePath;
    objModel.init(filePath);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1600, 800);
    glutCreateWindow("ObjLoader");
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    setLightRes();
    glEnable(GL_DEPTH_TEST);
}

void display()
{
    glColor3f(1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    setLightRes();
    glPushMatrix();

    gluLookAt(r * cos(c * degree), 0, r * sin(c * degree), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    //glTranslatef(0.0f, 0.0f, -35.0f);
    glTranslatef(0.0f, -7.0f, -10.0f);
    objModel.Draw();//绘制obj模型
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (GLdouble)width / (GLdouble)height, 1.0f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
}

//移动鼠标360观察模型
void moseMove(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        oldPosX = x; oldPosY = y;
    }
}
void changeViewPoint(int x, int y)
{
    int temp = x - oldPosX;
    degree += temp;
    oldPosX = x;
    oldPosY = y;
}

void myIdle()
{
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(moseMove);
    glutMotionFunc(changeViewPoint);
    glutIdleFunc(myIdle);
    glutMainLoop();
    return 0;
}