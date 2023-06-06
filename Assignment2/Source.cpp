//#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <ctime>
//#include <iostream>
#include <stdlib.h>

#include"main.h"
#include"menu.h"
#include"display.h"
//#include"display.cpp"
#include"util.h"

#define ANGLE 10
#define RADIANS (M_PI/180)

/*class Planet {
public:
    float radius, distance, orbit, orbitSpeed, axisTilt, axisAni;
    Planet(float _radius, float _distance, float _orbit, float _orbitSpeed, float _axisTilt, float _axisAni) {

    void drawSmallOrbit(void) {
        glPushMatrix();
        glColor3ub(255, 255, 255);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glutWireTorus(0.001, distance, 100.0, 100.0);
        glPopMatrix();
    }
        glRotatef(orbit, 0.0, 1.0, 0.0);

void orbitalTrails(void) {
    glPushMatrix();
    glColor3ub(255, 255, 255);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glutWireTorus(0.001, ear.distance, 100.0, 100.0);
    glPopMatrix();
}*/

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Assignment II");
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    //glShadeModel(GL_FLAT);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutSpecialFunc(specialKey); //register a special keyboard function.
   //Creates Menu on Right Click
    GenMenu();
    timer(0);
    //gluDeleteQuadric(quadric);
    glutMainLoop();
    return EXIT_SUCCESS;
}