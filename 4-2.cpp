#include<iostream>
#include<GL/freeglut.h>
#include<glm/geometric.hpp>
#include<stdio.h>
#include<vector>
#include<fstream>
#include<sstream>
#include<time.h>
#include<gl/glut.h>
#include<iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
using namespace std;
using namespace glm;

class Tocka {
	public:
		double min;
		double max;
	public:
		Tocka(double x1, double y1) {
			min = x1;
			max = y1;
		}
	};
//class that reprisents an polygon
class Polyg {
	
	public:
		vector<Tocka> V;
		int a;
		int b;
		int c;
		int d;
	
	public:
	
		Polyg() {
			V.clear();
		}
	};

class Cmpx {
	public:
		double real;
		double img;
	public:
		Cmpx(double r, double i)
		{
			real = r;
			img = i;
		}
		public:
			double mulitplyR()
			{
				return real * real;
			}
			double mulitplyI()
			{
				return img * img;
			}
			double mulitply()
			{
				return real * img;
			}
};

GLuint window;
GLuint width = 1300, height = 1000;

vector<Tocka> coordinates; //tocke
vector<Polyg> polygons; //ravnine

bool colorMode = false;
Tocka y = Tocka(0, 0); //ymin ymax
Tocka x = Tocka(0, 0); //xmin xmax
Tocka u = Tocka(0, 0); //umin umax
Tocka v = Tocka(0, 0); //vmin vmax
Cmpx complex = Cmpx(0,0); //kompleksni
bool julije = false;
double eps;
double iterations;

double calcModulM(Cmpx cmpx)
{
	Cmpx temp = Cmpx(0, 0);

	for (int i = 1; i <= iterations; ++i)
	{
		double tempR = temp.mulitplyR() - temp.mulitplyI() + cmpx.real;
		double tempI = 2 * temp.mulitply() + cmpx.img;

		temp.real = tempR; temp.img = tempI;
		if (temp.mulitplyR() + temp.mulitplyI() > eps * eps)
			return i;
	}
	return -1;
}

double calcModulJ(Cmpx cmpx)
{
	Cmpx temp = Cmpx(cmpx.real, cmpx.img);

	for (int i = 1; i <= iterations; ++i)
	{
		double tempR = temp.mulitplyR() - temp.mulitplyI() + complex.real;
		double tempI = 2 * temp.mulitply() + complex.img;

		temp.real = tempR; temp.img = tempI;
		if (temp.mulitplyR() + temp.mulitplyI() > eps* eps)
			return i;
	}
	return -1;
}

void rendersceneMendelbort() {

	glPointSize(1);
	glBegin(GL_POINTS);
	for (int i = 0; i <= y.max; i++) {
		for (int j = x.min; j <= x.max; j++) {
			double tempR = (double)(j - x.min) / (double)(x.max - x.min) * (u.max - u.min) + u.min;
			double tempI = (double)(i - y.min) / (double)(y.max - y.min) * (v.max - v.min) + v.min;
			Cmpx temp = Cmpx(tempR, tempI);
			int rez = calcModulM(temp);

			if (rez == -1) 
				glColor3f(0, 0, 0);
			
			else 
				glColor3f((double)rez / iterations - 0.1, 1 - (double)rez / iterations / 2.0 - 0.1, 0.8 - (double)rez / iterations / 3.0- 0.1);
			
			glVertex2i(j, i);
		}
	}
	glEnd();
}

void rendersceneJulije() {

	glPointSize(1);
	glBegin(GL_POINTS);
	for (int i = 0; i <= y.max; i++) { 
		for (int j = 0; j <= x.max; j++) { 
			double tempR = (double)(j - x.min) / (double)(x.max - x.min) * (u.max - u.min) + u.min;
			double tempI = (double)(i - y.min) / (double)(y.max - y.min) * (v.max - v.min) + v.min;
			Cmpx temp = Cmpx(tempR, tempI);
			int rez = calcModulJ(temp);

			if (rez == -1) 
				glColor3f(0, 0, 0);
			
			else 
				glColor3f((double)rez / iterations, 1 - (double)rez / iterations / 2.0, 0.8 - (double)rez / iterations / 3.0);
			
			glVertex2i(j, i);
		}
	}
	glEnd();
}

void display() {

	glClearColor(1.0f, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	if (julije)
		rendersceneJulije();
	else
		rendersceneMendelbort();
	
	glutSwapBuffers();

}

void reshape(int width, int height) 
{

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);

}

void unosi()
{
	cout << "Unesite prag epsilon" << endl;
	cin >> eps;
	cout << "Unesite broj maksimalnih iteracija " << endl;
	cin >> iterations;
	cout << "Unesite Umin Umax Vmin Vmax" << endl;
	cin >> u.min >> u.max >> v.min >> v.max;
	cout << "Unesite razlucivost Xmax Ymax" << endl;
	cin >> x.max >> y.max;
}

void mendelbortFunc()
{
	unosi();
}

void julijeFunc()
{
	unosi();
	cout << "Unesite realni i imaginarni dio konstante c" << endl;
	cin >> complex.real >> complex.img;
}

void nextStep(bool julije)
{
	if (julije)
		julijeFunc();
	else
		mendelbortFunc();
}

int main(int argc, char** argv)
{

	int temp;
	cout << "Pritinsi:\n1: Mendelbrot\n2: Julije" << endl;
	cin >> temp;

	if (temp == 2)
		julije = true;

	nextStep(julije);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("Zadatak");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
