#include <GL/glut.h>
#include <GL/gl.h>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <math.h>
#include <iostream>

#ifndef PI
#define PI 3.14159265358979323846
#endif

using namespace std;

//u and v are the parametic variables
int WIDTH_WINDOWS;
int HEIGHT_WINDOWS;

// for x-y-z axis
GLfloat redSurface[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat greenSurface[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat blueSurface[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat darkSurface[] = { 1.0, 0.0, 0.0, 1.0 };
//for lighting
GLfloat lightAmbient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat lightDiffuse[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat lightSpecular[] = { 0.4, 0.4, 0.4, 1.0 };
//GLfloat lightPosition[] = { 100, 100.0, 100.0, 0.0 };
GLfloat lightPosition[] = { 55.0, 100.0, 55.0, 0.0 };
GLfloat lightDirection[] = { 0.0, 0.0, -1.0 };
GLfloat shininess[] = { 50 };
// for the materials
GLfloat matAmbient[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat matDiffuse[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat blue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };

struct Position {
    Position() : x(0), y(0), z(0), u(0), v(0) {}
    Position(float m, float n) {
        x = m; y = n; z = 0; u = 0; v = 0;
    }
    Position(float m, float n, float t) {
        x = m; y = n; z = t; u = 0; v = 0;
    }
    Position(float m, float n, float t, float i, float j) {
        x = m; y = n; z = t; u = i; v = j;
    }
    float x;
    float y;
    float z;
    float u;
    float v;
};

vector<Position> controlPoints;
int numControlPoints = 0;
int numFrames = 100;
int currentFrame = 0;

float t = 0.0f;
float animationDuration = 4.0f;
float frameDuration = animationDuration / numFrames;

void drawCurve() {
    if (controlPoints.size() >= 4) {
        glLineWidth(2.0f);
        glColor3f(0.0, 1.0, 0.0); // Curve color

        glBegin(GL_LINE_STRIP);
        int numseg = 100;

        for (int i = 0; i <= numseg; ++i) {
            float t = static_cast<float>(i) / numseg;
            //split up calculations for more efficient calculation
            float tmin1 = 1.0 - t;
            float tmin1sq = pow(tmin1, 2);
            float tmin1cub = tmin1sq * tmin1;
            float tsq = pow(t, 2);
            float tcub = tsq * t;

            float x = ((tmin1cub * controlPoints[0].x) + (3 * t * tmin1sq * controlPoints[1].x) +
                3 * tsq * tmin1 * controlPoints[2].x +
                tcub * controlPoints[3].x);

            float y = (tmin1cub * controlPoints[0].y +
                3 * t * tmin1sq * controlPoints[1].y +
                3 * tsq * tmin1 * controlPoints[2].y +
                tcub * controlPoints[3].y);

            float z = (tmin1cub * controlPoints[0].z +
                3 * t * tmin1sq * controlPoints[1].z +
                3 * tsq * tmin1 * controlPoints[2].z +
                tcub * controlPoints[3].z);

            glVertex3f(x, y, z);
        }
        glEnd();
    }
}


void animate(int value) {
    t += frameDuration;
    currentFrame++;

    if (currentFrame >= numFrames) {
        currentFrame = 0;
        t = 0.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / 60, animate, 0);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float xPos = static_cast<float>(x) / glutGet(GLUT_WINDOW_WIDTH);
        float yPos = 1.0f - static_cast<float>(y) / glutGet(GLUT_WINDOW_HEIGHT);
        controlPoints.push_back(Position(xPos, yPos, 0.0f));
        numControlPoints++;

        if (numControlPoints >= 4) {
            glutTimerFunc(0, animate, 0);
        }

        glutPostRedisplay();
    }
}

void drawTeapot(float x, float y, float z, float angle) {
    glPushMatrix();
    //glScalef(scale, scale, scale);
    glTranslatef(x, y, z);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glutWireTeapot(0.1);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    glMatrixMode(GL_MODELVIEW); //

    glPointSize(5.0f);
    glBegin(GL_POINTS);

    for (int i = 0; i < numControlPoints; ++i) {
        glVertex3f(controlPoints[i].x, controlPoints[i].y, controlPoints[i].z);
    }

    glEnd();
    drawCurve();

    if (numControlPoints >= 4) {
        glColor3f(1.0f, 0.0f, 0.0f);

        float t = static_cast<float>(currentFrame) / numFrames;

        float tmin1 = 1.0f - t;
        float tmin1sq = tmin1 * tmin1;
        float tmin1cub = tmin1sq * tmin1;
        float tsq = t * t;
        float tcub = tsq * t;

        float x = ((tmin1cub * controlPoints[0].x) + (3 * t * tmin1sq * controlPoints[1].x) + (3 * tsq * tmin1 * controlPoints[2].x) + (tcub * controlPoints[3].x));
        float y = ((tmin1cub * controlPoints[0].y) + (3 * t * tmin1sq * controlPoints[1].y) + (3 * tsq * tmin1 * controlPoints[2].y) + (tcub * controlPoints[3].y));
        float z = ((tmin1cub * controlPoints[0].z) + (3 * t * tmin1sq * controlPoints[1].z) + (3 * tsq * tmin1 * controlPoints[2].z) + (tcub * controlPoints[3].z));

        glPushMatrix();
        glTranslatef(x, y + 0.05, z);
        glRotatef(50, 0, 1, 0);
        glRotatef((t * 360.0), 1, 0, 0);
        glutSolidTeapot(0.1);
        glPopMatrix();
    }
    
        glEnable(GL_NORMALIZE);

    	glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);

		//GLfloat ambfull[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
        glShadeModel(GL_FLAT);

 /*  if (numControlPoints >= 4) {
        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_LINE_STRIP);

        for (int i = 0; i <= currentFrame; ++i) {
            float u = i * frameDuration;
            Position p = bspline(u);
            glVertex2f(p.x, p.y);
        }

        glEnd();

        //dslid object (teapot)
        glColor3f(1.0f, 0.0f, 0.0f);
        Position slidingPoint = bspline(t);

        glPushMatrix();
        glTranslatef(slidingPoint.x, slidingPoint.y, 0.0f);
        drawTeapot(0.1f);
        glPopMatrix();
    }*/

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("B-Spline");

    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}