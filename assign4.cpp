#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define STEP 0.1
#define TORSO_HEIGHT 7.0
#define TORSO_WEIGHT 4.0
#define UPPER_ARM_HEIGHT 3.5
#define UPPER_ARM_WEIGHT 1.0
#define LOWER_ARM_HEIGHT 2.5
#define LOWER_ARM_WEIGHT 0.8
#define UPPER_LEG_HEIGHT 4.5
#define UPPER_LEG_WEIGHT 1.2
#define LOWER_LEG_HEIGHT 3.5
#define LOWER_LEG_WEIGHT 1.5
#define ELBOW_WEIGHT 0.7
#define KNEE_WEIGHT 0.9
#define HAND_WEIGHT 0.8
#define FOOT_WEIGHT 0.9
#define SHOULDER_WEIGHT 1.0
#define HEAD_HEIGHT 2.0
#define HEAD_WEIGHT 1.5
#define NECK_HEIGHT 1.2
#define NECK_WEIGHT 0.6
#define RAISE_HANDS 0
#define RAISE_LEG 1
#define RESET 2
#define NULL 0

int option = -1;
int animation = -3;
int done = 0;
double rotate = 0;
double horizontal = 0;

void head();
void torso();
void left_upper_arm();
void right_upper_arm();
void left_upper_leg();
void right_upper_leg();

typedef float point[3];

typedef struct treenode
{
	GLfloat m[16];
	void (*f)();
	struct treenode *sibling;
	struct treenode *child;
} treenode;

typedef treenode *t_ptr;

static GLfloat degree_list[11] = {0.0, 0.0, 0.0, 180.0, 0.0, 180.0, 0.0,
								  180.0, 0.0, 180.0, 0.0};

static GLint angle = 2;

GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul;
GLUquadricObj *relb, *lelb, *rknee, *lknee, *nk, *lhand, *rhand, *lfoot, *rfoot, *rsh, *lsh;

double size = 1.0;

treenode torso_node, head_node, lua_node, rua_node, lll_node, rll_node,
	lla_node, rla_node, rul_node, lul_node,
	relb_node, lelb_node, rknee_node, lknee_node, nk_node, lhand_node, rhand_node, lfoot_node, rfoot_node,
	rsh_node, lsh_node;

void traverse(treenode *root)
{
	if (root == NULL)
		return;
	glPushMatrix();
	glMultMatrixf(root->m);
	root->f();
	if (root->child != NULL)
		traverse(root->child);
	glPopMatrix();
	if (root->sibling != NULL)
		traverse(root->sibling);
}

void torso()
{
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, TORSO_HEIGHT - 2.9, 0.0);
	glScalef(TORSO_WEIGHT / 0.6 + 0.5, TORSO_HEIGHT, TORSO_WEIGHT / 0.6);
	glutSolidCube(1.0);
	glPopMatrix();
	glColor3f(0.0, 0.0, 0.0);
}

void head()
{
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, HEAD_HEIGHT + 1, 0.0);
	glScalef(HEAD_WEIGHT + 3, HEAD_HEIGHT + 3, HEAD_WEIGHT + 2);
	glutSolidCube(1.0);
	glPopMatrix();
	glColor3f(0.0, 0.0, 0.0);
}

void neck()
{
	glColor3f(0.0, 0.5, 0.0);
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(nk, NECK_WEIGHT, NECK_WEIGHT, NECK_HEIGHT, 10, 10);
	glPopMatrix();
}

void rightShoulder()
{
	glColor3f(0.5, 0.0, 0.0);
	glPushMatrix();
	gluSphere(relb, SHOULDER_WEIGHT, 10, 10);
	glPopMatrix();
	glColor3f(0.0, 0.0, 0.0);
}

void leftShoulder()
{
	glColor3f(0.5, 0.0, 0.0);
	glPushMatrix();
	gluSphere(lelb, SHOULDER_WEIGHT, 10, 10);
	glPopMatrix();
	glColor3f(0.0, 0.0, 0.0);
}

