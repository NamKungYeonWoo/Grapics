#include <glut.h>
#include <math.h>
GLint time=0,day=0;
int delay = 5;
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // load an identity matrix
	glColor3f(1.0,0.3,0.3);
	glutWireSphere(0.2,20,16);
	glPushMatrix();
		glRotatef((GLfloat)day * 360 / 365, 0.0, 1.0, 0.0);
		glTranslatef(0.7, 0.0, 0.0);
		glRotatef(-(GLfloat)day * 360 / 365, 0.0, 1.0, 0.0);
		glPushMatrix();
			glRotatef(23.5, 0.0, 0.0, 1.0);
			glRotatef((GLfloat)time * 360 / 24, 0.0, 1.0, 0.0);
			glColor3f(0.5, 0.6, 0.7);
			glutWireSphere(0.1, 10, 8);		
		glPopMatrix();
		glPushMatrix();
			glRotatef(-18.5, 0.0, 0.0, 1.0);
			glRotatef((GLfloat)day * 360 / 30, 0.0, 1.0, 0.0);
			glTranslatef(0.2, 0.0, 0);	
			glColor3f(0.9, 0.8, 0.2);
			glutWireSphere(0.04, 10, 8);
		glPopMatrix();
	glPopMatrix();
	glFlush();
}
void timer(int t)
{
	time++;
	if (time == 24)
		day++;
	time %= 24;
	glutPostRedisplay();
	glutTimerFunc(delay,timer, 1);
}
int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Home Work : sun-earth-moon animation");
	glutTimerFunc(delay, timer, 0);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
