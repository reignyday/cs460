#include <GL/glut.h>
#include <GL/gl.h>

#include <iostream>
#include <vector>

using namespace std;

vector<std::pair<float, float>> controlPoints;
vector<float> controlPointsZ; 

void drawPoint(float x, float y, float z) {
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
}

void drawQuadraticBSpline() {
    glColor3f(0.0, 1.0, 0.0); // Set color to green for the B-spline curve
    glBegin(GL_LINE_STRIP);

    // Iterate through the parameter values (t) for the curve
    for (float t = 0.0; t <= 1.0; t += 0.01) {
        float x = (1 - t) * (1 - t) * controlPoints[0].first + 2 * (1 - t) * t * controlPoints[1].first + t * t * controlPoints[2].first;
        float y = (1 - t) * (1 - t) * controlPoints[0].second + 2 * (1 - t) * t * controlPoints[1].second + t * t * controlPoints[2].second;
        float z = (1 - t) * (1 - t) * controlPointsZ[0] + 2 * (1 - t) * t * controlPointsZ[1] + t * t * controlPointsZ[2];

        glVertex3f(x, y, z);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0); // Set color to red for control points
    for (size_t i = 0; i < controlPoints.size(); ++i) {
        drawPoint(controlPoints[i].first, controlPoints[i].second, controlPointsZ[i]);
    }

    drawQuadraticBSpline();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float normalizedX = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
        float normalizedY = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);

        controlPoints.emplace_back(normalizedX, normalizedY);
        // For simplicity, set Z values to 0. You may adjust this based on your needs.
        controlPointsZ.push_back(0.0);

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Quadratic B-spline");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    glutMainLoop();

    return 0;
}
