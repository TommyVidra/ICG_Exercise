#include<GL/freeglut.h>
#include<glm/geometric.hpp>
#include<iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
using namespace std;
using namespace glm;


float xV1, xV2;
float yV1, yV2;

void Init() {

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1000, 0, 1000);
}

//function for drawing Bresenham Line Algorithm
void draw(float x, float y) {

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

//function that draws an line with coordinates y1 + 20 and y2 + 20 
void drawLine(int x1, int y1, int x2, int y2) {

	glBegin(GL_LINES);
	{
		glVertex2i(x1, y1 + 20);
		glVertex2i(x2, y2 + 20);
	}
	glEnd();
}


//function for 0 to 90 degrees
void LinePositive(float x1, float x2, float y1, float y2) {

	float dx, d, endX, endY, startX, startY, D;

	startX = x1;
	startY = y1;
	endX = x2;
	endY = y2;

	if (endY > endX) {

		float temp = endX;
		endX = endY;
		endY = temp;

		temp = startX;
		startX = startY;
		startY = temp;

		dx = -2 * (endX - startX);
		d = -(endX - startX);
		D = 2 * (endY - startY);

		for (float i = startX; i < endX; ++i) {

			draw(startY, i);
			d += D;

			if (d >= 0) {
				d = d + dx;
				startY += 1;
			}
		}
	}

	else {

		dx = -2 * (endX - startX);
		d = -(endX - startX);
		D = 2 * (endY - startY);
		for (float i = startX; i < endX; ++i) {

			draw(i, startY);
			d += D;

			if (d >= 0) {
				d = d + dx;
				startY += 1;
			}
		}
	}
}

//function for 0 to -90 degrees
void LineNegative(float x1, float x2, float y1, float y2) {

	float dx, d, endX, endY, startX, startY, D;

	startX = x1;
	startY = y1;
	endX = x2;
	endY = y2;

	if (-(endY - startY) > endX - startX) {

		float temp = endX;
		endX = startY;
		startY = temp;

		temp = startX;
		startX = endY;
		endY = temp;

		dx = 2 * (endX - startX);
		d = (endX - startX);
		D = 2 * (endY - startY);

		for (float i = startX; i < endX; ++i) {

			draw(startY, i);
			d += D;

			if (d <= 0) {
				d = d + dx;
				startY -= 1;
			}
		}
	}

	else {

		dx = 2 * (endX - startX);
		d = (endX - startX);
		D = 2 * (endY - startY);
		for (float i = startX; i < endX; ++i) {

			draw(i, startY);
			d += D;

			if (d <= 0) {
				d = d + dx;
				startY -= 1;
			}
		}
	}
}


//function that calls Bresenham Line Algorithm methods, depending on the quadrant in the
//coordinate system
void myLine(float x1, float x2, float y1, float y2) {

	if (x1 < x2) {
		if (y1 < y2)
			LinePositive(x1, x2, y1, y2);
		else
			LineNegative(x1, x2, y1, y2);
	}
	else {
		if (y1 > y2)
			LinePositive(x2, x1, y2, y1);
		else
			LineNegative(x2, x1, y2, y1);
	}
}

void Display() {

	drawLine(xV1, yV1, xV2, yV2);
	myLine(xV1, xV2, yV1, yV2);
	glFlush();
}

int main(int argc, char ** argv) {
	
	cout << "Put in the coordinates of V1 and V2" << endl;
	cin >> xV1 >> yV1 >> xV2 >> yV2;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bresenham's Line Drawing");

	Init();
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}
