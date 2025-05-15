#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_SPIRALS 200
#define MAX_POINTS 1000
#define PI 3.14159265

typedef struct {
    float angle;
    float scale;
    float colorPhase;
    int direction;
    float r, g, b;
} Spiral;

int numSpirals = 50;
Spiral spirals[MAX_SPIRALS];

// Function prototypes - add this section before any functions
void randomizeSpiralColor(Spiral* s);
void initSpirals();
void drawSpiral(Spiral* s);
void display();
void update(int value);
void changeAllColors();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void renderBitmapString(float x, float y, void *font, const char *string);
void initGL();

void randomizeSpiralColor(Spiral* s) {
    s->r = (rand() % 100) / 100.0f;
    s->g = (rand() % 100) / 100.0f;
    s->b = (rand() % 100) / 100.0f;
}

void initSpirals() {
    for (int i = 0; i < MAX_SPIRALS; i++) {
        spirals[i].angle = (float)(i * 36);  // spread angles
        spirals[i].scale = 1.0f;
        spirals[i].colorPhase = i;
        spirals[i].direction = (i % 2 == 0) ? 1 : -1;
        randomizeSpiralColor(&spirals[i]);
    }
}

void drawSpiral(Spiral* s) {
    glPushMatrix();
    glRotatef(s->angle, 0.0f, 0.0f, 1.0f);
    glScalef(s->scale, s->scale, 1.0f);
    glColor3f(s->r, s->g, s->b);

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < MAX_POINTS; i++) {
        float t = i * 0.05f;
        float x = t * cos(t);
        float y = t * sin(t);
        glVertex2f(x / 15.0f, y / 15.0f);
    }
    glEnd();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (numSpirals > 0) {
        for (int i = 0; i < numSpirals; i++) {
            drawSpiral(&spirals[i]);
        }
    }
    // When numSpirals == 0, screen remains blank as cleared above
    char buffer[50];
    sprintf(buffer, "Spirals: %d", numSpirals);
    glColor3f(1, 1, 1);  // White text
    renderBitmapString(-1.1f, -1.15f, GLUT_BITMAP_HELVETICA_18, buffer);

    glutSwapBuffers();
}

void update(int value) {
    for (int i = 0; i < numSpirals; i++) {
        Spiral* s = &spirals[i];
        s->angle += s->direction * 0.8f;
        s->scale += 0.005f * s->direction;
        if (s->scale > 1.5f || s->scale < 0.5f)
            s->direction *= -1;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void changeAllColors() {
    for (int i = 0; i < numSpirals; i++) {
        randomizeSpiralColor(&spirals[i]);
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:  // ESC
            exit(0);
        case '+':
            if (numSpirals < MAX_SPIRALS) numSpirals++;
            break;
        case '-':
            if (numSpirals > 0) numSpirals--;
            // Now numSpirals can be zero, screen will clear in display()
            break;
        case 'r':
        case 'R':
            initSpirals();
            break;
        case 'c':
        case 'C':
            changeAllColors();
            break;
        default:
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            for (int i = 0; i < numSpirals; i++)
                spirals[i].direction *= -1;
        } else if (button == GLUT_RIGHT_BUTTON) {
            changeAllColors();
        }
    }
}

void renderBitmapString(float x, float y, void *font, const char *string) {
    glRasterPos2f(x, y);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void initGL() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.2, 1.2, -1.2, 1.2);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Interactive Rotating Spirals");

    initGL();
    initSpirals();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}