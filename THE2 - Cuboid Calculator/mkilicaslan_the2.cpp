// mkilicaslan_the2
#include "strutils.h"
#include <iomanip>
using namespace std;


bool checkInput(const string & color, double width, double length, double height){
	if((width > 0) & (length > 0) & (height > 0))
		return true;

	cout << "Invalid entry for " << color << " cuboid. Dimensions should be positive real numbers!" << endl;
	return false;
}


void checkCubeandDisplay(string color, double width, double length, double height){
	if ((width == length) & (width == height) & (length == height))
		cout << color << " cuboid is a cube." << endl;
	else
		cout << color << " cuboid is not a cube." << endl;
	cout << endl;
}


void display(const string & color, double area, double volume){
	cout << "Results for the " << color << " cuboid:" << endl;
	cout << "Area: " << area << endl;
	cout << "Volume: " << volume << endl;
}


void calculate(const string & color, double width, double length, double height, double & area, double & volume){
	area = 2 * ((height * width) + (width * length) + (height * length));
	volume = height * width * length;

	display(color, area, volume);
	checkCubeandDisplay(color, width, length, height);
}


string compare(const string & color1, const string & color2, string area_or_volume, double a_v1, double a_v2){
		ToLower(area_or_volume);
		if (a_v1 > a_v2)
			return color1 + " has the largest " + area_or_volume + ".";
		else if (a_v1 < a_v2)
			return color2 + " has the largest " + area_or_volume + ".";
		return "Two cuboids have the same " + area_or_volume + ".";
}



int main(){

	cout.setf(ios::fixed);
	cout.precision(2);

	string color1, color2, c1_check, c2_check;
	double length1,length2,  width1,width2,  height1,height2;
	double area1,area2,  volume1,volume2;

	cout << "Hello! This program compares two cuboids..." << endl;
	cout << "Please enter colors for the two cuboids: ";
	cin >> color1 >> color2;

	c1_check = color1;		
	c2_check = color2;
	ToLower(c1_check);   
	ToLower(c2_check);

	if (c1_check != c2_check){
		cout << "Please enter length, width and height of the " << color1 << " cuboid: ";
		cin >> length1 >> width1 >> height1;

		if (checkInput(color1,width1,length1,height1)){
			cout << "Please enter length, width and height of the " << color2 << " cuboid: ";
			cin >> length2 >> width2 >> height2;

			if (checkInput(color2, width2, length2, height2)){
				calculate(color1, width1, length1, height1, area1, volume1);
				calculate(color2, width2, length2, height2, area2, volume2);

				cout << "Comparison of the two cuboids:" << endl;
				cout << compare(color1, color2, "Volume", volume1, volume2) << endl;
				cout << compare(color1, color2, "Area", area1, area2) << endl;
			}
		}
	}
			
	else
		cout << "Color names cannot be the same, good bye..." << endl;

	return 0;
}