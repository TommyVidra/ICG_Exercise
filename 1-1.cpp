//#include<glm/mat3x3.hpp>
//#include<glm/vec3.hpp>
//#include<glm/geometric.hpp>
//#include<iostream>
//#include<glm/gtc/type_ptr.hpp>
//#include<iomanip>
//#include<glm/gtx/string_cast.hpp>
//
//#define glm_enable_experimental
//#include "glm/ext.hpp"
//using namespace std;
//using namespace glm;
//
//
//void vectorf() {
//
//	vec3 v1_1 = vec3(2, 3, -4);
//	vec3 v1_2 = vec3(-1, 4, -1);
//	vec3 v1 = v1_1 + v1_2;
//
//	int s = dot(v1_1, v1_2);
//
//	vec3 temp = vec3(2, 2, 4);
//	vec3 v2 = cross(v1, temp);
//
//	vec3 v3 = normalize(v2);
//	vec3 v4 = -v2;
//}
//
//void matrixf() {
//
//	mat3x3 m1_1 = mat3x3(1, 2, 3,
//		2, 1, 3,
//		4, 5, 1);
//
//	mat3x3 tempm = mat3x3(-1, 2, -3,
//		5, -2, 7,
//		-4, -1, 3);
//
//	mat3x3 m1 = m1_1 + tempm;
//
//	mat3x3 m2_1 = mat3x3(1, 2, 3,
//		2, 1, 3,
//		4, 5, 1);
//
//	mat3x3 m2 = transpose(tempm) * m2_1;
//	mat3x3 m3 = inverse(tempm) * m2_1;
//
//	cout << to_string(m1) << endl;
//	cout << to_string(m2) << endl;
//	cout << to_string(m3) << endl;
//}
//
//void equationf() {
//
//	//variables that represent our equations, x, y, z and the result r
//	float x1, y1, z1, r1;
//	float x2, y2, z2, r2;
//	float x3, y3, z3, r3;
//
//	cout << "write x, y, z variables and the result" << endl;
//	cin >> x1 >> y1 >> z1 >> r1;
//	cout << "write x, y, z variables and the result" << endl;
//	cin >> x2 >> y2 >> z2 >> r2;
//	cout << "write x, y, z variables and the result" << endl;
//	cin >> x3 >> y3 >> z3 >> r3;
//
//	cout << "equation looks like this: " + to_string(x1) + "x " + to_string(y1) + "y " + to_string(z1) + "z " << endl;
//	cout << "equation looks like this: " + to_string(x2) + "x " + to_string(y2) + "y " + to_string(z2) + "z " << endl;
//	cout << "equation looks like this: " + to_string(x3) + "x " + to_string(y3) + "y " + to_string(z3) + "z " << endl;
//
//	//defines a matrix with x, y and z variables
//	mat3x3 m = mat3x3(x1, y1, z1, x2, y2, z2, x3, y3, z3);
//
//	//defines a vector with the results to equations 
//	vec3 mm = vec3(r1, r2, r3);
//
//	//inverts the matrix
//	mat3x3 m1 = inverse(m);
//
//	//vector that represents our solutions x, y, z
//	vec3 solution = mm * m1;
//	cout << to_string(solution) + " this is the solution to equations" << endl;
//
//}
//
//void trianglef() {
//
//
//	cout << "put in coordinates a, b, c and an coordinate in 3d t" << endl;
//
//	//variables that represent our x, y, and z coordinates of a, b, c and t
//	int ax, ay, az, bx, by, bz, cx, cy, cz, tx, ty, tz;
//
//	cin >> ax >> ay >> az;
//	cin >> bx >> by >> bz;
//	cin >> cx >> cy >> cz;
//	cin >> tx >> ty >> tz;
//
//	mat3x3 m = mat3x3(ax, bx, cx, ay, by, cy, az, bz, cz);
//	vec3 t = vec3(tx, ty, tz);
//	mat3x3 mm = inverse(m);
//
//	vec3 solutiont = t * mm;
//
//	cout << "solution of barycentric coordinate is: " + to_string(solutiont) << endl;
//
//}
//
//int main() {
//
//
//	vectorf();
//	matrixf();
//	equationf();
//	trianglef();
//
//	return 0;
//}