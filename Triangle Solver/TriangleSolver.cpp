/**
* Author:			Alokwe Udueshi Miracle
* Program Name:		Triangle Solver
* Purpose:			A program that takes in user input as a string consisting of
*					the types of data (sides and/or angles) and following it with 
*					the parameters for those sides/angles. It then calculates and
*					outputs the missing sides and/or angles, area, perimeter, type,
*					and class of the triangle. If the triangle isn't possible based
*					on the user's input it tells them that. If the user enters a 
*					quit keyword, the program will stop running.
* Resources used:	https://en.wikipedia.org/wiki/Sum_of_angles_of_a_triangle //#Two_sides_and_non-included_angle_given_(SSA) for SSA
*					https://www.britannica.com/science/Herons-formula
*					https://en.wikipedia.org/wiki/Triangle#Types_of_triangle
*					https://en.wikipedia.org/wiki/Radian#Between_degrees
* Date of start:	Tuesday, January 16, 2024.
* Date of stop:		Saturday, February 4, 2024.
* */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <algorithm> 

#define M_PI 3.14159265358979323846
using namespace std;


// ==== HELPERS ====
/**
* Function Name:	isPossible
* Accepts:			A String stored from user input
* Returns:			A boolean value depending on if the
*					string parameter matches a possible
*					calculation format.
* @Param:			string
*/
bool isPossible(string str) {	
	string possibleScenarios[] = { "SSS", "SAS", "ASA", "SSA" };
	bool isPossible = false;
	for (string s : possibleScenarios) {
		if (s == str) {
			isPossible = true;
		}
	}
	return isPossible;
}
/**
* Function Name:	toUpper
* Accepts:			A string to be modified to uppercase
* Returns:			The same string in uppercase
* @Param:			string
*/
inline string toUpper(string& str) {
	transform(str.begin(), str.end(), str.begin(), toupper);
	return str;
}
/**
* Function Name:	nowExit
* Accepts:			a string to be compared to the exit keywords
* Returns:			a boolean value of true if the entered string 
*					matches an exit keyword and a boolean value of 
*					false if otherwise.
* @Param:			string
*/
bool nowExit(string choice) {
	//Function checks if the user wants to quit.
	choice = toUpper(choice);
	string exitCond[] = {"QUIT", "EXIT", "BYE"};
	for (string s : exitCond) {
		if (choice == s) { return true; }
	}
	return false;
}
/**
* Function Name:	calcArea
* Accepts:			3 double sides to calculate the area of the triangle 
*					using Heron's formula (see line 12).
* Returns:			The area of the triangle from the given sides as a double value.
* @param:			double a, double b, double c
*/
double calcArea(double a, double b, double c) {
	//area using Heron's formula (line 12)
	double s = (a + b + c) / 2.0;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}
/**
* Function Name:	findType
* @param:			double side1, double side2, double side3
* Accepts:			3 double sides to allocate a type based on their lengths.
*					(see line 13)
* Returns:			A string literal with the type of triangle.
*/
string findType(double side1, double side2, double side3)
{
	if (side1 != side2 && side1 != side3 && side2 != side3)
	{
		return "scalene,";
	}
	if(side1 == side2 && side1 == side3 && side2 == side3)
	{
		return "equilateral,";
	}
	return "isosceles,";
}
/**
* Function Name:	findClass
* Accepts:			3 double angles to allocate a class based on the 
*					size of the angles. (see line 13)
* Returns:			A string literal with the class of triangle.
* @param:			double angle1, double angle2, double angle3
*/
string findClass(double angle1, double angle2, double angle3)
{
	if (angle1 < 90 && angle2 < 90 && angle3 < 90)
	{
		return " acute";
	}
	if (angle1 == 90 || angle2 == 90 || angle3 == 90)
	{
		return " right";
	}
	return " obtuse";
}
/**
* Function Name:	printData
* Accepts:			1 string, 3 double side values, and 3 double angle values 
*					to print to the user in a formatted output if it is valid.
* Returns:			void (Nothing).
* @param:			string format, double side1, double side2, double side3, double angle1, double angle2, double angle3
*/
void printData(string format, double side1, double side2, double side3, double angle1, double angle2, double angle3) {
	if ((angle1 + angle2 + angle3) == 180) {  
		cout << fixed << setprecision(3);
		if (format == "prime") {  // this accounts for the SSA double triangle case.
			cout << "--> gamma'" << endl; 
		}
		else {
			cout << "Format: " << setw(10) << left << toUpper(format) << endl;
		}
		cout << "a =   " << setw(8) << left << side1 << "alpha =   " << setw(8) << right << angle1 << endl;
		cout << "b =   " << setw(8) << left << side2 << "beta  =   " << setw(8) << right << angle2 << endl;
		cout << "c =   " << setw(8) << left << side3 << "gamma =   " << setw(8) << right << angle3 << endl;
		cout << "Perimeter = " << setw(8) << right << (side1 + side2 + side3) << endl;
		cout << "Area      = " << setw(8) << right << calcArea(side1, side2, side3) << endl;
		cout << "Type      = " << setw(8) << right << findType(side1, side2, side3) << findClass(angle1, angle2, angle3) << "\n " << endl;
	}
	else {
		cout << "Impossible triangle" << endl;
	}
}
/**
* Function Name:	convertToRadians
* Accepts:			double value in degrees
* Returns:			double value in radians (see line 14)
* @param:			double degree
*/
inline double convertToRadians(double degree) { return degree * (M_PI / 180); }
/**
* Function Name:	convertToDegrees
* Accepts:			double value in radians
* Returns:			double value in degrees (see line 14)
* @param:			double radians
*/
inline double convertToDegrees(double radians){ return radians * (180 / M_PI); }

