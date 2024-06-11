#include <stdlib.h>
#include <GL/glut.h>

GLfloat ctrlpoints[15][15][3];

int lastX = 0, lastY = 0;
float rotationX = 0.0, rotationY = 0.0;

void initCtrlPoints()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            ctrlpoints[i][j][0] = i - 7.0;
            ctrlpoints[i][j][1] = j - 7.0;
            ctrlpoints[i][j][2] = 0.2 * (i - 7.0) * (i - 7.0) + 0.2 * (j - 7.0) * (j - 7.0);
        }
    }
}

void display(void)
{
    int i, j;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -15.0);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);

    glColor3f(1.0, 1.0, 1.0);
    for (j = 0; j < 14; j++)
    {
        glBegin(GL_LINE_STRIP);
        for (i = 0; i < 14; i++)
            glVertex3fv(ctrlpoints[i][j]);
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (i = 0; i < 14; i++)
            glVertex3fv(ctrlpoints[j][i]);
        glEnd();
    }

    glFlush();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    initCtrlPoints();
    glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        lastX = x;
        lastY = y;
    }
}

void mouseMotion(int x, int y)
{
    rotationX += (y - lastY);
    rotationY += (x - lastX);
    lastX = x;
    lastY = y;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}