void rightElbow()
{
	glColor3f(0.5, 0.5, 0.0);
	glPushMatrix();
	gluSphere(relb, ELBOW_WEIGHT, 10, 10);
	glPopMatrix();
	glColor3f(0.0, 0.0, 0.0);
}

void leftElbow()
{
	glColor3f(0.5, 0.5, 0.0);
	glPushMatrix();
	gluSphere(lelb, ELBOW_WEIGHT, 10, 10);
	glPopMatrix();
	glColor3f(0.0, 0.0, 0.0);
}

void rightKnee()
{
	glPushMatrix();
	gluSphere(rknee, KNEE_WEIGHT, 10, 10);
	glPopMatrix();
}

void leftKnee()
{
	glPushMatrix();
	gluSphere(lknee, KNEE_WEIGHT, 10, 10);
	glPopMatrix();
}

void leftFoot()
{
	glPushMatrix();
	gluSphere(lknee, FOOT_WEIGHT, 10, 10);
	glPopMatrix();
}

void rightFoot()
{
	glPushMatrix();
	gluSphere(lknee, FOOT_WEIGHT, 10, 10);
	glPopMatrix();
}

void rightHand()
{
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	gluSphere(lknee, HAND_WEIGHT, 10, 10);
	glPopMatrix();
	glColor3f(0.0, 0.0, 0.0);
}

void leftHand()
{
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	gluSphere(lknee, HAND_WEIGHT, 10, 10);
	glPopMatrix();
	glColor3f(0.0, 0.0, 0.0);
}

void left_upper_arm()
{
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, UPPER_ARM_HEIGHT - 1.5, 0.0);
	glScalef(UPPER_ARM_WEIGHT + 1, UPPER_ARM_HEIGHT - 0.5, UPPER_ARM_WEIGHT + 1);
	glutSolidCube(1.0);
	glPopMatrix();
	glColor3f(0.0, 0.0, 0.0);
}

void left_lower_arm()
{
	glColor3f(0.0, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(0.0, LOWER_ARM_HEIGHT - 1.5, 0.0);
	glScalef(LOWER_ARM_WEIGHT + 0.8, LOWER_ARM_HEIGHT - 0.5, LOWER_ARM_WEIGHT + 1);
	glutSolidCube(1.0);
	glPopMatrix();
}

void right_upper_arm()
{
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, UPPER_ARM_HEIGHT - 1.5, 0.0);
	glScalef(UPPER_ARM_WEIGHT + 1, UPPER_ARM_HEIGHT - 0.5, UPPER_ARM_WEIGHT + 1);
	glutSolidCube(1.0);
	glPopMatrix();
	glColor3f(0.0, 0.0, 0.0);
}

void right_lower_arm()
{
	glColor3f(0.0, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(0.0, LOWER_ARM_HEIGHT - 1.5, 0.0);
	glScalef(LOWER_ARM_WEIGHT + 0.8, LOWER_ARM_HEIGHT - 0.5, LOWER_ARM_WEIGHT + 1);
	glutSolidCube(1.0);
	glPopMatrix();
}

void left_upper_leg()
{
	glPushMatrix();
	glTranslatef(0.0, UPPER_LEG_HEIGHT - 2, 0.0);
	glScalef(UPPER_LEG_WEIGHT + 1, UPPER_LEG_HEIGHT - 0.5, UPPER_LEG_WEIGHT + 1);
	glutSolidCube(1.0);
	glPopMatrix();
}

void left_lower_leg()
{
	glPushMatrix();
	glTranslatef(0.0, LOWER_LEG_HEIGHT - 2, 0.0);
	glScalef(LOWER_LEG_WEIGHT + 0.8, LOWER_LEG_HEIGHT - 0.5, LOWER_LEG_WEIGHT + 1);
	glutSolidCube(1.0);
	glPopMatrix();
}

void right_upper_leg()
{
	glPushMatrix();
	glTranslatef(0.0, UPPER_LEG_HEIGHT - 2, 0.0);
	glScalef(UPPER_LEG_WEIGHT + 1, UPPER_LEG_HEIGHT - 0.5, UPPER_LEG_WEIGHT + 1);
	glutSolidCube(1.0);
	glPopMatrix();
}

void right_lower_leg()
{
	glPushMatrix();
	glTranslatef(0.0, LOWER_LEG_HEIGHT - 2, 0.0);
	glScalef(LOWER_LEG_WEIGHT + 0.8, LOWER_LEG_HEIGHT - 0.5, LOWER_LEG_WEIGHT + 1);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawText(const char *text, int x, int y)
{
	glPushMatrix();
	glRasterPos2i(x, y);
	while (*text != '\0')
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
		++text;
	}
	glPopMatrix();
}

void displayLegend()
{
	glColor3f(0.0, 0.0, 0.0);
	drawText("Legend:", -10, 10);
	drawText("1: Raise Hands", -10, 8);
	drawText("2: Raise Leg", -10, 6);
}

void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15, 15, -15, 15, -15, 15);
	glRotatef(rotate, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0.6, 0.6, 0.6);
	displayLegend();
	traverse(&torso_node);
	glutSwapBuffers();
}

