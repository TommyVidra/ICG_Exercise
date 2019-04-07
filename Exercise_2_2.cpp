#include<iostream>
#include<GL/freeglut.h>
#include<glm/geometric.hpp>
#include<stdio.h>
#include<vector>
#include<fstream>
#include<sstream>
#include<time.h>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
using namespace std;
using namespace glm;

//class that reprisents an point
class Tocka {
public:
	double x;
	double y;
	double z;
public:
	Tocka(double x1, double y1, double z1) {
		x = x1;
		y = y1;
		z = z1;
	}

	/*void setX(int x1) { x = x1; }
	void setY(int y1) { y = y1; }
	int getX() { return x; }
	int getY() { return y; }
*/
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

vector<Tocka> coordinates;
vector<Polyg> polygons;
string name = "Objects";

int height = 700;
int width = 1300;
double coef = 100;

int dX = width / 2;
int dY = height / 2;
bool pomakGore = false;
bool pomakDole = false;
bool colorMode = false;
bool konveksno = false;

vector<string> split(const string& s, char delimiter) {

	vector<string> tokens;
	string token;
	istringstream tokenStream(s);

	while (getline(tokenStream, token, delimiter)) {

		tokens.push_back(token);
	}
	return tokens;
}

//function that tests if the coordinate is in the object
void isPointIn(Tocka t) {

	bool inside = true;
	for (int i = 0; i < polygons.size(); ++i) {
		if (konveksno) {
			if (t.x * polygons.at(i).a + t.y * polygons.at(i).b + t.z*polygons.at(i).c + polygons.at(i).d > 0) {
				cout << "Point is outside the polygon" << endl;
				inside = false;
				break;
			}
		}
		else {
			if (t.x * polygons.at(i).a + t.y * polygons.at(i).b + t.z*polygons.at(i).c + polygons.at(i).d < 0) {
				cout << "Point is outside the polygon" << endl;
				inside = false;
				break;
			}
		}
	}

	if (inside)
		cout << "Point is inside the polygon" << endl;

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

//takes the points from the polygons, centers them if needed and scales them for later drawing
void drawPoly() {

	for (int i = 0; i < polygons.size(); ++i) {
		

		int last = 2;
		for (int j = 0; j < 3; j++) {

			if (colorMode) {

				glColor3f(polygons.at(i).V.at(j).x + 0.2, polygons.at(i).V.at(j).y + 0.2, polygons.at(i).V.at(j).z + 0.2);

			}
			if (pomakGore) {
				myLine(polygons.at(i).V.at(last).x * coef + dX, polygons.at(i).V.at(j).x * coef + dX, polygons.at(i).V.at(last).y * coef + dY + 300, polygons.at(i).V.at(j).y * coef + dY + 300);
			}
			if (pomakDole)
			{
				myLine(polygons.at(i).V.at(last).x * coef + dX, polygons.at(i).V.at(j).x * coef + dX, polygons.at(i).V.at(last).y * coef + dY - 300, polygons.at(i).V.at(j).y * coef + dY - 300);
			}
			else if(!pomakDole && !pomakGore)
				myLine(polygons.at(i).V.at(last).x * coef + dX, polygons.at(i).V.at(j).x * coef + dX, polygons.at(i).V.at(last).y * coef + dY, polygons.at(i).V.at(j).y * coef + dY);
			
			last = j;
		}
		glFlush();
	}
}

//calculates coefficients of polygons which will later be used for seeing if a point is contained in an object
void koefCalc() {

	for (int i = 0; i < polygons.size(); ++i) {

		Tocka T1 = polygons.at(i).V.at(0);
		Tocka T2 = polygons.at(i).V.at(1);
		Tocka T3 = polygons.at(i).V.at(2);

		int a = (T2.y - T1.y) * (T3.z - T1.z) - (T2.z - T1.z) * (T3.y - T1.y);
		int b = -(T2.x - T1.x) * (T3.z - T1.z) + (T2.z - T1.z) * (T3.x - T1.x);
		int c = (T2.x - T1.x) * (T3.y - T1.y) - (T2.y - T1.y) * (T3.x - T1.x);
		int d = -(a * T1.x) - b * T1.y - c * T1.z;

		polygons.at(i).a = a;
		polygons.at(i).b = b;
		polygons.at(i).c = c;
		polygons.at(i).d = d;

	}

	drawPoly();
}

//loads coordinates from a file, which make polygons. Assembles the polygons ad puts them in a vector
void loadObject(string path) {

	string line;
	ifstream myfile(path);

	if (myfile.is_open()) {
		while (myfile.good()) {
			getline(myfile, line);
			vector<string> splittedString = split(line, ' ');

			if (splittedString.size() > 0) {
				if (splittedString.at(0) == "v") {

					Tocka T = Tocka(strtod(splittedString.at(1).c_str(), NULL), strtod(splittedString.at(2).c_str(), NULL), strtod(splittedString.at(3).c_str(), NULL));
					coordinates.push_back(T);
				}
				else if (splittedString.at(0) == "f") {

					Polyg P = Polyg();
					P.V.push_back(coordinates.at(atoi(splittedString.at(1).c_str()) -1));
					P.V.push_back(coordinates.at(atoi(splittedString.at(2).c_str()) -1));
					P.V.push_back(coordinates.at(atoi(splittedString.at(3).c_str()) -1));
					polygons.push_back(P);

				}
				else if (splittedString.at(0) == "g")
					name = splittedString.at(1);
			}
		}
		myfile.close();
		koefCalc();

	}
	else
		cout << "Error while opening file" << endl;

}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(1.0);
	drawPoly();
	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glColor3f(0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {

	//selects which object to draw
	cout << "Put in any number from 0 to 12" << endl;
	int j;
	cin >> j;

	//Mode that colors polygons in multiple colors
	cout << "Color mode? y , n" << endl;
	char d;
	cin >> d;

	if (d = 'y')
		colorMode = true;

	switch (j) {
		case 0:
			loadObject("D:\\FER\\IRG\\tetrahedron.obj");
			konveksno = true;
			coef = 500;
			break;
		case 1:
			loadObject("D:\\FER\\IRG\\kocka.obj");
			konveksno = true;
			coef = 500;
			break;
		case 2:
			loadObject("D:\\FER\\IRG\\teddy.obj");
			coef = 15;
			break;
		case 3:
			loadObject("D:\\FER\\IRG\\bird.obj");
			coef = 400;
			break;
		case 4:
			loadObject("D:\\FER\\IRG\\teapot.obj");
			break;
		case 5:
			loadObject("D:\\FER\\IRG\\frog.obj");
			coef = 60;
			break;
		case 6:
			loadObject("D:\\FER\\IRG\\all.obj");
			coef = 800;
			pomakGore = true;
			break;
		case 7:
			loadObject("D:\\FER\\IRG\\bull.obj");
			coef = 0.2;
			pomakDole = true;
			break;
		case 8:
			loadObject("D:\\FER\\IRG\\porsche.obj");
			coef = 1100;
			break;
		case 9:
			loadObject("D:\\FER\\IRG\\arena.obj");
			coef = 800;
			break;
		case 10:
			loadObject("D:\\FER\\IRG\\dragon.obj");
			coef = 800;
			break;
		case 11:
			loadObject("D:\\FER\\IRG\\temple.obj");
			coef = 1000;
			break;
		default:
			loadObject("D:\\FER\\IRG\\skull.obj");
			coef = 800;
			break;
	}

	cout << "Put in x, y and z coordinates of a point" << endl;
	int x, y, z;
	cin >> x >> y >> z;

	Tocka temp = Tocka (x, y, z);
	isPointIn(temp);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(200, 200);

	glutCreateWindow(name.c_str());

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
