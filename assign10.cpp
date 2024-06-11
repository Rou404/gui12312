#include <GL/freeglut.h>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLfloat angle_sun = 0.0f; // Angle for the Sun's rotation
GLfloat angle_planets[5] = {0.0f}; // Angles for planet orbits
GLuint textures[6]; // Texture IDs

void loadTexture(const char* filename, GLuint textureID) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    } else {
        printf("Failed to load texture: %s\n", filename);
    }
}

void setLightProperties() {
    // Set light properties for the Sun
    GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); 
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    // Load textures
    glGenTextures(6, textures);
    loadTexture("sun.jpeg", textures[0]);
    loadTexture("mercury.jpeg", textures[1]);
    loadTexture("venus.jpeg", textures[2]);
    loadTexture("earth.jpg", textures[3]);
    loadTexture("mars.jpg", textures[4]);
    loadTexture("uranus.jpeg", textures[5]);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Place the camera
    gluLookAt(0.0, 15.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Set the light position in the scene
    setLightProperties();

    // Draw the Sun with rotation
    glPushMatrix();
    glRotatef(angle_sun, 0.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    // Set the material properties for the Sun
    GLfloat sun_ambient[] = { 0.8f, 0.8f, 0.0f, 1.0f };
    GLfloat sun_diffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    GLfloat sun_specular[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    GLfloat sun_emission[] = { 0.5f, 0.5f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission);

    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluSphere(quad, 3.0f, 20, 20);
    gluDeleteQuadric(quad);
    glPopMatrix();

    // Draw the planets with textures
    GLfloat planet_distances[5] = {5.0f, 8.0f, 11.0f, 14.0f, 17.0f};
    GLfloat planet_sizes[5] = {0.5f, 0.75f, 1.0f, 0.6f, 0.9f};
    GLfloat orbit_speeds[5] = {0.05f, 0.04f, 0.03f, 0.02f, 0.01f};

    for (int i = 0; i < 5; ++i) {
        glPushMatrix();
        glRotatef(angle_planets[i], 0.0f, 1.0f, 0.0f);
        glTranslatef(planet_distances[i], 0.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, textures[i + 1]);

        // Set the material properties for the planets
        GLfloat planet_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat planet_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        GLfloat planet_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat planet_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT, planet_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, planet_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, planet_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION, planet_emission);

        quad = gluNewQuadric();
        gluQuadricTexture(quad, GL_TRUE);
        gluSphere(quad, planet_sizes[i], 20, 20);
        gluDeleteQuadric(quad);
        glPopMatrix();

        // Update the angle for the next frame
        angle_planets[i] += orbit_speeds[i];
    }

    // Update the Sun's rotation angle
    angle_sun += 0.02f;

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
    glutCreateWindow("Textured Solar System");

    stbi_set_flip_vertically_on_load(true);

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}
