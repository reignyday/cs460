#include"display.h"
#include"util.h"

//#define NDEBUG  // used to disabled all assert.
GLsizei width, height;

//double m_xtheta = 0;
//double m_ytheta = 0;
//double m_ztheta = 0;
//`double m_slide = 40;

GLUquadricObj* quadric = gluNewQuadric();
float mercRotation = 0.0;
float earthRotation = 0.0;
float moonRotation = 0.0;

float moonx = 0.0;
float moonz = 0.0;
float moonangle = 0.0;

float leverangle = 0.0;

struct point {
    float x;
    float y;
    float z;
};

//vector<float> n;// = { 0, 0, 40 };
//needed for v1 functions
point n = { 0, 0, -1 };
point u = { 1, 0, 0 };
point up = { 0, 1, 0 }; //up x, y, z  vector, v vector
point eye = { 0, 0, 40 };//eye 
point center = { 0, 0, 0 };

void setup()
{
    glClearColor(0, 0, 0, 1.0); // *should* display black background
}

void timer(int) {
    glutSwapBuffers();
    glutPostRedisplay();
    //glutTimerFunc(1000 / 60, timer, 0);
    glutTimerFunc(1000 / 10, timer, 0);
    //glRotatef(earthRotation, 0.0f, 1.0f, 0.0f);
    //glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    //gluSphere(earth, 35.0, 72, 72);
    //glutWireSphere(.5, 30, 30);

    mercRotation += 10.0f;
    earthRotation += 10.0f;
    moonRotation += 20.0f;

    if (mercRotation > 360.0f){
        mercRotation = 0.0f;
    }
    if (earthRotation > 360.0f){
        earthRotation = 0.0f;
    }
    if (moonRotation > 360.0f){
        moonRotation = 0.0f;
    }

    moonx = (9.0 * sin(moonangle));
    moonz = (9.0 * cos(moonangle));
    moonangle = moonangle + 0.05;
    if (moonangle > 360) {
        moonangle = 0.0;
    }
}

