#include<glm/mat3x3.hpp>
#include<glm/vec3.hpp>
#include<glm/geometric.hpp>
#include<iostream>
#include<glm/gtc/type_ptr.hpp>
#include<iomanip>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
using namespace std;
using namespace glm;

void vectorF() {

	vec3 v1_1 = vec3(2, 3, -4);
	vec3 v1_2 = vec3(-1, 4, -1);
	vec3 v1 = v1_1 + v1_2;

	int s = dot(v1_1, v1_2);

	vec3 temp = vec3(2, 2, 4);
	vec3 v2 = cross(v1, temp);

	vec3 v3 = normalize(v2);
	vec3 v4 = -v2;
}

void matrixF() {

	mat3x3 M1_1 = mat3x3(1, 2, 3,
		2, 1, 3,
		4, 5, 1);

	mat3x3 tempM = mat3x3(-1, 2, -3,
		5, -2, 7,
		-4, -1, 3);

	mat3x3 M1 = M1_1 + tempM;

	mat3x3 M2_1 = mat3x3(1, 2, 3,
		2, 1, 3,
		4, 5, 1);

	mat3x3 M2 = transpose(tempM) * M2_1;
	mat3x3 M3 = inverse(tempM) * M2_1;

	cout << to_string(M1) << endl;
	cout << to_string(M2) << endl;
	cout << to_string(M3) << endl;
}

void equationF() {

	//variables that represent our equations, x, y, z and the result r
	float x1, y1, z1, r1;
	float x2, y2, z2, r2;
	float x3, y3, z3, r3;

	cout << "Write x, y, z variables and the result" << endl;
	cin >> x1 >> y1 >> z1 >> r1;
	cout << "Write x, y, z variables and the result" << endl;
	cin >> x2 >> y2 >> z2 >> r2;
	cout << "Write x, y, z variables and the result" << endl;
	cin >> x3 >> y3 >> z3 >> r3;

	cout << "Equation looks like this: " + to_string(x1) + "x " + to_string(y1) + "y " + to_string(z1) + "z " << endl;
	cout << "Equation looks like this: " + to_string(x2) + "x " + to_string(y2) + "y " + to_string(z2) + "z " << endl;
	cout << "Equation looks like this: " + to_string(x3) + "x " + to_string(y3) + "y " + to_string(z3) + "z " << endl;

	//defines a matrix with x, y and z variables
	mat3x3 M = mat3x3(x1, y1, z1, x2, y2, z2, x3, y3, z3);

	//defines a vector with the results to equations 
	vec3 MM = vec3(r1, r2, r3); 

	//inverts the matrix
	mat3x3 M1 = inverse(M);
	
	//vector that represents our solutions x, y, z
	vec3 solution = MM * M1;
	cout << to_string(solution) + " This is the solution to equations" << endl;

}

void triangleF() {


	cout << "Put in coordinates A, B, C and an coordinate in 3D T" << endl;
	
	//variables that represent our x, y, and z coordinates of A, B, C and T
	int Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz, Tx, Ty, Tz;

	cin >> Ax >> Ay >> Az;
	cin >> Bx >> By >> Bz;
	cin >> Cx >> Cy >> Cz;
	cin >> Tx >> Ty >> Tz;

	mat3x3 M = mat3x3(Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz);
	vec3 T = vec3(Tx, Ty, Tz);

	vec3 solutionT = M * T ;

	cout << "Solution of Barycentric coordinate is: " + to_string(solutionT) <<endl;

}

int main() {

	
	vectorF();
	matrixF();
	equationF();
	triangleF();

	return 0;
}
