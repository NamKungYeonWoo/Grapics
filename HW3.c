#include <glut.h>
#include <math.h>
#define PI 3.141592
GLfloat scale = 0.1;
GLfloat px = 0.0;
GLfloat py = 0.0;
GLfloat pz = 0.0;
GLint axis = 1;
GLfloat R = 10;
int delay = 20;
int type = 1;
GLfloat p1[2];
GLfloat theta[3] = { 0 };
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glFrustum(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // load an identity matrix
	glColor3f(0, 0, 0);
	glTranslatef(px, py, pz);
	glRotatef(theta[0], 0.0, 1.0, 0.0);
	glRotatef(-theta[1], 1.0, 0.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	R = sqrt(pow(px, 2) + pow(py, 2) + pow(pz + 10, 2));
	glutWireTeapot(scale);
	glFlush();
}
void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'w') {
		pz += 0.005;
		scale += 0.005;
	}
	if (key == 'a') {
		px += 0.01;
	}
	if (key == 's') {
		pz -= 0.005;
		scale -= 0.005;
	}
	if (key == 'd') {
		px -= 0.01;
	}
}
void mouse_handler(int btn, int state, int x, int y)

{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		p1[0] = x;
		p1[1] = y;
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		px = px + ((p1[0] - x) / 25);
		py = py - ((p1[1] - y) / 25);
		pz = sqrt(pow(R, 2) - pow(px, 2) - pow(py, 2)) - 10;
		theta[0] = ((atan2f(R, px) * 180 / PI) - 90) * 10;
		theta[1] = ((atan2f(R, py) * 180 / PI) - 90) * 10;
		theta[2] = ((atan2f(R, pz) * 180 / PI) - 90) * 10;
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
