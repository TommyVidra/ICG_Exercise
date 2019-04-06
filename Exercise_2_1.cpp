#include<iostream>
#include<GL/freeglut.h>
#include<glm/geometric.hpp>
#include<stdio.h>
#include<vector>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
using namespace std;
using namespace glm;

class Tocka {
private: 
	int x;
	int y;
public:
	Tocka(int x1, int y1) {
		x = x1;
		y = y1;
	}

	void setX(int x1) { x = x1; }
	void setY(int y1) { y = y1; }
	int getX() { return x;}
	int getY() { return y;}

};

class Brid {

private:
	int a;
	int b;
	int c;
	bool lijevi;
public:
	Brid(int a1, int b1, int c1, bool l) {
		a = a1;
		b = b1; 
		c = c1;
		lijevi = l;
	}
	int getA() { return a; }
	int getB() { return b; }
	int getC() { return c; }
	bool getLijevi() { return lijevi; }
};

//bool prva = true;
vector<Tocka> v;
vector<Brid> b;

void myMouse(int button, int state, int x, int y);
void myKeyboard(unsigned char theKey, int mouseX, int mouseY);
void myPoly();
void koefCalc();
int width = 400, height = 400;

void myReshape(int w, int h)
{

	width = w; height = h;               
	glViewport(0, 0, width, height);	

	glMatrixMode(GL_PROJECTION);		
	glLoadIdentity();					
	gluOrtho2D(0, width, 0, height); 	
	glMatrixMode(GL_MODELVIEW);			
	glLoadIdentity();					

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT);		
	glPointSize(1.0);					
	glColor3f(0.0f, 0.0f, 0.0f);		
}

void myDisplay()
{
	
	glFlush();
}

//function draws a line
void myLine(float x1, float x2, float y1, float y2) {

	glBegin(GL_LINES);
	{
		glVertex2i(x1, y1); //y coordinate needs to be 1000 - y, or the polygon will be inverted
		glVertex2i(x2, y2);
	}
	glEnd();
}

int main(int argc, char ** argv)
{

	v.clear();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Poly drawing alg");

	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);

	glutMainLoop();
	return 0;
}

//Tests if a point is in the polygon
void isPoint(int x, int y) {
	bool unutar = true;
	for (int i = 0; i < b.size(); i++) {
		int temp = x * b.at(i).getA() + y * b.at(i).getB() + b.at(i).getC();

		if (temp > 0) {
			unutar = false;
			cout << "COORDINATE OUTSIDE OF A POLYGON" << endl;
			break;
		}
	}
	if (unutar)
		cout << "COORDINATE INSIDE OF A POLYGON" << endl;
	}

//Calculates the coefficients of sides from polygon
void koefCalc() {

	b.clear();
	int last = v.size() - 1;

	for (int i = 0; i < v.size(); ++i) {

		int tempA = v.at(last).getY() - v.at(i).getY();
		int tempB = -(v.at(last).getX() - v.at(i).getX());
		int tempC = v.at(last).getX()*v.at(i).getY() - v.at(last).getY()*v.at(i).getX();

		bool lijevi = v.at(last).getY() < v.at(i).getY();

		Brid temp = Brid(tempA, tempB, tempC, lijevi);
		b.push_back(temp);

		last = i;

	}

	vector<Brid> temp;
	temp.clear();
	last = b.size() - 1;
	temp.push_back(b.at(last));

	for (int i = 0; i < b.size(); ++i) {
		temp.push_back(b.at(i));
	}
	b.swap(temp);

	for (int i = 0; i < b.size(); ++i) {

		if (b.at(i).getLijevi())
			cout << "LIJEVI" << endl;
		else
			cout << "NIJE" << endl;
	}
	
}

void myPoly() {

	int j = v.size()-1;
	bool kriviRedosljed = false;
	
	//Draws an polygon
	for (int i = 0; i < v.size(); ++i) {

		myLine(v.at(j).getX(), v.at(i).getX(), v.at(j).getY(), v.at(i).getY());
		j = i;
	}

	j = v.size() - 1;

	//Tests if the polygon is convex
	for (int i = 0; i < v.size(); ++i) {

		vec3 vek = cross(vec3(v.at(j).getX(), v.at(j).getY(), 0), vec3(v.at(i).getX(), v.at(i).getY(), 0));
		vec3 V = vec3 (v.at(j).getX(), v.at(j).getY(), 0);

		if (dot(vek, V) > 0) {
			kriviRedosljed = true;
			cout << "Nije konveksan" << endl;
			break;
		}
	}

	//switches the polygon to convex if it isn't
	if (kriviRedosljed) {
		vector<Tocka> temp;
		temp.clear();
		for (int i = v.size() - 1; i >= 0; --i) {

			temp.push_back(v.at(i));
		}
		v.swap(temp);
	}

	koefCalc();
}

//Alghoritm for finding which coordinates to color
void myPolyColor() {

	int yMIN, yMAX, xMAX, xMIN, L, D, y, x, last;

	xMAX = xMIN = v.at(0).getX();
	yMAX = yMIN = v.at(0).getY();

	for (int i = 0; i < v.size(); ++i) {
		if (xMAX < v.at(i).getX())
			xMAX = v.at(i).getX();

		if (xMIN > v.at(i).getX())
			xMIN = v.at(i).getX();

		if (yMAX < v.at(i).getY())
			yMAX = v.at(i).getY();

		if (yMIN > v.at(i).getY())
			yMIN = v.at(i).getY();
	}

	for (y = yMIN; y <= yMAX; ++y) {
		L = xMIN;
		D = xMAX;
		last = v.size() - 1;

		for (int i = 0; i < v.size(); last = i++) {

			if (b.at(last).getA() == 0) {

				if (v.at(last).getY() == y) {

					if (v.at(last).getX() < v.at(i).getX()) {
						L = v.at(last).getX();
						D = v.at(i).getX();
					}
					else {
						L = v.at(i).getX();
						D = v.at(last).getX();
					}
					break;
				}
			}
			else {
				x = (-b.at(last).getB()*y - b.at(last).getC()) / (double)b.at(last).getA();
				if (b.at(last).getLijevi()) {
					if (L < x)
						L = x;
				}
				else {
					if (D > x)
						D = x;
				}
			}
		}
		myLine(L, D, y, y);
	}
}

//Mouse function
void myMouse(int button, int state, int x, int y)
{
	// Left button sets coordinates of the polygon
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//Creating an new Point and puting it at the end of an vector
		Tocka t = Tocka(x, height - y);
		v.push_back(t);

		glFlush();
	}
	//Right button sets an coordinate of the point we wish to test
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){

		isPoint(x, height - y);
		glFlush();
	}
}

//Keyboard function
void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
	switch (theKey)
	{//Key k "locks" the coordinates of the polygon and draws it
	case 'k':
		myPoly();
		break;

	case 'c':
		cout << "Put in the color you want to polygon to be" << endl;
		int x, y, k;
		cin >> x >> y >> k;

		glColor3f(x, y, k);//Sets the filling color of a polygon
		myPolyColor();
		break;
	}
	
	glFlush();
}