void animate(int option)
{
	switch (option)
	{
	case 0:
		if (degree_list[5] < 180.0)
		{
			degree_list[5] += STEP;
			degree_list[3] += STEP;
			degree_list[1] -= 0.2 * STEP;
		}
		else
			animation = option;

		glPushMatrix();

		glLoadIdentity();
		glTranslatef(0, 0, 0.0);
		glRotatef(degree_list[5], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);

		glLoadIdentity();
		glTranslatef(0, 0, 0.0);
		glRotatef(degree_list[3], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);

		glLoadIdentity();
		glTranslatef(0.0, TORSO_HEIGHT - 0.25 * NECK_HEIGHT, 0.0);
		glRotatef(degree_list[1], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, nk_node.m);

		glPopMatrix();
		break;
	case 1:
		if (degree_list[9] < 180.0)
		{
			degree_list[9] += STEP;
			degree_list[10] -= STEP;
		}
		else
			animation = option;

		glPushMatrix();

		glLoadIdentity();
		glTranslatef(TORSO_WEIGHT / 2, 0.1 * UPPER_LEG_HEIGHT, 0.0);
		glRotatef(degree_list[9], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rul_node.m);

		glLoadIdentity();
		glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rknee_node.m);

		glLoadIdentity();
		glTranslatef(0.0, KNEE_WEIGHT / 2, 0.0);
		glRotatef(degree_list[10], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rll_node.m);

		glPopMatrix();
		break;
	default:
		animation = option;
	}
}

