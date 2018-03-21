#include <glut.h>
#include <math.h>
#include <stdio.h>
#define PI 3.141592
void init();
void display();
static int delay = 100;

GLfloat angle = 0;
int bias = -5;
unsigned char frame[240][416];
int main(int argc, char* argv[])
{
	void timer(int);
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog10: image in 3D");
	glutTimerFunc(delay, timer, 0);
	glutDisplayFunc(display);
	init();
	glutMainLoop();

	return 0;
}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0.0, 416.0, 0.0, 240.0, -500.0, 500.0);
	glPointSize(8);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	int i, j;
	FILE *filename;
	fopen_s(&filename,"testo.y", "rb");
	fread(frame,416*240,sizeof(char),filename);
	fclose(filename);
}
void display(){
	GLfloat x, y, z;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int i, j;
	
	if (angle==0||angle==80) {
		bias *= -1;
	}
	angle += bias;
	glBegin(GL_POINTS);
	for (i = 0; i < 240; i++) {
		for (j = 0; j < 416; j++) {
			GLfloat v = frame[i][j];
			glColor3f(v/255,v/255,v/255);
			x = j*cos(angle*PI/180);
			y = 239 - i;
			z = j*sin(angle*PI / 180);
			glVertex3f(x,y,z);
		}
	}	glEnd();
	glFlush();
}
void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}
