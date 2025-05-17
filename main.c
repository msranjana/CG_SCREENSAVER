/*#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>  // ✅ Required for bool, true, false

int state = 0;            // 0 = Red, 1 = Yellow, 2 = Green
bool autoMode = true;     // Auto timer mode by default

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw traffic light pole
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(0.48f, 0.0f);
        glVertex2f(0.52f, 0.0f);
        glVertex2f(0.52f, 0.2f);
        glVertex2f(0.48f, 0.2f);
    glEnd();

    // Draw traffic light box
    glColor3f(0.2f, 0.2f, 0.2f);  // Dark gray
    glBegin(GL_POLYGON);
        glVertex2f(0.4f, 0.2f);
        glVertex2f(0.6f, 0.2f);
        glVertex2f(0.6f, 0.8f);
        glVertex2f(0.4f, 0.8f);
    glEnd();

    // Red light
    glColor3f(state == 0 ? 1.0f : 0.3f, 0.0f, 0.0f);
    drawCircle(0.5f, 0.7f, 0.06f);

    // Yellow light
    glColor3f(state == 1 ? 1.0f : 0.3f, state == 1 ? 1.0f : 0.3f, 0.0f);
    drawCircle(0.5f, 0.5f, 0.06f);

    // Green light
    glColor3f(0.0f, state == 2 ? 1.0f : 0.3f, 0.0f);
    drawCircle(0.5f, 0.3f, 0.06f);

    glFlush();
}

void timer(int value) {
    if (autoMode) {
        state = (state + 1) % 3;
        glutPostRedisplay();
        glutTimerFunc(2000, timer, 0);  // Cycle every 2 seconds
    }
}

// Keyboard event handler
void keyboard(unsigned char key, int x, int y) {
    autoMode = false;  // Stop auto mode on manual input

    switch (key) {
        case 'r':
        case 'R':
            state = 0;
            printf("Manual: Red Light\n");
            break;
        case 'y':
        case 'Y':
            state = 1;
            printf("Manual: Yellow Light\n");
            break;
        case 'g':
        case 'G':
            state = 2;
            printf("Manual: Green Light\n");
            break;
        case 'a':
        case 'A':
            autoMode = true;
            printf("Auto Mode ON\n");
            glutTimerFunc(0, timer, 0);  // Restart timer
            break;
    }

    glutPostRedisplay();
}

// Mouse event handler
void mouse(int button, int stateMouse, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && stateMouse == GLUT_DOWN) {
        autoMode = false;  // Stop automatic mode
        state = (state + 1) % 3;  // Next light
        printf("Mouse Click at (%d, %d). Switched to state %d\n", x, y, state);
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);  // Light gray background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);  // 2D coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(400, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Traffic Light Simulation with Keyboard & Mouse");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(0, timer, 0);  // Start auto mode
    glutMainLoop();
    return 0;
}








*/




















#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_SPIRALS 200
#define MAX_POINTS 1000
#define PI 3.14159265
#define NUM_SPIRAL_TYPES 5

typedef struct {
    float angle;
    float scale;
    int direction;
    float r, g, b;
} Spiral;

int numSpirals = 50;
Spiral spirals[MAX_SPIRALS];
int currentSpiralType = 0;

// Function prototypes
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
        spirals[i].angle = (float)(i * 36);  
        spirals[i].scale = 1.0f;
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
    switch (currentSpiralType) {
        case 0: // Original spiral
            for (int i = 0; i < MAX_POINTS; i++) {
                float t = i * 0.05f;
                float x = t * cos(t);
                float y = t * sin(t);
                glVertex2f(x / 15.0f, y / 15.0f);
            }
            break;
        case 1: // Flower spiral
            for (int i = 0; i < MAX_POINTS; i++) {
                float t = i * 0.05f;
                float r = t * 0.05f;
                float x = r * cos(t) * (1 + 0.5f * sin(5*t));
                float y = r * sin(t) * (1 + 0.5f * sin(5*t));
                glVertex2f(x, y);
            }
            break;
        case 2: // Pulsating spiral using sine waves
            for (int i = 0; i < MAX_POINTS; i++) {
                float t = i * 0.05f;
                float r = t * (0.04f + 0.02f * fabs(sin(8 * t)));
                float x = r * cos(t);
                float y = r * sin(t);
                glVertex2f(x, y);
    }
            break;

        case 3: // Spiral Star (sharp petal-like shape)
            for (int i = 0; i < MAX_POINTS; i++) {
                float t = i * 0.05f;
                float r = t * 0.03f * fabs(sin(6 * t));
                float x = r * cos(t);
                float y = r * sin(t);
                glVertex2f(x, y);
            }
            break;

        case 4: // Rose curve spiral (r = sin(kθ))
            for (int i = 0; i < MAX_POINTS; i++) {
                float t = i * 0.05f;
                float k = 5.0f;  // number of petals
                float r = 0.4f * sin(k * t);
                float x = r * cos(t);
                float y = r * sin(t);
                glVertex2f(x, y);
            }
            break;
    }
    glEnd();
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (numSpirals >=0) {
        for (int i = 0; i < numSpirals; i++) {
            drawSpiral(&spirals[i]);
        }
    }
    // When numSpirals == 0, screen remains blank 
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
            break;
        case 'r':
        case 'R':
            initSpirals();
            break;
        case 'c':
        case 'C':
            changeAllColors();
            break;
        case 's':
        case 'S':
            currentSpiralType = (currentSpiralType + 1) % NUM_SPIRAL_TYPES;
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