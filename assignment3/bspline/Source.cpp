#include <GL/glut.h>
#include <GL/gl.h>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <iostream>

using namespace std;

//u and v are the parametic variables
int WIDTH_WINDOWS;
int HEIGHT_WINDOWS;

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

Position bspline(float u) {
    Position result = { 0.0f, 0.0f };
    int n = numControlPoints - 1;

    for (int i = 0; i <= n; ++i) {
        float blend = 1.0f;
        for (int j = 0; j <= n; ++j) {
            if (j != i) {
                blend *= (u - j) / (i - j);
            }
        }
        result.x += controlPoints[i].x * blend;
        result.y += controlPoints[i].y * blend;
    }

    return result;
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
        controlPoints.push_back(Position(xPos, yPos));
        numControlPoints++;

        if (numControlPoints >= 4) {
            glutTimerFunc(0, animate, 0);
        }

        glutPostRedisplay();
    }
}

void drawTeapot(float scale) {
    glPushMatrix();
    glScalef(scale, scale, scale);
    glutWireTeapot(0.5);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // background black
    glClearDepth(1.0f);

    glMatrixMode(GL_MODELVIEW); //

    glPointSize(5.0f);
    glBegin(GL_POINTS);

    for (int i = 0; i < numControlPoints; ++i) {
        glVertex2f(controlPoints[i].x, controlPoints[i].y);
    }

    glEnd();

    if (numControlPoints >= 4) {
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
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("B-Spline Interpolation");

    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}