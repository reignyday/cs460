#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <assert.h>
#include "time.h"
#include <iomanip>

using namespace std;
int k = 0;
int subnum = 3;

float r = 0.0f, g = 0.0f, b = 1.0f;

const float a = .525731112119133606;
const float d = .850650808352039932;

//vertices
float v[12][3] = { {-a, 0.0, d}, {a, 0.0, d}, {-a, 0.0, -d}, {a, 0.0, -d},
					   {0.0, d, a}, {0.0, d, -a}, {0.0, -d, a}, {0.0, -d, -a},
					   {d, a, 0.0}, {-d, a, 0.0}, {d, -a, 0.0}, {-d, -a, 0.0} };
//triangle indices
int triangle_indices[20][3] = { {0, 1, 4}, {0, 4, 9}, {9, 4, 5}, {4, 8, 5}, {4, 1, 8},
								{8, 1, 10}, {8, 10, 3}, {5, 8, 3}, {5, 3, 2}, {2, 3, 7},
								{7, 3, 10}, {7, 10, 6}, {7, 6, 11}, {11, 6, 0}, {0, 6, 1},
								{6, 10, 1}, {9, 11, 0}, {9, 2, 11}, {9, 5, 2}, {7, 11, 2} };

struct Color {
	float r = 0.0;
	float g = 0.0;
	float b = 0.0;
};


void normalize(float v[3]) {
	float d = sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
	assert(d > 0);
	v[0] = v[0] / d;
	v[1] = v[1] / d;
	v[2] = v[2] / d;
}

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClearColor(0.5, 0.5, 0.2, 0.5);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100);
}

void getColor(float c[]) {
	static int j = 0;
	j++;
	srand(j);
	for (int i = 0; i < 3; i++) {
		c[i] = (rand() % 256) / 255.0;
	}
}

//this function should draw a sphere using subdivision 4nx20 spherical approximation
void trig(float * v1, float * v2, float * v3) {
	float c[3];

	getColor(c);
	glColor3fv(c);
	k++;
	//cout << ::k << endl;
	glBegin(GL_TRIANGLES);
		glNormal3fv(v1);
		glVertex3fv(v1);
		glNormal3fv(v2);
		glVertex3fv(v2);
		glNormal3fv(v3);
		glVertex3fv(v3);
	glEnd();
}

void subdivide(float * v1, float * v2, float * v3, long d) {
	float edge1[3];
	float edge2[3];
	float edge3[3];

	if (d == 0) {
		trig(v1, v2, v3);
		return;
	}

	for (int i = 0; i < 3; i++) {
		edge1[i] = (v1[i] + v2[i]) / 2.0;
		edge2[i] = (v2[i] + v3[i]) / 2.0;
		edge3[i] = (v3[i] + v1[i]) / 2.0;
	}

	normalize(edge1);
	normalize(edge2);
	normalize(edge3);

	subdivide(v1, edge1, edge3, d - 1);
	subdivide(v2, edge2, edge1, d - 1);
	subdivide(v3, edge3, edge2, d - 1);
	subdivide(edge1, edge2, edge3, d - 1);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(8.0, 8.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//glPointSize(1.0);

	Color black = { 0.0, 0.0, 0.0 };
	Color white = { 1.0, 1.0, 1.0 };
	Color red = { 1.0, 0.0, 0.0 };
	Color lightblue = { 0.5, 0.7, 1.0 };

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//glColor3f(1, 0, 0);
	//glutWireSphere(1, 30, 30);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 20; i++) {
		subdivide(&v[triangle_indices[i][0]][0], &v[triangle_indices[i][1]][0], &v[triangle_indices[i][2]][0], subnum);
	}
	glEnd();
	cout << "This sphere is comprised of " << ::k << " triangles." << endl;
	//glutSwapBuffers();
	glFlush();
}

int main(int argc, char** argv) {
	clock_t start, end;
	start = clock();
	// create a window
	glutInit(&argc, argv);

	// use double buffer for animation
	// check OpenGL redbook 7e page 22 "Animation"
	//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	// create a window
	glutInitWindowPosition(100, 100);
	//glutInitWindowSize(800, 600);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Final Assignment");

	init();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//glShadeModel(GL_SMOOTH);
	//glEnable(GL_DEPTH_TEST);

	//glMatrixMode(GL_PROJECTION);
	//glOrtho(-400.0, 400.0, -300.0, 300.0, 1.0, -1.0);
	glutDisplayFunc(display);
	//glutIdleFunc(display);
	glViewport(0, 0, 700, 700);
	cout << "This sphere is comprised of " << ::k << " triangles." << endl;
	cout << "The original icosahedron was subdivided " << subnum << " times." << endl;
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "Time taken by program is : " << fixed << time_taken << setprecision(5) << " sec " << endl;
	// event processing loop
	glutMainLoop();

	return 0;
}
