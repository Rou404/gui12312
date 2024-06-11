#include <GL/freeglut.h>
#include <cmath>

GLfloat angle1 = 0.0f; // Angle for first light orbit
GLfloat angle2 = 0.0f; // Angle for second light orbit

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);

    // Set light properties
    GLfloat light0_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light1_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light0_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light1_diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Place the camera
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Rotate lights around objects
    GLfloat light0_radius = 5.0f;
    GLfloat light1_radius = 5.0f;
    GLfloat light_speed = 0.01f;
    GLfloat light0_x = light0_radius * cos(angle1);
    GLfloat light0_y = light0_radius * sin(angle1);
    GLfloat light1_x = light1_radius * cos(angle2);
    GLfloat light1_y = light1_radius * sin(angle2);
    GLfloat light0_position[] = { light0_x, 0.0f, light0_y, 1.0f };
    GLfloat light1_position[] = { light1_x, 0.0f, light1_y, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    angle1 += light_speed;
    angle2 -= light_speed;

    // Draw base platform
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, 0.0f, -5.0f);
    glVertex3f(-5.0f, 0.0f, 5.0f);
    glVertex3f(5.0f, 0.0f, 5.0f);
    glVertex3f(5.0f, 0.0f, -5.0f);
    glEnd();

    // Draw small balls to indicate light positions
    glPushMatrix();
    glTranslatef(light0_x, 0.1f, light0_y);
    glColor3f(1.0f, 1.0f, 1.0f); // White ball for light0
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(light1_x, 0.1f, light1_y);
    glColor3f(1.0f, 1.0f, 1.0f); // White ball for light1
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();
    
    // Draw objects
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(1.0, 20, 20); // Red sphere
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(2.0f, 1.0f, 0.0f);
    glutSolidCube(1.0); // Green cube
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 1.0f, 2.0f);
    glutSolidCone(1.0, 2.0, 20, 20); // Blue cone
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(-2.0f, 1.0f, 0.0f);
    glutSolidTorus(0.3, 1.0, 20, 20); // Yellow torus
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Multiple Lighting Sources");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}
