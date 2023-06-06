#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>
using namespace std;

float r = 0.0f, g = 0.0f, b = 1.0f;

struct Color {
	float r = 0.0;
	float g = 0.0;
	float b = 0.0;
};

void midpointcircle(int xcenter, int ycenter, int radius) {

	float decision = (5 / 4) - radius;
	int x = 0; //x (k)
	int y = radius;// this x,y is a point of the circle, 0 degrees

	//cout << "x:" << x << " y:" << y << endl;

	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_POINTS);
	glVertex2f(xcenter, ycenter + radius);
	glVertex2f(xcenter, ycenter - radius);
	glVertex2f(xcenter + radius, ycenter);
	glVertex2f(xcenter - radius, ycenter);
	glEnd();

	/*//for (int i = 0; i < 8; i++) {*/
	while (y > x) {
		x = x + 1; // formula for x (k+1)
		if (decision < 0) {
			decision = decision + (2 * x) + 1;
		}
		else {
			y = y - 1;// formula for y (k+1)
			decision = decision + (2 * x) + 1 - (2 * y);
		}

		glBegin(GL_POINTS);
		glVertex2f(xcenter + x, ycenter + y);
		//glVertex2f(x, y);
		//glVertex2f(x, (-1 * y));
		//cout << "x:" << xcenter + x << " y:" << (ycenter + y) << endl;
		glVertex2f(xcenter + x, ycenter - y);
		//glVertex2f((-1 * x), y);
		glVertex2f(xcenter - x, ycenter + y);
		//glVertex2f((-1 * x), (-1 * y));
		glVertex2f(xcenter - x, ycenter - y);
		//glColor3f(0.0f, 1.0f, 0.0f);
		//glVertex2f(y, x);
		glVertex2f(xcenter + y, ycenter + x);
		//glVertex2f(-y, x);
		glVertex2f(xcenter + y, ycenter - x);
		//glVertex2f(y, -x);
		glVertex2f(xcenter - y, ycenter + x);
		//glVertex2f(-y, -x);
		glVertex2f(xcenter - y, ycenter - x);
		glEnd();
	};
}


void midpointellipse(int xcenter, int ycenter, int radiusx, int radiusy) {

	int x = 0; //x (k)
	int y = radiusy;// this x,y is a point of the circle, 0 degrees
	float decision1 = (radiusy * radiusy) - ((radiusx * radiusx) * radiusy) + ((radiusx * radiusx) * (1 / 4));

	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_POINTS);
	glVertex2f(xcenter, ycenter + radiusy);
	glVertex2f(xcenter, ycenter - radiusy);
	glVertex2f(xcenter + radiusx, ycenter);
	glVertex2f(xcenter - radiusx, ycenter);
	glEnd();

	while ((2 * (radiusy * radiusy) * x) <= (2 * (radiusx * radiusx) * y)) {
		if (decision1 < 0) {
			x = x + 1;
			decision1 = decision1 + (2 * (radiusy * radiusy) * x) + (radiusy * radiusy);
		}
		else {
			x = x + 1;
			y = y - 1;// formula for y (k+1)
			decision1 = decision1 + (2 * (radiusy * radiusy) * x) - (2 * (radiusx * radiusx) * y) + (radiusy * radiusy);
		}

		glBegin(GL_POINTS);
		glVertex2f(xcenter + x, ycenter + y);
		glVertex2f(xcenter - x, ycenter + y);
		glVertex2f(xcenter + x, ycenter - y);
		glVertex2f(xcenter - x, ycenter - y);
		glEnd();
	};

	float decision2 = ((radiusy * radiusy) * ((x + (1 / 2)) * (x + (1 / 2)))) + ((radiusx * radiusx) * ((y - 1) * (y - 1))) - ((radiusx * radiusx) * (radiusy * radiusy));

	while (y >= 0) {
		if (decision2 > 0) {
			y = y - 1;
			decision2 = decision2 - (2 * (radiusx * radiusx) * y) + (radiusx * radiusx);//+ (2 * radiusx *radiusx);
		}
		else {
			x = x + 1;
			y = y - 1;// formula for y (k+1)
			decision2 = decision2 + (2 * (radiusy * radiusy) * x) - (2 * (radiusx * radiusx) * y) + (radiusx * radiusx); //+ (2 * radiusx * radiusx) + (2 * radiusy * radiusy);
		}

		glBegin(GL_POINTS);
		glVertex2f(xcenter + x, ycenter + y);
		glVertex2f(xcenter - x, ycenter + y);
		glVertex2f(xcenter + x, ycenter - y);
		glVertex2f(xcenter - x, ycenter - y);
		glEnd();
	};
}

