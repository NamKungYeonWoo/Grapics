#include <math.h>
#include <glut.h>

// ---------------------------------------------------------------------------------------------
// Type definition
// ---------------------------------------------------------------------------------------------
int delay = 20;
typedef struct _object
{
	GLfloat*        vertices;    // vertex array
	GLfloat*        colors;      // color array
	GLubyte*        indices;     // index
	int             nums;        // number of vertices
	GLfloat         theta[3];    // rotation parameter (x, y, z)
	GLfloat         trans[3];		 // translation parameter
	struct _object* child;
} Object;

typedef struct _viewer
{
	GLfloat         eye[3];    // viewer position
	GLfloat         at[3];    // center
	GLfloat         up[3];    // up direction
} Viewer;

// ---------------------------------------------------------------------------------------------
// Data
// ---------------------------------------------------------------------------------------------

// array 1 (top)
GLfloat vertices1[][3] = { { -0.2,-1.0,-0.2 },{ 0.2,-1.0,-0.2 },{ 0.2,1.0,-0.2 },{ -0.2,1.0,-0.2 },
	{ -0.2,-1.0, 0.2 },{ 0.2,-1.0, 0.2 },{ 0.2,1.0, 0.2 },{ -0.2,1.0, 0.2 } };
GLfloat colors1[][3] = { { 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 1.0,1.0, 0.0 },{ 0.0,1.0, 0.0 },
	{ 0.0, 0.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0,1.0, 1.0 },{ 0.0,1.0, 1.0 } };
GLubyte indices1[] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };
GLfloat vertices2[][3] = { { -0.8,-0.1,-0.1 },{ 0.8,-0.1,-0.1 },{ 0.8,0.1,-0.1 },{ -0.8,0.1,-0.1 },
	{ -0.8,-0.1,0.1 },{ 0.8,-0.1,0.1 },{ 0.8,0.1,0.1 },{ -0.8,0.1,0.1 } };
GLfloat colors2[][3] = { { 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 1.0,1.0, 0.0 },{ 0.0,1.0, 0.0 },
	{ 0.0, 0.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0,1.0, 1.0 },{ 0.0,1.0, 1.0 } };
GLubyte indices2[] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };

// ---------------------------------------------------------------------------------------------
// Objects
// ---------------------------------------------------------------------------------------------

Object top,sb1;
Viewer v;
GLfloat dir = 1.0;

// ---------------------------------------------------------------------------------------------
// Functions
// ---------------------------------------------------------------------------------------------

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLfloat clip(GLfloat x)
{
	if (x < 0) return x + 360.0;
	if (x > 360.0) return x - 360.0;
	return x;
}

// ---------------------------------------------------------------------------------------------
// I/O
// ---------------------------------------------------------------------------------------------

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') v.eye[0] -= 0.1; if (key == 'X') v.eye[0] += 0.1;
	if (key == 'y') v.eye[1] -= 0.1; if (key == 'Y') v.eye[1] += 0.1;
	if (key == 'z') v.eye[2] -= 0.1; if (key == 'Z') v.eye[2] += 0.1;
}

void mouse_handler(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON   && state == GLUT_DOWN) dir = -dir;
}

void draw(Object* p)
{
	// transformation
	glTranslatef(p->trans[0], p->trans[1], p->trans[2]);
	glRotatef(p->theta[0], 1.0, 0.0, 0.0);
	glRotatef(p->theta[1], 0.0, 1.0, 0.0);
	glRotatef(p->theta[2], 0.0, 0.0, 1.0);

	// draw
	glVertexPointer(3, GL_FLOAT, 0, p->vertices);
	glColorPointer(3, GL_FLOAT, 0, p->colors);
	glDrawElements(GL_QUADS, p->nums, GL_UNSIGNED_BYTE, p->indices);
	if (p->child) {
		draw(p->child);
	}
}

void display()
{
	// clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup viewer
	glLoadIdentity();
	gluLookAt(v.eye[0], v.eye[1], v.eye[2], v.at[0], v.at[1], v.at[2], v.up[0], v.up[1], v.up[2]);

	// draw
	draw(&top);
	// flush & swap buffers
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	// GLUT initialization
	void timer(int);
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog26: multiple objects");

	// call-back functions
	glutKeyboardFunc(keyboard_handler);
	glutMouseFunc(mouse_handler);
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);
	// enable color/vertex array
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	// object initialization
	top.vertices = &vertices1[0][0];
	top.colors = &colors1[0][0];
	top.indices = &indices1[0];
	top.nums = 24;
	top.theta[0] = top.theta[1] = top.theta[2] = 0;
	top.trans[0] = top.trans[1] = top.trans[2] = 0;
	// initialize viewer
	v.eye[0] = 0.0; v.eye[1] = 0.0; v.eye[2] = 1.0;
	v.at[0] = 0.0; v.at[1] = 0.0; v.at[2] = 0.0;
	v.up[0] = 0.0; v.up[1] = 1.0; v.up[2] = 0.0;
	top.child = &sb1;
	sb1.vertices = &vertices2[0][0];
	sb1.colors = &colors2[0][0];
	sb1.indices = &indices2[0];
	sb1.nums = 24;
	sb1.theta[0] = sb1.theta[1] = sb1.theta[2] = 0;
	sb1.trans[0] = sb1.trans[2] = 0;
	sb1.trans[1] = 1.0;
	sb1.child = 0;
	init();
	glutMainLoop();

	return 0;
}
void timer(int t) {
	top.theta[2] += 2.0*dir;  top.theta[2] = clip(top.theta[2]);
	sb1.theta[2] += 4.0*dir;  sb1.theta[2] = clip(sb1.theta[2]);
	glutPostRedisplay();

	glutTimerFunc(delay, timer, t);

}
