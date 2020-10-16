//
//#include<iostream>
//#include<GL/freeglut.h>
//#include<glm/geometric.hpp>
//#include<stdio.h>
//#include<vector>
//#include<fstream>
//#include<sstream>
//#include<time.h>
//#include<gl/glut.h>
//
//#define GLM_ENABLE_EXPERIMENTAL
//#include "glm/ext.hpp"
//using namespace std;
//using namespace glm;
//
////void reshape(int width, int height);
//
//GLuint window;
//GLint height = 1000, width = 1300;
//
//string path = "E:\\Projects\\OpenGL\\OpenGL\\OpenGL\\Objects";
//
//string name = "Objects";
////class that reprisents an point
//class Tocka {
//public:
//	double x;
//	double y;
//	double z;
//public:
//	Tocka(double x1, double y1, double z1) {
//		x = x1;
//		y = y1;
//		z = z1;
//	}
//};
//
////class that reprisents an polygon
//class Polyg {
//
//public:
//	vector<Tocka> V;
//	int a;
//	int b;
//	int c;
//	int d;
//
//public:
//
//	Polyg() {
//		V.clear();
//	}
//};
//
//vector<Tocka> coordinates;
//vector<Polyg> polygons;
//vector<Tocka> curve;
//vector<Tocka> control;
//
//bool colorMode = false;
//
//Tocka glediste = Tocka(0, 0, 0);
//Tocka ociste = Tocka(1, 1, 3);
//Tocka vrhovi = Tocka(0, 1, 0);
//
//vector<string> split(const string& s, char delimiter) {
//
//	vector<string> tokens;
//	string token;
//	istringstream tokenStream(s);
//
//	while (getline(tokenStream, token, delimiter)) {
//
//		tokens.push_back(token);
//	}
//	return tokens;
//}
//
//void drawPolygon(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
//
//	glBegin(GL_LINE_STRIP);
//	glVertex3d(x1, y1, z1);
//	glVertex3d(x2, y2, z2);
//	glVertex3d(x3, y3, z3);
//	glEnd();
//}
//
////Returns the coordinate of a point in a polygon
//double getCoordinate(int i, int j, int z) {
//	
//	if(z == 0)
//		return polygons.at(i).V.at(j).x;
//	else if (z == 1)
//		return polygons.at(i).V.at(j).y;
//	else 
//		return polygons.at(i).V.at(j).z;
//}
//
////takes the points from the polygons, centers them if needed and scales them for later drawing
//void drawPoly() {
//	glColor3f(0.0f, 0.0f, 0.0f);
//
//	for (int i = 0; i < polygons.size(); ++i) {
//
//		if (colorMode)
//			glColor3f(polygons.at(i).V.at(1).x + 0.2, polygons.at(i).V.at(1).y + 0.2, polygons.at(i).V.at(1).z + 0.2);
//		else
//			glColor3f(0.0f, 0.0f, 0.0f);
//
//		drawPolygon(getCoordinate(i, 0, 0), getCoordinate(i, 0, 1), getCoordinate(i, 0, 2), getCoordinate(i, 1, 0), getCoordinate(i, 1, 1), getCoordinate(i, 1, 2), getCoordinate(i, 2, 0), getCoordinate(i, 2, 1), getCoordinate(i, 2, 2));
//
//		glFlush();
//	}
//}
//
////loads coordinates from a file, which make polygons. Assembles the polygons and puts them in a vector
//void loadObject(string path) {
//
//	string line;
//	ifstream myfile(path);
//
//
//	if (myfile.is_open()) {
//		while (myfile.good()) {
//			getline(myfile, line);
//			vector<string> splittedString = split(line, ' ');
//
//			if (splittedString.size() > 0) {
//				if (splittedString.at(0) == "v") {
//
//					Tocka T = Tocka(strtod(splittedString.at(1).c_str(), NULL), strtod(splittedString.at(2).c_str(), NULL), strtod(splittedString.at(3).c_str(), NULL));
//					coordinates.push_back(T);
//				}
//				else if (splittedString.at(0) == "f") {
//
//					Polyg P = Polyg();
//					P.V.push_back(coordinates.at(atoi(splittedString.at(1).c_str()) - 1));
//					P.V.push_back(coordinates.at(atoi(splittedString.at(2).c_str()) - 1));
//					P.V.push_back(coordinates.at(atoi(splittedString.at(3).c_str()) - 1));
//					polygons.push_back(P);
//
//				}
//				else if (splittedString.at(0) == "g")
//					name = splittedString.at(1);
//			}
//		}
//		myfile.close();
//		drawPoly();
//
//	}
//	else
//		cout << "Error while opening file" << endl;
//
//}
//
//void swichObjects(int j) 
//{
//	switch (j) {
//	case 0:
//		loadObject(path + "\\tetrahedron.obj");
//		break;
//	case 1:
//		loadObject(path + "\\kocka.obj");
//		break;
//	case 2:
//		loadObject(path + "\\teddy.obj");
//		break;
//	case 3:
//		loadObject(path + "\\bird.obj");
//		break;
//	case 4:
//		loadObject(path + "\\teapot.obj");
//		break;
//	case 5:
//		loadObject(path + "\\frog.obj");
//		break;
//	case 6:
//		loadObject(path + "\\all.obj");
//		break;
//	case 7:
//		loadObject(path + "\\bull.obj");
//		break;
//	case 8:
//		loadObject(path + "\\porsche.obj");
//		break;
//	case 9:
//		loadObject(path + "\\arena.obj");
//		break;
//	case 10:
//		loadObject(path + "\\dragon.obj");
//		break;
//	case 11:
//		loadObject(path + "\\temple.obj");
//		break;
//	default:
//		loadObject(path + "\\skull.obj");
//		break;
//	}
//
//}
//
//void drawCurve() {
//	double X1;
//	double Y1;
//	double Z1;
//	
//	glPointSize(3.0f);
//	glColor3f(0.0f, 2.0f, 1.0f);
//	glBegin(GL_POINTS);
//	for (int i = 0; i < 100; ++i) {
//		
//		X1 = curve.at(i).x;
//		Y1 = curve.at(i).y;
//		Z1 = curve.at(i).z;
//		glVertex3f(X1, Y1, Z1);
//		
//	}
//	glEnd();
//}
//
//void renderScene() {
//
//	glPushMatrix();
//	drawPoly();
//	drawCurve();
//	glPopMatrix();
//
//}
//
//void update()
//{
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glFrustum(-1.2, 1.2, -1.2, 1.2, 1.5, 100);
//	glMatrixMode(GL_MODELVIEW);
//	glViewport(0, 0, width, height);
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glLoadIdentity();
//	gluLookAt(ociste.x, ociste.y, ociste.z, glediste.x, glediste.y, glediste.z, vrhovi.x, vrhovi.y, vrhovi.z);
//	renderScene();
//	glutSwapBuffers();
//}
//
//void mySpecKeyboard(int theKey, int mouseX, int mouseY)
//{
//	switch (theKey)
//	{
//	case GLUT_KEY_HOME:
//		
//		for (int i = 0; i <100; i+=1) {
//			ociste.x = curve.at(i).x;
//			ociste.y = curve.at(i).y;
//			ociste.z = curve.at(i).z;
//			update();
//			Sleep(10);
//		}
//		break;
//
//	case GLUT_KEY_UP:
//		ociste.x += 0.1;
//		update();
//		break;
//	case GLUT_KEY_DOWN:
//		ociste.x -= 0.1;
//		update();
//		break;
//	case GLUT_KEY_LEFT:
//		ociste.y += 0.1;
//		update();
//		break;
//	case GLUT_KEY_RIGHT:
//		ociste.y -= 0.1;
//		update();
//		break;
//	}
//}
//
//void initGV() {
//	
//	glediste.x = 0;
//	glediste.y = 0;
//	glediste.z = 0;
//	vrhovi.x = 0;
//	vrhovi.y = 1;
//	vrhovi.z = 0;
//
//}
//
//void display() {
//
//	initGV();
//
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glLoadIdentity();
//	gluLookAt(ociste.x, ociste.y, ociste.z, glediste.x, glediste.y, glediste.z, vrhovi.x, vrhovi.y, vrhovi.z);
//
//	renderScene();
//	glutSwapBuffers();
//}
//
//void initCurve() {
//
//	for (int i = 0; i < 100; ++i) {
//		Tocka T = Tocka(0, 0, 0);
//		curve.push_back(T);
//	}
//
//}
//
//double equation(int n, double t, int i) {
//
//	return (factorial(n) * pow(t, i) * pow(1 - t, n - i)) / factorial(i) * factorial(n - i);
//}
//
//void beizerCurve() {
//	
//	Tocka T = Tocka(2, 2, 2);
//	Tocka T1 = Tocka(-2, 2, 2);
//	Tocka T2 = Tocka(-2, -2, 2);
//	Tocka T3 = Tocka(2, -2, 2);
//
//	control.push_back(T);
//	control.push_back(T1);
//	control.push_back(T2);
//	control.push_back(T3);
//
//	int k = 0;
//	for (double t = 0; t < 1; t += 0.01) {
//		int l = 0;
//		for (int j = 0; j <= 3; j++) {
//			curve.at(k).x += control.at(j).x * equation(3, t, l);
//			curve.at(k).y += control.at(j).y * equation(3, t, l);
//			curve.at(k).z += control.at(j).z * equation(3, t, l);
//			++l;
//		}
//		k++;
//	}
//
//
//}
//
//void reshape(int w, int h) {
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glFrustum(-1.2, 1.2, -1.2, 1.2, 1.5, 40);
//
//	glMatrixMode(GL_MODELVIEW);
//	glViewport(0, 0, width, height);
//}
//
//
//
//int main(int argc, char **argv) {
//
//	initGV();
//
//	//selects which object to draw
//	cout << "Unesite brojku od 0 do 12" << endl;
//	int j;
//	cin >> j;
//	swichObjects(j);
//
//	cout << "Boja? \n1 za da" << endl;
//	cin >> j;
//	if (j == 1)
//		colorMode = true;
//
//	//string path = "E:\\Projects\\OpenGL\\OpenGL\\OpenGL\\Objects\\tetrahedron.obj";
//	initCurve();
//	beizerCurve();
//	
//
//	cout << "Pritisnite HOME kako bi zapoceli" << endl;
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE);
//	glutInitWindowSize(width, height);
//	glutInitWindowPosition(100, 0);
//	glutCreateWindow("Zadatak2");
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//	glutSpecialFunc(mySpecKeyboard);
//	glutMainLoop();
//	return 0;
//
//}
