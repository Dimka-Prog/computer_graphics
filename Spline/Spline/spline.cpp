#include<GL/glew.h>
#include<GL/freeglut.h>
#include<iostream>

using namespace std;

int fact(int points)
{
	if (points == 0)
		return 1;
	else
		return points * fact(points - 1);

}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);

	double x = 0, y = 0,
		t = 0.01,
		//alpha = 0.5; //Catmull–Rom
		alpha = 0.16; //uniform B-spline

	const int sizeArray = 4;
	int referencePoints = 4;

	int array_PxINT[sizeArray] = {},
		array_PyINT[sizeArray] = {},
		arrayPx[sizeArray] = { 25, 35, 100, 125 }, // { 25, 35, 100, 125 } - рациональные кривые (полином Бернштейна)
												   // { 100, 150, 200, 250 } - Catmull–Rom, uniform B-spline

		arrayPy[sizeArray] = { 50, 125, 135, 25 }; // { 100, 50, 100, 50 } - Catmull–Rom; 
												   // { 50, 100, 100, 50 } - uniform B-spline
	                                               // { 50, 125, 135, 25 } - рациональные кривые (полином Бернштейна)

	/* Catmull–Rom
	{-1, 3, -3, 1},
	{2, -5, 4, -1},
	{-1, 0, 1, 0},
	{0, 2, 0, 0}
	*/

	/* uniform B-spline
	{-1, 3, -3, 1},
	{3, -6, 3, 0},
	{-3, 0, 3, 0},
	{1, 4, 1, 0}
	*/
	int arrayINT[sizeArray][sizeArray] = {
			{-1, 3, -3, 1},
			{3, -6, 3, 0},
			{-3, 0, 3, 0},
			{1, 4, 1, 0}
	};

	/*
	while (t < 1.01)
	{
		double arrayT[sizeArray] = { pow(t, 3), pow(t, 2), t, 1 };

		for (int i = 0; i < size(arrayT); i++)
			arrayT[i] *= alpha;


		for (int rows = 0; rows < sizeArray; rows++)
		{
			for (int cols = 0; cols < sizeArray; cols++)
			{
				array_PxINT[rows] += arrayINT[rows][cols] * arrayPx[cols];
				array_PyINT[rows] += arrayINT[rows][cols] * arrayPy[cols];
			}
		}


		for (int i = 0; i < size(arrayT); i++)
		{
			x += arrayT[i] * array_PxINT[i];
			y += arrayT[i] * array_PyINT[i];

			array_PxINT[i] = 0;
			array_PyINT[i] = 0;
		}

		glVertex2i(x, y);

		x = 0;
		y = 0;
		t += 0.01;
	} */

	// Рациональные кривые Безье
	
	t = 0.01;

	int w[sizeArray] = { 1, 30, 30, 1 };

	double numeratorX = 0,
		   numeratorY = 0,
		   denominator = 0;
		   
	double b = 0,
		   C = 0;

	while (t < 1.001)
	{
		for (int pointNumber = 0; pointNumber < sizeArray; pointNumber++)
		{
			C = fact(referencePoints) / (fact(pointNumber) * fact(referencePoints - pointNumber));
			b = C * pow(t, pointNumber) * pow((1 - t), referencePoints - pointNumber);

			numeratorX += w[pointNumber] * arrayPx[pointNumber] * b;
			numeratorY += w[pointNumber] * arrayPy[pointNumber] * b;
			denominator += w[pointNumber] * b;
		}

		x = numeratorX / denominator;
		y = numeratorY / denominator;
		t += 0.001;

		numeratorX = 0;
		numeratorY = 0;
		denominator = 0;

		glVertex2i(x, y);
	}

	glEnd();
	glFlush();
}

void myinit() {
	glClearColor(255, 255, 255, 255);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 200, 0, 200); // (50, 300, 0, 200)
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(400, 150);
	glutCreateWindow("spline");
	myinit();
	glutDisplayFunc(display);

	glutMainLoop();
}