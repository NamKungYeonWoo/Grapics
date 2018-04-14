#include <glut.h>
#include <math.h>
#define PI 3.141592
int delay = 20;
GLfloat p1[3] = { 0,0,0 };//x,y,z
GLfloat p2[3] = { 0,0,1 };//x,y,z
GLfloat theta[2] = { 0,0 };
GLfloat dx[2], dy[2], dz[2];
GLfloat axis = 1;
GLfloat p3[2];
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glFrustum(-1, 1, -1, 1, 1, 20);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity(); // load an identity matrix

	gluLookAt(p1[0], p1[1], p1[2], p2[0], p2[1], axis* p2[2], 0, 1, 0);
	glPushMatrix();
		glTranslatef(0, 0, 2);
		glColor3f(0.0, 0.8, 0.7);
		glutWireTeapot(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 0, -2);
		glColor3f(1.0, 0.0, 0.0);
		glutWireTeapot(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(2, 0, 0);
		glColor3f(0.0, 1.0, 0.0);
		glutWireTeapot(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-2, 0, 0);
		glColor3f(0.0, 0.0, 1.0);
		glutWireTeapot(0.5);
	glPopMatrix();
	glFlush();
}
void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'w') {
		p1[0] += 0.01*sin((theta[0] * PI) / 180);
		p1[2] += 0.01*cos((theta[0] * PI) / 180);
		p2[0] += 0.01*sin((theta[0] * PI) / 180);
		p2[2] += 0.01*cos((theta[0] * PI) / 180);
	}
	if (key == 'a') {
		p1[0] += 0.01*sin(((theta[0] + 90) * PI) / 180);
		p1[2] += 0.01*cos(((theta[0] + 90)  * PI) / 180);
		p2[0] += 0.01*sin(((theta[0] + 90)  * PI) / 180);
		p2[2] += 0.01*cos(((theta[0] + 90)  * PI) / 180);
	}
	if (key == 's') {
		p1[0] -= 0.01*sin((theta[0] * PI) / 180);
		p1[2] -= 0.01*cos((theta[0] * PI) / 180);
		p2[0] -= 0.01*sin((theta[0] * PI) / 180);
		p2[2] -= 0.01*cos((theta[0] * PI) / 180);
	}
	if (key == 'd') {
		p1[0] -= 0.01*sin(((theta[0] + 90)  * PI) / 180);
		p1[2] -= 0.01*cos(((theta[0] + 90)  * PI) / 180);
		p2[0] -= 0.01*sin(((theta[0] + 90)  * PI) / 180);
		p2[2] -= 0.01*cos(((theta[0] + 90)  * PI) / 180);
	}

}
void mouse_handler(int btn, int state, int x, int y)

{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		dx[0] = x;
		dy[0] = y;

	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		dx[1] = x;
		dy[1] = y;
		p3[0] = (dx[1] - dx[0]) / 500;
		p3[1] = (dy[1] - dy[0]) / 500;
		theta[0] += p3[0] * 30;
		theta[1] += p3[1] * 30;
		if (theta[0]>360)
			theta[0] -= 360;
		if (theta[1]>360)
			theta[1] -= 360;
		if (theta[0]<-360)
			theta[0] += 360;
		if (theta[1]<-360)
			theta[1] += 360;
		p2[0] = p1[0] + sin((theta[0] * PI) / 180);
		p2[1] = p1[1] + sin((theta[1] * PI) / 180);
		p2[2] = p1[2] + cos(((360 - theta[0]) * PI) / 180);
	}

}
int main(int argc, char* argv[])
{
	void timer(int);
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("HW3:CAD");
	glutTimerFunc(delay, timer, 0);
	glutKeyboardFunc(keyboard_handler); // add keyboard handler
	glutMouseFunc(mouse_handler); // add mouse handler
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}
