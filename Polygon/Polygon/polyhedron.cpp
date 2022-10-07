#include<GL/glew.h>
#include<GL/freeglut.h>
#include<iostream>
#include<ctime>

using namespace std;

const int points = 50;
int centreX = 100, centreY = 100;
int arrX[points] = {}, arrY[points] = {};

void circle()
{
	srand(time(NULL));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_POLYGON);
	glColor3d((rand() % 70 + 15) / double(100), (rand() % 70 + 15) / double(100), (rand() % 70 + 15) / double(100));

	int radius = rand() % 70 + 30;
	int x = 0, y = 0, angle = 360 / points;

	for (int i = 0; i < points; i++)
	{
		x = radius * sin(angle * 3.14 / 180) + centreX;
		y = radius * cos(angle * 3.14 / 180) + centreY;

		arrX[i] = x;
		arrY[i] = y;

		glVertex3d(x, y, 0);
		angle += 360 / points;
	}

	glEnd();
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	srand(time(NULL));

	circle();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (int i = 0; i < points; i++)
	{
		glBegin(GL_TRIANGLES);
		glColor3d((rand() % 70 + 15) / double(100), (rand() % 70 + 15) / double(100), (rand() % 70 + 15) / double(100));

		if (i + 1 < points)
		{
			glVertex3d(arrX[i], arrY[i], 0);
			glVertex3d(centreX, centreY, 0);
			glVertex3d(arrX[i + 1], arrY[i + 1], 0);
		}
		else
		{
			glVertex3d(arrX[points - 1], arrY[points - 1], 0);
			glVertex3d(centreX, centreY, 0);
			glVertex3d(arrX[0], arrY[0], 0);
		}
		
		glEnd();
	}

	glFlush();
}

void myinit() {
	glClearColor(255, 255, 255, 255);
	glLineWidth(3);
	glPointSize(3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 200, 0, 200); 
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(400, 150);
	glutCreateWindow("Polygon circle");
	myinit();
	glutDisplayFunc(display);

	glutMainLoop();
}