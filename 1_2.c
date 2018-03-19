#include <glut.h>

void init();

void display();

static int delay = 1;//1


int main(int argc, char* argv[])

{
	
	void timer(int);

	glutInit(&argc, (char**)argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutCreateWindow("Prog08: hidden surface removal");

	glutTimerFunc(delay, timer, 0);
	
	glutDisplayFunc(display);

	

	init();

	glutMainLoop();

	return 0;

}

void init()

{
	
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glOrtho(0.0, 50.0, 0.0, 50.0, -50.0, 50.0);
	
	glEnable(GL_DEPTH_TEST);

}

void display()

{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(15, 15, 35); glVertex3f(35, 15, 35); glVertex3f(35, 35, 35); glVertex3f(15, 35, 35);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(15, 15, 35); glVertex3f(35, 15, 35); glVertex3f(40, 20, 15); glVertex3f(20, 20, 15);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(20, 20, 15); glVertex3f(40, 20, 15); glVertex3f(40, 40, 15); glVertex3f(20, 40, 15);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(20, 40, 15); glVertex3f(40, 40, 15); glVertex3f(35, 35, 35); glVertex3f(15, 35, 35);
	glEnd();
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(15, 15, 35); glVertex3f(15, 35, 35); glVertex3f(20, 40, 15); glVertex3f(20, 20, 15);
	glEnd();
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(40, 20, 15); glVertex3f(40, 40, 15); glVertex3f(35, 35, 35); glVertex3f(35, 15, 35);
	glEnd();

	glFlush();

}

void timer(int t) {

	glutPostRedisplay();

	glutTimerFunc(delay, timer, t);

}
