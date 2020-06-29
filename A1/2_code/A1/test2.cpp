#include<GL\glut.h>
#include<math.h>
#define PI 3.1415926//定义pi，便于进行三角函数运算
typedef struct glvector2f {
	GLfloat x;
	GLfloat y;//定义向量结构
}glpoint2f, glvector2f;

/*
画出一个菱形
*/

void glstar_part(glpoint2f P, glpoint2f Q) {//P为中心，Q为P对应顶点，MN为两侧顶点
	float k1 = tan(PI / 10) / (tan(PI / 5) + tan(PI / 10)); //tan18 / （tan36 + tan18）
	float k2 = tan(PI / 5);//tan36

	glvector2f PQ = { Q.x - P.x , Q.y - P.y };
	glvector2f PH = { k1 * PQ.x , k1 * PQ.y };
	glvector2f HM = { k2 * PH.y , (-k2) * PH.x };//逆时针旋转90的垂直向量为（y，-x）

	glpoint2f M = { P.x + PH.x + HM.x , P.y + PH.y + HM.y };
	glpoint2f N = { P.x + PH.x - HM.x , P.y + PH.y - HM.y };//利用向量得出坐标

	glBegin(GL_POLYGON);//画四边形
	glVertex2f(P.x, P.y);
	glVertex2f(M.x, M.y);
	glVertex2f(Q.x, Q.y);
	glVertex2f(N.x, N.y);
	glEnd();
}

/*
由中心和当前顶点通过向量的旋转公式计算出下一次的顶点坐标
*/

void rotate(glpoint2f P, glpoint2f *Q) {
	float rad = 2 * PI / 5;

	glvector2f PQ = { Q->x - P.x , Q->y - P.y };//PQ向量
	glvector2f Pq = {
		cos(rad) * PQ.x + sin(rad) * PQ.y,
		cos(rad) * PQ.y + sin(rad) * (-PQ.x)
	}; //PQ'向量，由旋转性质可推导
	Q->x = P.x + Pq.x;
	Q->y = P.y + Pq.y;
}

/*
画五个菱形组成一个五角星，其中通过rotate旋转函数得出下一次的顶点坐标
*/

void glstar(GLfloat P_x, GLfloat P_y, GLfloat Q_x, GLfloat Q_y) {
	glpoint2f P = { P_x , P_y };
	glpoint2f Q = { Q_x , Q_y };
	for (int i = 0; i < 5; ++i) {
		glstar_part(P, Q);
		rotate(P, &Q);
	}
}

void display() {
	//定义长宽比为3：2的红色背景
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(-0.9, 0.6);
	glVertex2f(0.9, 0.6);
	glVertex2f(0.9, -0.6);
	glVertex2f(-0.9, -0.6);
	glEnd();

	glColor3f(1, 1, 0);
	glstar(-0.60, 0.30, -0.60, 0.48);
	glstar(-0.30, 0.48, -0.24, 0.48);
	glstar(-0.18, 0.36, -0.24, 0.36);
	glstar(-0.18, 0.18, -0.18, 0.24);
	glstar(-0.30, 0.06, -0.24, 0.06);//各个五角星的中心坐标和第一个顶点的坐标由图片得出...

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(400, 400);
	glutCreateWindow("My First Glut!");
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}