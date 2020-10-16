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
//GLuint window;
//GLint height = 1000, width = 1300;
//
//string path = "E:\\Projects\\OpenGL\\OpenGL\\OpenGL\\Objects";
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
//void renderScene() {
//
//	glPushMatrix();
//	drawPoly();
//	glPopMatrix();
//
//}
//
//void updatePerspective()
//{
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glFrustum(-1.2, 1.2, -1.2, 1.2, 1.5, 40);
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
//void mySpecKeyboard(int theKey, int mouseX, int mouseY)
//{
//	switch (theKey)
//	{
//	case GLUT_KEY_RIGHT:
//		glediste.x += 1;
//		break;
//	case GLUT_KEY_LEFT:
//		glediste.x -= 1;
//		break;
//	case GLUT_KEY_UP:
//		glediste.y += 1;
//		break;
//	case GLUT_KEY_DOWN:
//		glediste.y -= 1;
//		break;
//	case GLUT_KEY_PAGE_UP:
//		glediste.z += 1;
//		break;
//	case GLUT_KEY_PAGE_DOWN:
//		glediste.z -= 1;
//		break;
//	case GLUT_KEY_HOME:
//		glediste.x = 0;
//		glediste.y = 0;
//		glediste.z = 0;
//		ociste.x = 1;
//		ociste.y = 1;
//		ociste.z = 3;
//		break;
//
//	case GLUT_KEY_F1:
//		ociste.x += 1;
//		break;
//	case GLUT_KEY_F2:
//		ociste.x -= 1;
//		break;
//	case GLUT_KEY_F3:
//		ociste.y += 1;
//		break;
//	case GLUT_KEY_F4:
//		ociste.y -= 1;
//		break;
//	case GLUT_KEY_F5:
//		ociste.z += 1;
//		break;
//	case GLUT_KEY_F6:
//		ociste.z -= 1;
//		break;
//	}
//	updatePerspective();
//}
//
//void display() {
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
//void reshape(int w, int h) {
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glFrustum(-1.2, 1.2, -1.2, 1.2, 1.5, 5);
//
//	glMatrixMode(GL_MODELVIEW);
//	glViewport(0, 0, width, height);
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
//void calculations()
//{
//	//T1 - pomak ishodista
//	mat4x4 T1 = mat4x4(1, 0, 0, 0,
//						0, 1, 0, 0,
//						0, 0, 1, 0,
//						-ociste.x, -ociste.y, -ociste.z, 0);
//
//	//x, y, z of G1
//	double tempGx = glediste.x - ociste.x;
//	double tempGy = glediste.y - ociste.y;
//	double tempGz = glediste.z - ociste.z;
//
//	//sin, cos for T2
//	double tempSin = tempGy / (sqrt(pow(tempGx, 2) + pow(tempGy, 2)));
//	double tempCos = tempGx / (sqrt(pow(tempGx, 2) + pow(tempGy, 2)));
//
//	//T2 - rot za kut alfa oko z osi
//	mat4x4 T2 = mat4x4(tempCos, -tempSin, 0, 0,
//						tempSin, tempCos, 0, 0,
//						0, 0, 1, 0,
//						0, 0, 0, 1);
//
//	//x, y, z of G2, z didnt change
//	tempGx = (sqrt(pow(tempGx, 2) + pow(tempGy, 2)));
//	tempGy = 0;
//
//	//sin, cos for T3
//	tempSin = tempGx / (sqrt(pow(tempGx, 2) + pow(tempGz, 2)));
//	tempCos = tempGz / (sqrt(pow(tempGx, 2) + pow(tempGz, 2)));
//
//	//T3 - rot za kut beta oko y osi
//	mat4x4 T3 = mat4x4(tempCos, 0, tempSin, 0,
//						0, 1, 0, 0,	
//						-tempSin, 0, tempCos, 0,
//						0, 0, 0, 1);
//
//	//x, y, z of G3
//	tempGx = 0;
//	tempGy = 0;
//	tempGz = (sqrt(pow(tempGx, 2) + pow(tempGz, 2)));
//
//	//T4 - rot za 90°oko z osi
//	mat4x4 T4 = mat4x4(0, -1, 0, 0,
//						1, 0, 0, 0,
//						0, 0, 1, 0, 
//						0, 0, 0, 1);
//
//	//promjena predznaka na x osi
//	mat4x4 T5 = mat4x4(-1, 0, 0, 0,
//						0, 1, 0, 0,
//						0, 0, 1, 0,
//						0, 0, 0, 1);
//
//	cout << "\nT1:\n" << to_string(T1) << "\nT2:\n" << to_string(T2) << "\nT3:\n" << to_string(T3) << "\nT4:\n" << to_string(T4) << "\nT5:\n" << to_string(T5) << endl;
//	mat4x4 T = T5 * T4 * T3 * T2 * T1;
//	cout << "\nT:\n" << to_string(T) << endl;
//
//	double H = sqrt(pow(ociste.x - glediste.x, 2) + pow(ociste.y - glediste.y, 2) + pow(ociste.z - glediste.z, 2));
//	mat4x4 P = mat4x4(1, 0, 0, 0,
//		0, 1, 0, 0,
//		0, 0, 0, 1 / H,
//		0, 0, 0, 0);
//
//	cout << "\nH:\n" << to_string(H) << "\nP:\n" << to_string(P) << endl;
//}
//
//int main(int argc, char** argv) {
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
//	cout << "Zelite li mjenjati koorinate ocista/gledista?\n1 za da" << endl;
//	cin >> j;
//
//	if (j == 1) {
//
//			cout << "Upisite koordinate Ocista, i onda Gledista" << endl;
//
//			cin >> ociste.x >> ociste.y >> ociste.z;
//			cin >> glediste.x >> glediste.y >> glediste.z;
//
//			cout << "Ociste: " << ociste.x << " " << ociste.y << " " << ociste.z << "\nGlediste: " << glediste.x << " " << glediste.y << " " << glediste.z << " " << endl;
//
//	}
//	
//	calculations();
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE);
//	glutInitWindowSize(width, height);
//	glutInitWindowPosition(100, 0);
//	glutCreateWindow(name.c_str());
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//	glutSpecialFunc(mySpecKeyboard);
//	glutMainLoop();
//	return 0;
//
//
//}