void DrawLever() {
    //DrawGround();
    glPushMatrix();
    DrawGround();
    glPopMatrix();
   //glPushMatrix();
   /* glColor3f(0, 0, 1);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();*/

    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 20);
    glVertex3f(0.0, 0.0, -20);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0, 0, 1);
    glVertex3f(20, 0.0, 0);
    glVertex3f(-20, 0.0, 0);
    glEnd(); 

    //glPointSize(1);

    //b2, middle sphere, origin
    glPushMatrix();//'save current position'
    //glColor3f(0, 0, 1);
    glutSolidSphere(1.5, 30, 30);
    //glPopMatrix();//'load the last position saved'

    //s1
    //glPushMatrix();
    glColor3f(1, 0, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(quadric, 1, 1, 20, 20, 20);
    glRotatef(-90, 1, 0, 0);
    //glPopMatrix();

    //s2 s3
    //glPushMatrix();
    glColor3f(1, 0, 0);
    //glRotatef(180, 0, 0, 1);
    //rotate around xz plane or y axis
    glRotatef(leverangle, 0, 1, 0);
    glTranslatef(0, 0, -10);
    gluCylinder(quadric, 1, 1, 20, 20, 20);
   // glPopMatrix();

    //b3   
    //glPushMatrix();
    glColor3f(0, 0, 1);
    //glRotatef(leverangle, 0, 1, 0);
    //glTranslatef(0, 0, -10);
    glutSolidSphere(1.5, 30, 30);
    glTranslatef(0, 0, 10);
    //glPopMatrix();

    //b1
    //glPushMatrix();
    glColor3f(1, 0, 1);
    //glRotatef(leverangle, 0, 1, 0);
    glTranslatef(0, 0, 10);
    glutSolidSphere(1.5, 30, 30);
    //glTranslatef(0, 0, -10);
    //glPopMatrix();

    //s4
    //rotate around z axis/b1
    glPushMatrix();
    glColor3f(1, 0, 0);
    glRotatef(leverangle, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    gluCylinder(quadric, 0, 1.5, 10, 20, 20);
    //b4
    glTranslatef(0, 0, 10);
    glutSolidSphere(3, 30, 30);
    //glRotatef(-90, 1, 0, 0);
    //glTranslatef(0, 0, -10);
    glPopMatrix();
    
    //s5
    //glPushMatrix();
    glColor3f(0, 1, 0);
    glRotatef((leverangle * -1), 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, -10, 0);
    glTranslatef(0, -10, 0);
    //glTranslatef(0, 0, 10);
    gluCylinder(quadric, 0, 1.5, 10, 20, 20);
    //b5
    glTranslatef(0, 0, 10);
    glutSolidSphere(3, 30, 30);
    //glRotatef(90, 1, 0, 0);
    glPopMatrix();

    //glPushMatrix();
    /*glColor3f(0, 0, 1);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();

    //s3
    glPushMatrix();
    glColor3f(1, 0, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(quadric, 1, 1, 10, 20, 20);
    //glPopMatrix();

    //b1    
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(0, 0, -10);
    glutSolidSphere(1.5, 30, 30);

    //b4
    //glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(0, 10, 0);
    glutSolidSphere(3, 30, 30);
    glPopMatrix();

    //b3
    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslatef(0, 0, 10);
    glutSolidSphere(1.5, 30, 30);
    //glPopMatrix();

    //b5
    //glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslatef(0, 10, 0);
    glutSolidSphere(3, 30, 30);
    glPopMatrix();*/
    //DrawGround();
}


void reshape(int w, int h) {
    width = w;
    height = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glColor3f(1.0f, 0.0f, 0.0f);

    //V2
    //glOrtho(0, width, height, 0, -1, 1);
    //glViewport(width / 2.0, 0, width / 2.0, height / 2.0);
    glViewport(0, 0, width / 2, height / 2);
    projection(width / 2.0, height / 2.0, 1);
    gluLookAt(0.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

    //gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //glLoadIdentity();
    //gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //DrawGround();
    DrawLever();
    //glutWireTeapot(1);

    //V3
    //glPopMatrix();
    glViewport(0, height / 2, width / 2, height / 2);
    projection(width / 2.0, height / 2.0, 1);
    // gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

     //gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
     //glLoadIdentity();
    gluLookAt(40.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //glPushMatrix();
    //DrawGround();
    //glPopMatrix();
    DrawLever();
    //DrawGround();
    //glPopMatrix();

    //projection(width / 2.0, height / 2.0, 1);
    //gluLookAt(0.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    //glLoadIdentity();
    //gluLookAt(0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    //DrawGround();

    //RenderGLScene(7, 3, 5);
    //glColor3f(0.8, 0.5, 0.2);
    //DrawGround();
    //glutWireSphere(.75, 30, 30);

    //V4
    //glViewport(0, 0, width / 2, height / 2);
    //projection(width / 2.0, height / 2.0, 1);
    //gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

    //gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //glLoadIdentity();
    //gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glViewport(width / 2, height / 2, width / 2, height / 2);
    projection(width / 2.0, height / 2.0, 1);
    gluLookAt(0.0, 0.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //DrawGround();
    DrawLever();

    //V1
    glViewport(width / 2, 0, width / 2, height / 2);
    projection(width / 2.0, height / 2.0, 1);
    //gluLookAt(0, 0, 40, 0.0, 0.0, 0, 0.0, 1.0, 0.0);
    gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
    //glLoadIdentity();
    //Planet e = new Planet(.5, 5, )
    //Planet ear(2.0, 16, 0, 2.98, 23.44, 0);	
    //gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //glPushMatrix();
    //glRotatef(m_xtheta, 1, 0, 0);
    //glRotatef(m_ytheta, 0, 1, 0);
    //glRotatef(m_ztheta, 0, 0, 1);

    RenderGLScene();
    //glFlush();
    glutSwapBuffers();
}

void DrawGround() {
    //glPushMatrix();
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_LINES);

    for (float i = -1; i <= 1; ) {
        glVertex3f(i * 100.f, -10.f, -100.f);
        glVertex3f(i * 100.f, -10.f, 100.f);
        i += 0.1;
    }
    for (float j = -1; j <= 1; ) {
        glVertex3f(-100.f, -10.f, j * 100.f);
        glVertex3f(100.f, -10.f, j * 100.f);
        j += 0.1;
    }
    glEnd();
    //glPopMatrix();
}

void projection(int width, int height, int perspectiveORortho) {
    float ratio = (float)width / height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (perspectiveORortho)
        gluPerspective(60, ratio, 1, 256);
    else
        glOrtho(-ratio, ratio, -ratio, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderGLScene(void) {//int radius, int r, int r2) {
    //void RenderGLScene(int radius, int height) {
        // draw a cylinder or a sphere, 
        // you will draw more objects in this function
        //GLUquadricObj* quadObj = gluNewQuadric ();
        //gluQuadricDrawStyle (quadObj, GLU_LINE);

        //draw a cone shape cylinder
        //gluCylinder(quadObj, base_radius, top_radius, height, 20, 10); 
   /* glColor3f(0.8, 0.5, 0.2);
    glutWireSphere(radius, 30, 30);

    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-14.0, 0.0, 0.0);
    glutWireSphere(r, 30, 30);

    glTranslatef(14.0, 0.0, 0.0);

    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(18.0, 0.0, 0.0);
    glutWireSphere(r2, 30, 30);

    glTranslatef(-18.0, 0.0, 0.0);

    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(18.0, 0.0, 0.0);
    /*glTranslatef(moonposx, 0.0, moonposz);
    glutWireSphere(1.0, 30, 30);

    glTranslatef(-18.0, 0.0, 0.0);
    glLoadIdentity();

    //draw ground lines for reference
    //DrawGround();*/
    //gluDeleteQuadric(quadObj);*/

    glPushMatrix();
    DrawGround();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8, 0.5, 0.2);
    glRotatef(90, 1.0f, 0.0f, 0.0f); //turns object upright
    glutWireSphere(10, 30, 30);//sun
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-14, 0.0, 4.0);
    glRotatef(90, 1.0f, 0.0f, 0.0f); //turns object upright
    glRotatef(mercRotation, 0.0f, 0.0f, 1.0f); //to make earth spin
    glutWireSphere(4, 30, 30); //mercury
    glTranslatef(14, 0.0, -4.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(20, 0.0, 5.0);
    //glutWireSphere(.5, 30, 30);
    //glRotatef(earthRotation, 0.0f, 1.0f, 0.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f); //turns object upright
    glRotatef(earthRotation, 0.0f, 0.0f, 1.0f); //to make earth spin
    //glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    //gluSphere(earth, 35.0, 72, 72);
    glutWireSphere(6, 30, 30); //earth
    glTranslatef(-20, 0.0, -5.0);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    //glRotatef(90, 1.0f, 0.0f, 0.0f);
    glTranslatef(20, 0.0, 5.0);
    //glTranslatef(9, 0.0, 0.0);    
    glTranslatef(moonx, 0.0, moonz);
    //glPushMatrix();
    glRotatef(90, 1.0f, 0.0f, 0.0f); //turns object upright
    glRotatef(moonRotation, 0.0f, 0.0f, 1.0f); //to make moon spin
    //glRotatef(moonx, 1.0, 0.0, 0.0);
    glutWireSphere(1.5, 25, 25); //moon

    glPopMatrix();
    //glFlush();
}

//a-angle, r, radians
//roll, replicate circle around z axis
void RollUp(float a, float r) {
    //shouldnt need z
    u.x = u.x * cos(a * r) + up.x * sin(a * r);
    up.x = up.x * cos(a * r) - u.x * sin(a * r);
    u.y = u.y * cos(a * r) + up.y * sin(a * r);
    up.y = up.y * cos(a * r) - u.y * sin(a * r);
    u.z = u.z * cos(a * r) + up.z * sin(a * r);
    up.z = up.z * cos(a * r) - u.z * sin(a * r);
}
void RollDown(float a, float r) {
    //shouldnt need z
    u.x = u.x * cos(a * r) - up.x * sin(a * r);
    up.x = u.x * sin(a * r) + up.x * cos(a * r);
    u.y = u.y * cos(a * r) - up.y * sin(a * r);
    up.y = u.y * sin(a * r) + up.y * cos(a * r);
    u.z = u.z * cos(a * r) - up.z * sin(a * r);
    up.z = u.z * sin(a * r) + up.z * cos(a * r);
    
}
void PitchUp(float a, float r) {
    up.x = up.x * cos(a * r) - n.x * sin(a * r);
    n.x = up.x * sin(a * r) + n.x * cos(a * r);
    center.x = eye.x + n.x;
    up.y = up.y * cos(a * r) - n.y * sin(a * r);
    n.y = up.y * sin(a * r) + n.y * cos(a * r);
    center.y = eye.y + n.y;
    up.z = up.z * cos(a * r) - n.z * sin(a * r);
    n.z = up.z * sin(a * r) + n.z * cos(a * r);
    center.z = eye.z + n.z;
}
void PitchDown(float a, float r) {
    up.x = up.x * cos(a * r) + n.x * sin(a * r);
    n.x = n.x * cos(a * r) - up.x * sin(a * r);
    center.x = eye.x + n.x;
    up.y = up.y * cos(a * r) + n.y * sin(a * r);
    n.y = n.y * cos(a * r) - up.y * sin(a * r);
    center.y = eye.y + n.y;
    up.z = up.z * cos(a * r) + n.z * sin(a * r);
    n.z = n.z * cos(a * r) - up.z * sin(a * r);
    center.z = eye.z + n.z;
}
void YawUp(float a, float r) {
    //shouldnt need y 
    u.x = u.x * cos(a * r) + n.x * sin(a * r);
    n.x = n.x * cos(a * r) - u.x * sin(a * r);
    center.x = eye.x + n.x;
    u.y = u.y * cos(a * r) + n.y * sin(a * r);
    n.y = n.y * cos(a * r) - u.y * sin(a * r);
    center.y = eye.y + n.y;
    u.z = u.z * cos(a * r) + n.z * sin(a * r);
    n.z = n.z * cos(a * r) - u.z * sin(a * r);
    center.z = eye.z + n.z;
}
void YawDown(float a, float r) {
    //shouldnt need y 
    u.x = u.x * cos(a * r) - n.x * sin(a * r);
    n.x = u.x * sin(a * r) + n.x * cos(a * r);
    center.x = eye.x + n.x;
    u.y = u.y * cos(a * r) - n.y * sin(a * r);
    n.y = u.y * sin(a * r) + n.y * cos(a * r);
    center.y = eye.y + n.y;
    u.z = u.z * cos(a * r) - n.z * sin(a * r);
    n.z = u.z * sin(a * r) + n.z * cos(a * r);
    center.z = eye.z + n.z;
}
void SlideUp(float a) {
    //think only z is needed, but putting all just in case
    eye.x += n.x;
    eye.y += n.y;
    eye.z += n.z;
}
void SlideDown(float a) {
    //sliding along z axis
    eye.x -= n.x;
    eye.y -= n.y;
    eye.z -= n.z;
}

void RotateLever(float a) {
    leverangle += a;
}