//void drawline(int x1, int y1, int x2, int y2) {
void guptasproull_line(int x, int y, double distance, Color c) {
	double opacity = 1 - (distance * 2 / 3) * (distance * 2 / 3);
	//special case
	//glColor4f((c.r * opacity), (c.g * opacity), (c.b * opacity));
	glColor4f(c.r, c.g, c.b, opacity);
	//cout << opacity << endl;
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

//midpoint drawing algorithm first
void midpointline(int x1, int y1, int x2, int y2, Color c) {

	int dx = x2 - x1;
	int dy = y2 - y1;

	int dx2;
	int dy2;
	if (dx < 0) {
		dx2 = -1 * dx;
	}
	else {
		dx2 = dx;
	}

	if (dy < 0) {
		dy2 = -1 * dy;
	}
	else {
		dy2 = dy;
	}

	int x = x1;
	int y = y1;
	int u;
	int du;
	int dv;
	int xsign;
	int ysign;

	if (dx2 > dy2) {
		du = dx2;
		dv = dy2;
		u = x2;
		if (dx < 0) {
			xsign = -1;
		}
		else {
			xsign = 1;
		}

		if (dy < 0) {
			ysign = -1;
		}
		else {
			ysign = 1;
		}
	}
	else {
		du = dy2;
		dv = dx2;
		u = y2;
		if (dx < 0) {
			xsign = -1;
		}
		else {
			xsign = 1;
		}

		if (dy < 0) {
			ysign = -1;
		}
		else {
			ysign = 1;
		}
	}

	int endu = u + du;
	int d = (2 * dv) - du;
	int incs = 2 * dv;
	int incd = 2 * (dv - du);
	int twovdu = 0; //numerator for distance
	double inversedenom = 1.0 / (2.0 * sqrt((du * du) + (dv * dv))); //inverse denominator
	double inversed2du = 2.0 * (du * inversedenom); //constant

	if (dx2 > dy2) {
		do {
			guptasproull_line(x, y, (twovdu * inversedenom), c);
			guptasproull_line(x, (y + ysign), (inversed2du - (twovdu * inversedenom)), c);
			guptasproull_line(x, (y - ysign), (inversed2du + (twovdu * inversedenom)), c);

			if (d < 0) {
				twovdu = d + du;
				d += incs;

			}
			else {
				twovdu = d - du;
				d += incd;
				y += ysign;
			}
			u = u + 1;
			x = x + xsign;
		} while (u < endu);
	}
	else {
		do {
			guptasproull_line(x, y, twovdu * inversedenom, c);
			guptasproull_line(x, y + ysign, inversed2du - twovdu * inversedenom, c);
			guptasproull_line(x, y - ysign, inversed2du + twovdu * inversedenom, c);

			if (d < 0) {
				twovdu = d + du;
				d += incs;

			}
			else {
				twovdu = d - du;
				d += incd;
				x += xsign;
			}
			u = u + 1;
			y = y + ysign;
		} while (u < endu);
	}
}

//old midpoint
/*void midpointlinex(int x1, int y1, int x2, int y2) {
	glColor3f(0, 1, 0);

	int currentx = x1;
	int currenty = y1;

	int dx = x2 - x1; //151
	int dy = y2 - y1; //-81
	int d = (2 * dy) - dx; //-303
	int ince = 2 * dy;
	int incne = 2 * (dy - dx);
	//int dd = 2 * (dy - dx); //-232
	int dnum;
	int ddenom = 2 * sqrt((dx * dx) + (dy * dy));
	int pixd;
	glBegin(GL_POINTS);
		glVertex2f(currentx, currenty);
	glEnd();

	//if there's a downward slope
	if (y1 > y2) {
		while (currenty != y2 && currentx < x2) {
			//case one using e
			if (d < 0) {
				currentx = currentx + 1;
				//dnum = d + dx;
				d = d + ince;
				cout << "di:" << d << "cx:" << currentx << "cy:" << currenty << endl;
			}
			//case 2 using ne
			else if (d >= 0) {
				//else {
				d = d + incne;
				currentx = currentx + 1;
				currenty = currenty - 1;
				//dnum = d - dx;
				//d = d + dd;
			}

			//pixd = dnum / ddenom;
			glBegin(GL_POINTS);
			glVertex2f(currentx, currenty);
			glEnd();
		}
	}
	else {
		//while (currenty != y2 && currentx < x2) {
		while (currentx < x2) {
			//case one using e
			if (d < 0) {
				currentx = currentx + 1;
				//dnum = d + dx;
				d = d + ince;
				cout << "di:" << d << "cx:" << currentx << "cy:" << currenty << endl;
			}
			//case 2 using ne
			else if (d >= 0) {
				//else {
				d = d + incne;
				currentx = currentx + 1;
				currenty = currenty + 1;
				//dnum = d - dx;
				//d = d + dd;
			}

			//pixd = dnum / ddenom;
			glBegin(GL_POINTS);
			glVertex2f(currentx, currenty);
			glEnd();
		}
	}
} */

void flood(int x, int y, Color c, Color old) {
	// change[3] = {0.0, 0.0, 0.0};
	Color current;
	glReadPixels(x + 400, y + 300, 1, 1, GL_RGB, GL_FLOAT, &current);
	//cout << current.r << " " << current.g << " " << current.b << endl;
	//Color current = {change[0], change[1], change[2]};
	//cout << change[0] << " " << change[1] << " " << change[2] << endl;
	if (current.r == old.r && current.g == old.g && current.b == old.b) {
		//if (old.r != c.r && old.g == c.g && old.b == c.b) {
		glBegin(GL_POINTS);
		glColor3f(c.r, c.g, c.b);
		//glColor3f(0, 1, 0);
		glVertex2f(x, y);
		glEnd();
		glFlush();

		flood(x + 1, y, c, old);
		flood(x - 1, y, c, old);
		flood(x, y + 1, c, old);
		flood(x, y - 1, c, old);
	}
	return;
}

void display() {
	// clear color buffer
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPointSize(1.0);

	Color black = { 0.0, 0.0, 0.0 };
	Color white = { 1.0, 1.0, 1.0 };
	Color red = { 1.0, 0.0, 0.0 };

	midpointcircle(0, 0, 98);
	//midpointcircle(400, 300, 98);
	midpointcircle(120, 70, 40);
	//look up flood fiilling algorithm, choose point in curcle then flood
	midpointcircle(-120, 70, 40);

	Color lightblue = { 0.5, 0.7, 1.0 };

	midpointellipse(-42, 14, 28, 14);
	midpointellipse(42, 14, 28, 14);
	midpointellipse(0, -56, 24, 10);

	midpointline(69, -69, 220, -150, black);
	midpointline(-69, -69, -220, -150, black);
	//midpointline(-220, -150, -69, -69, black);
	midpointline(-220, -150, 220, -150, black);

	flood(120, 70, black, white);
	flood(-120, 70, black, white);
	flood(-42, 14, lightblue, white);
	flood(42, 14, lightblue, white);
	flood(0, -56, red, white);
	//glutSwapBuffers();
	glFlush();
}

int main(int argc, char** argv) {

	// create a window
	glutInit(&argc, argv);

	// use double buffer for animation
	// check OpenGL redbook 7e page 22 "Animation"
	//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// create a window
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Computer Graphics");

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);
	glOrtho(-400.0, 400.0, -300.0, 300.0, 1.0, -1.0);
	glutDisplayFunc(display);
	//glutIdleFunc(display);

	// event processing loop
	glutMainLoop();

	return 0;
}