void idle()
{
	switch (option)
	{
	case 0:
		if (animation != option)
			animate(option);
		else if (!done)
		{
			if (degree_list[5] > 30.0)
			{
				degree_list[5] -= STEP;
				degree_list[3] -= STEP;
				degree_list[1] += 0.2 * STEP;
			}
			else
				done = 1;

			glPushMatrix();

			glLoadIdentity();
			glTranslatef(0, 0, 0.0);
			glRotatef(degree_list[5], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);

			glLoadIdentity();
			glTranslatef(0, 0, 0.0);
			glRotatef(degree_list[3], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);

			glLoadIdentity();
			glTranslatef(0.0, TORSO_HEIGHT - 0.25 * NECK_HEIGHT, 0.0);
			glRotatef(degree_list[1], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, nk_node.m);

			glPopMatrix();
		}
		break;
	case 1:
		if (animation != option)
			animate(option);
		else if (!done)
		{
			if (degree_list[9] > 110.0)
			{
				degree_list[9] -= STEP;
				degree_list[10] += STEP;
			}
			else
				done = 1;

			glPushMatrix();

			glLoadIdentity();
			glTranslatef(TORSO_WEIGHT / 2, 0.1 * UPPER_LEG_HEIGHT, 0.0);
			glRotatef(degree_list[9], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rul_node.m);

			glLoadIdentity();
			glTranslatef(0.0, KNEE_WEIGHT / 2, 0.0);
			glRotatef(degree_list[10], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rll_node.m);

			glLoadIdentity();
			glTranslatef(0, -horizontal, -horizontal);
			glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);

			glPopMatrix();
		}
		break;
	case 2:
		animate(option);
		break;
	}
	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-10.0, 10.0, -10.0 * (GLfloat)h / (GLfloat)w,
				10.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-10.0 * (GLfloat)w / (GLfloat)h,
				10.0 * (GLfloat)w / (GLfloat)h, 0.0, 10.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myinit()
{
	glClearColor(0.5, 1.0, 1.0, 1.0);
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	t = gluNewQuadric();
	gluQuadricDrawStyle(t, GLU_FILL);
	lua = gluNewQuadric();
	gluQuadricDrawStyle(lua, GLU_FILL);
	lelb = gluNewQuadric();
	gluQuadricDrawStyle(lelb, GLU_FILL);
	lla = gluNewQuadric();
	gluQuadricDrawStyle(lla, GLU_FILL);
	rua = gluNewQuadric();
	gluQuadricDrawStyle(rua, GLU_FILL);
	rla = gluNewQuadric();
	gluQuadricDrawStyle(rla, GLU_FILL);
	lul = gluNewQuadric();
	gluQuadricDrawStyle(lul, GLU_FILL);
	lll = gluNewQuadric();
	gluQuadricDrawStyle(lll, GLU_FILL);
	rul = gluNewQuadric();
	gluQuadricDrawStyle(rul, GLU_FILL);
	rll = gluNewQuadric();
	gluQuadricDrawStyle(rll, GLU_FILL);
	rknee = gluNewQuadric();
	gluQuadricDrawStyle(rknee, GLU_FILL);
	lknee = gluNewQuadric();
	gluQuadricDrawStyle(lknee, GLU_FILL);
	relb = gluNewQuadric();
	gluQuadricDrawStyle(relb, GLU_FILL);
	nk = gluNewQuadric();
	gluQuadricDrawStyle(nk, GLU_FILL);
	rhand = gluNewQuadric();
	gluQuadricDrawStyle(rhand, GLU_FILL);
	lhand = gluNewQuadric();
	gluQuadricDrawStyle(lhand, GLU_FILL);
	lfoot = gluNewQuadric();
	gluQuadricDrawStyle(lfoot, GLU_FILL);
	rfoot = gluNewQuadric();
	gluQuadricDrawStyle(rfoot, GLU_FILL);
	rsh = gluNewQuadric();
	gluQuadricDrawStyle(rsh, GLU_FILL);
	lsh = gluNewQuadric();
	gluQuadricDrawStyle(lsh, GLU_FILL);

	glLoadIdentity();
	glRotatef(degree_list[0], 0.0, 1.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);
	torso_node.f = torso;
	torso_node.sibling = NULL;
	torso_node.child = &nk_node;

	glLoadIdentity();
	glTranslatef(0.0, TORSO_HEIGHT - 0.25 * NECK_HEIGHT, 0.0);
	glRotatef(degree_list[1], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, nk_node.m);
	nk_node.f = neck;
	nk_node.sibling = &lsh_node;
	nk_node.child = &head_node;

	glLoadIdentity();
	glTranslatef(-(TORSO_WEIGHT + UPPER_ARM_WEIGHT), 0.9 * TORSO_HEIGHT, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lsh_node.m);
	lsh_node.f = leftShoulder;
	lsh_node.sibling = &rsh_node;
	lsh_node.child = &lua_node;

	glLoadIdentity();
	glTranslatef(TORSO_WEIGHT + UPPER_ARM_WEIGHT, 0.9 * TORSO_HEIGHT, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rsh_node.m);
	rsh_node.f = rightShoulder;
	rsh_node.sibling = &lul_node;
	rsh_node.child = &rua_node;

	glLoadIdentity();
	glTranslatef(0.0, 0.75 * NECK_HEIGHT, 0.0);
	glRotatef(degree_list[2], 0.0, 1.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);
	head_node.f = head;
	head_node.sibling = NULL;
	head_node.child = NULL;

	glLoadIdentity();
	glTranslatef(0, 0, 0.0);
	glRotatef(degree_list[3], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);
	lua_node.f = left_upper_arm;
	lua_node.sibling = NULL;
	lua_node.child = &lelb_node;

	glLoadIdentity();
	glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
	glRotatef(degree_list[4], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lelb_node.m);
	lelb_node.f = leftElbow;
	lelb_node.sibling = NULL;
	lelb_node.child = &lla_node;

	glLoadIdentity();
	glTranslatef(0, 0, 0.0);
	glRotatef(degree_list[5], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);
	rua_node.f = right_upper_arm;
	rua_node.sibling = NULL;
	rua_node.child = &relb_node;

	glLoadIdentity();
	glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
	glRotatef(degree_list[4], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, relb_node.m);
	relb_node.f = rightElbow;
	relb_node.sibling = NULL;
	relb_node.child = &rla_node;

	glLoadIdentity();
	glTranslatef(-TORSO_WEIGHT / 2, 0.1 * UPPER_LEG_HEIGHT, 0.0);
	glRotatef(degree_list[7], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lul_node.m);
	lul_node.f = left_upper_leg;
	lul_node.sibling = &rul_node;
	lul_node.child = &lknee_node;

	glLoadIdentity();
	glTranslatef(TORSO_WEIGHT / 2, 0.1 * UPPER_LEG_HEIGHT, 0.0);
	glRotatef(degree_list[9], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rul_node.m);
	rul_node.f = right_upper_leg;
	rul_node.sibling = NULL;
	rul_node.child = &rknee_node;

	glLoadIdentity();
	glTranslatef(0.0, ELBOW_WEIGHT / 2, 0.0);
	glRotatef(degree_list[4], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lla_node.m);
	lla_node.f = left_lower_arm;
	lla_node.sibling = NULL;
	lla_node.child = &lhand_node;

	glLoadIdentity();
	glTranslatef(0.0, ELBOW_WEIGHT / 2, 0.0);
	glRotatef(degree_list[4], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rla_node.m);
	rla_node.f = right_lower_arm;
	rla_node.sibling = NULL;
	rla_node.child = &rhand_node;

	glLoadIdentity();
	glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rhand_node.m);
	rhand_node.f = rightHand;
	rhand_node.sibling = NULL;
	rhand_node.child = NULL;

	glLoadIdentity();
	glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lhand_node.m);
	lhand_node.f = leftHand;
	lhand_node.sibling = NULL;
	lhand_node.child = NULL;

	glLoadIdentity();
	glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
	glRotatef(degree_list[10], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lknee_node.m);
	lknee_node.f = leftKnee;
	lknee_node.sibling = NULL;
	lknee_node.child = &lll_node;

	glLoadIdentity();
	glTranslatef(0.0, KNEE_WEIGHT / 2, 0.0);
	glRotatef(degree_list[8], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lll_node.m);
	lll_node.f = left_lower_leg;
	lll_node.sibling = NULL;
	lll_node.child = &lfoot_node;

	glLoadIdentity();
	glTranslatef(0.0, LOWER_LEG_HEIGHT, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lfoot_node.m);
	lfoot_node.f = leftFoot;
	lfoot_node.sibling = NULL;
	lfoot_node.child = NULL;

	glLoadIdentity();
	glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
	glRotatef(degree_list[10], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rknee_node.m);
	rknee_node.f = rightKnee;
	rknee_node.sibling = NULL;
	rknee_node.child = &rll_node;

	glLoadIdentity();
	glTranslatef(0.0, KNEE_WEIGHT / 2, 0.0);
	glRotatef(degree_list[10], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rll_node.m);
	rll_node.f = right_lower_leg;
	rll_node.sibling = NULL;
	rll_node.child = &rfoot_node;

	glLoadIdentity();
	glTranslatef(0.0, LOWER_LEG_HEIGHT, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rfoot_node.m);
	rfoot_node.f = rightFoot;
	rfoot_node.sibling = NULL;
	rfoot_node.child = NULL;

	glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		option = RAISE_HANDS;
		done = 0;
		animate(option);
		break;
	case '2':
		option = RAISE_LEG;
		done = 0;
		animate(option);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 1200);
	glutCreateWindow("Gigel");
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(myReshape);
	glutIdleFunc(idle);
	glutDisplayFunc(display);

	myinit();
	glutMainLoop();
	return 0;
}
