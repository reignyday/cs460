#include <GL/glut.h>
#include <GL/gl.h>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <iostream>

using namespace std;

float t = 0.0;
float v = 0.0005;

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

vector<Position> cubicPoints = {Position(0,100), Position(1.0 / 3.0, 250.0),Position(2.0 / 3.0, 150), Position(1.0, 450.0)
};

float lagrangecubic(float u, float x0, float x1, float x2, float x3, float y0, float y1, float y2, float y3) {
    float pow3 = (((u - x1) * (u - x2) * (u - x3)) / ((x0 - x1) * (x0 - x2) * (x0 - x3))) * y0;
    float pow2 = (((u - x0) * (u - x2) * (u - x3)) / ((x1 - x0) * (x1 - x2) * (x1 - x3))) * y1;
    float pow1 = (((u - x0) * (u - x1) * (u - x3)) / ((x2 - x0) * (x2 - x1) * (x2 - x3))) * y2;
    float pow0 = (((u - x0) * (u - x1) * (u - x2)) / ((x3 - x0) * (x3 - x1) * (x3 - x2))) * y3;

    return pow3 + pow2 + pow1 + pow0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // background black

    glPointSize(10.0f);

    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < 4; ++i) {
        glVertex2f(cubicPoints[i].x * 800, cubicPoints[i].y);
    }
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; ++i) {
        float u = i / 100.0;
        float x = u * 800;
        float y = lagrangecubic(u, cubicPoints[0].x, cubicPoints[1].x, cubicPoints[2].x, cubicPoints[3].x, cubicPoints[0].y, cubicPoints[1].y, cubicPoints[2].y, cubicPoints[3].y);
        glVertex2f(x, y);
    }
    glEnd();

    float teapotPos[2] = {t * 800, lagrangecubic(t, cubicPoints[0].x, cubicPoints[1].x, cubicPoints[2].x, cubicPoints[3].x, cubicPoints[0].y, cubicPoints[1].y, cubicPoints[2].y, cubicPoints[3].y)
    };

    //cout << teapotPos[0] << " " << teapotPos[1] << endl;

    /*glPushMatrix();
    glTranslatef(teapotPos[0], teapotPos[1], 0.0);
    glColor3f(0.0f, 1.0f, 0.0f);

    if (rotation) {
        glRotatef(120.0f, 0.0f, 0.0f, 1.0f); // Rotate by 120 degrees
        cout << "Rotating" << endl;
    }

    //if (fabs(t - (1.0 / 3.0)) < v || fabs(t - (2.0 / 3.0)) < v) {
    //if(t < (1.0 / 3.0) && (t + v) > (1.0/3.0)){//|| t == (2.0 / 3.0) || t == 1.0) {
    //if (fabs(t - (1.0 / 3.0)) < 0.001 || fabs(t - (2.0 / 3.0)) < 0.001 || fabs(t - 1.0) < 0.001) {
   //     glRotatef(120.0f, 0.0f, 0.0f, 1.0f); // Rotate by 120 degrees
    //    cout << "yup" << endl;
    //}
    glutWireTeapot(20);
    glPopMatrix();

        rotation = true;
    }
    else {
        rotation = false;
    }*/

    if (fabs(t - 1.0) < (25*v)) {
        glPushMatrix();
        glTranslatef(teapotPos[0], teapotPos[1], 0.0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glRotatef(-120.0f, 0.0f, 0.0f, 1.0f);
        glRotatef(-120.0f, 0.0f, 0.0f, 1.0f);
        glRotatef(-120.0f, 0.0f, 0.0f, 1.0f);
        glutWireTeapot(20);
        glPopMatrix();
        //cout << "Rotating" << endl;
    }
    else if (t > (2.0 / 3.0)) {
        glPushMatrix();
        glTranslatef(teapotPos[0], teapotPos[1], 0.0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glRotatef(-120.0f, 0.0f, 0.0f, 1.0f);
        glRotatef(-120.0f, 0.0f, 0.0f, 1.0f);
        glutWireTeapot(20);
        glPopMatrix();
        //cout << "Rotating" << endl;
    }
    else if (t > (1.0 / 3.0)) {
        glPushMatrix();
        glTranslatef(teapotPos[0], teapotPos[1], 0.0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glRotatef(-120.0f, 0.0f, 0.0f, 1.0f);
        glutWireTeapot(20);
        glPopMatrix();
        //cout << "Rotating" << endl;
    }
    else {
        glPushMatrix();
        glTranslatef(teapotPos[0], teapotPos[1], 0.0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glutWireTeapot(20);
        glPopMatrix();
    }

    t += v; //animation parameter

    if (t > 1.0) {
        t = 0.0;
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cubic Interpolation Animation");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glOrtho(-30, 830, 0, 500, -1, 1);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