//============== MAIN ==============

int main(){
	cout << "TriSolver 1.0.0 (c) January 2024, Alokwe Udueshi Miracle\n";
	string input{}, choice{};
	double sideA{ 0.0 }, sideB{ 0.0 }, sideC{ 0.0 };
	double alpha{ 0.0 }, beta{ 0.0 }, gamma{ 0.0 };
	do {
		cout << "\n-> ";
		getline(cin, input); 
		istringstream iss(input);
		iss >> choice;
		choice = toUpper(choice);
		if (nowExit(choice)){ // first check if the user wants to quit the program.
			break;
		}
		if (isPossible(choice) && (iss >> sideA >> sideB >> sideC)){ // Now check if this is a possible calculation.
			if (choice == "SSS") // case SSS, A
			{
				iss >> sideA >> sideB >> sideC;
				sideA = abs(sideA), sideB = abs(sideB), sideC = abs(sideC);		//Make all values absolute before calculations
				alpha = acos((sideB * sideB + sideC * sideC - sideA * sideA) / (2 * sideB * sideC));
				beta = acos((sideC * sideC + sideA * sideA - sideB * sideB) / (2 * sideC * sideA));
				gamma = acos((sideA * sideA + sideB * sideB - sideC * sideC) / (2 * sideA * sideB));
				// convert angles to degrees
				alpha = convertToDegrees(alpha);
				beta = convertToDegrees(beta);
				gamma = convertToDegrees(gamma);
				printData(choice, sideA, sideB, sideC, alpha, beta, gamma);
			}
			else if (choice == "SAS") {
				istringstream issSAS(input);
				issSAS >> choice; // consume the first string in the iss object
				issSAS >> sideA >> gamma >> sideB;
				sideA = abs(sideA), gamma = abs(gamma), sideB = abs(sideB);		//Make all values absolute before use
				gamma = convertToRadians(gamma);
				sideC = sqrt(sideA * sideA + sideB * sideB - (2 * sideA * sideB * cos(gamma)));
				alpha = acos((sideB * sideB + sideC * sideC - sideA * sideA) / (2 * sideB * sideC));
				beta = acos((sideC * sideC + sideA * sideA - sideB * sideB) / (2 * sideC * sideA));
				
				alpha = convertToDegrees(alpha), beta = convertToDegrees(beta), gamma = convertToDegrees(gamma); // 
				printData(choice, sideA, sideB, sideC, alpha, beta, gamma);
			}
			else if (choice == "ASA") {
				istringstream issASA(input);
				issASA >> choice; // see line 261
				issASA >> alpha >> sideA >> beta;
				alpha = abs(alpha), sideA = abs(sideA), beta = abs(beta);
				gamma = 180 - alpha - beta;
				alpha = convertToRadians(alpha);
				beta = convertToRadians(beta);
				gamma = convertToRadians(gamma);
								
				sideB = sideA * (sin(alpha) / sin(gamma));
				sideC = sideA * (sin(beta) / sin(gamma));
				alpha = convertToDegrees(alpha);
				beta = convertToDegrees(beta);
				gamma = convertToDegrees(gamma);
				printData(choice, sideA, sideB, sideC, alpha, beta, gamma);
			}
			else if (choice == "SSA") {
				istringstream issSSA(input);
				issSSA >> choice; 
				issSSA >> sideB >> sideC >> beta;
				sideB = abs(sideB), sideC = abs(sideC), beta = abs(beta);
				beta = convertToRadians(beta);
				double D = (sideC / sideB) * sin(beta); //see line 11
				beta = convertToDegrees(beta);
				 
				if (asin(D) > 1) { cout << "impossible triangle" << endl; }
				else if (asin(D) == 1) { 
					gamma = 90.0; // see line 11
					alpha = 180 - beta - gamma;
					alpha = convertToRadians(alpha), beta = convertToRadians(beta);
					sideA = sideB * (sin(alpha) / sin(beta));
					alpha = convertToDegrees(alpha), beta = convertToDegrees(beta);
					printData(choice, sideA, sideB, sideC, alpha, beta, gamma);
				}
				else if (asin(D) < 1) {
					if (sideB >= sideC) {
						gamma = convertToDegrees(asin(D));
						alpha = 180 - beta - gamma;
						alpha = convertToRadians(alpha), beta = convertToRadians(beta);
						sideA = sideB * (sin(alpha) / sin(beta));
						alpha = convertToDegrees(alpha), beta = convertToDegrees(beta);
						printData(choice, sideA, sideB, sideC, alpha, beta, gamma);
					}
					else {
						gamma = convertToDegrees(asin(D)); 
						alpha = 180 - beta - gamma;
						alpha = convertToRadians(alpha); beta = convertToRadians(beta);
						sideA = sideB * (sin(alpha) / sin(beta));
						alpha = convertToDegrees(alpha), beta = convertToDegrees(beta);
						printData(choice, sideA, sideB, sideC, alpha, beta, gamma);

						double gammaPrime = 180 - gamma;
						alpha = 180 - gammaPrime - beta;
						alpha = convertToRadians(alpha), beta = convertToRadians(beta);
						sideA = sideB * sin(alpha) / sin(beta);
						alpha = convertToDegrees(alpha), beta = convertToDegrees(beta);
						printData("prime", sideA, sideB, sideC, alpha, beta, gammaPrime);
					}
				}
			}
		}
		else { // show user how it should look
			cout << "Bad command : Format # # #\n" <<
				"where Format = SSS | SAS | ASA | SSA\n" <<
				"      # = a real number";
		}
	} while (true);
}