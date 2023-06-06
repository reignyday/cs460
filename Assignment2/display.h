#define PI 3.1415926


void setup();
void reshape(int w, int h);
void display();
void projection(int width, int height, int perspectiveORortho);
void RenderGLScene(void);
void DrawGround();
void timer(int);

void DrawLever();

// setting the rotation.
void RollUp(float a, float r);
void RollDown(float a, float r);
void PitchUp(float a, float r);
void PitchDown(float a, float r);
void YawUp(float a, float r);
void YawDown(float a, float r);
void SlideUp(float a);
void SlideDown(float a);
void RotateLever(float a);
