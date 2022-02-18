/*	mkilicaslan_the1  */
#include <iostream>
#include <string>
using namespace std;

int main(void){

	string studentName, courseName, isFirstYear, wantChangeGrade, prevGrade, currentGrade, chooseGrade;

	cout << "Welcome to the Fall 2020-2021 Semester grading system. What is your name? ";
	cin >> studentName;

	cout << "Hello " << studentName << "! Please enter the name of the course to be processed: ";
	cin >> courseName;

	cout << "Hello " << studentName << "! If you take the " << courseName << " for the first time, enter YES otherwise NO: ";
	cin >> isFirstYear;


	/* First Year */
	if (isFirstYear == "YES") {
		cout << "What is your grade from (A,B,C,D,F)? ";
		cin >> currentGrade;
		
		if (currentGrade == "A" || currentGrade == "B" || currentGrade == "C" || currentGrade == "D"){
			cout << "Do you want to switch your grade from " << currentGrade << " to S (YES or NO)? ";
			cin >> wantChangeGrade;
			
			if (wantChangeGrade == "YES")
				cout << studentName << ", your final grade for " << courseName << " is S. Goodbye..." << endl;
			else if (wantChangeGrade == "NO")
				cout << studentName << ", your final grade for " << courseName << " is " << currentGrade << ". Goodbye..." << endl;
			else
				cout << "Invalid grade selection. Goodbye..." << endl;
		}
			
		else if (currentGrade == "F"){
			cout << "Do you want to switch your grade from F to U (YES or NO)? ";
			cin >> wantChangeGrade;
			
			if (wantChangeGrade == "YES")
				cout << studentName << ", your final grade for " << courseName << " is U. Goodbye..." << endl;
			else if (wantChangeGrade == "NO")
				cout << studentName << ", your final grade for " << courseName << " is F. Goodbye..." << endl;
			else
				cout << "Invalid grade selection. Goodbye..." << endl;
		}
			
		else
			cout << "Invalid grade selection. Goodbye..." << endl;
	}


	/* Second Year */
	else if (isFirstYear == "NO"){
		cout << "Please enter your previous grade from (A,B,C,D,F,S,U): ";
		cin >> prevGrade;

		if (prevGrade == "A" || prevGrade == "B" || prevGrade == "C" || prevGrade == "D" || prevGrade == "F" || prevGrade == "S" || prevGrade == "U"){
			cout << "Please enter your current grade from (A,B,C,D,F): ";
			cin  >> currentGrade;

			if (currentGrade == "A" || currentGrade == "B" || currentGrade == "C" || currentGrade == "D" || currentGrade == "F"){
				cout << "Please enter the grade you want to choose from (A,B,C,D,F,S,U): ";
				cin >> chooseGrade;

				if (chooseGrade == "A" || chooseGrade == "B" || chooseGrade == "C" || chooseGrade == "D" || chooseGrade == "F" || chooseGrade == "S" || chooseGrade == "U"){

					if (prevGrade == "A" || prevGrade == "B" ||prevGrade == "C" || prevGrade == "D"){
						if ((chooseGrade == "S" && currentGrade != "F") || chooseGrade == currentGrade || (chooseGrade == "U" && currentGrade == "F"))
							cout << studentName << ", your final grade for " << courseName << " is " << chooseGrade << ". Goodbye..." << endl;
						else
							cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
					}

					else if (prevGrade == "U"){
						if (chooseGrade == "S" || chooseGrade == currentGrade || (chooseGrade == "U" && currentGrade == "F"))
							cout << studentName << ", your final grade for " << courseName << " is " << chooseGrade << ". Goodbye..." << endl;
						else
							cout << "Invalid grade selection. If you received U before, you may choose S or current letter grade." << endl;					}					else if (prevGrade == "S"){						if ((chooseGrade == "S" && currentGrade != "F") || chooseGrade == currentGrade)
							cout << studentName << ", your final grade for " << courseName << " is " << chooseGrade << ". Goodbye..." << endl;						else if (currentGrade == "F" && chooseGrade != "F")							cout << "Invalid grade selection. If you received S before and fail this semester, you get F." << endl;						else							cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;					}					else if (prevGrade == "F"){						if ((chooseGrade == "S" && currentGrade != "F") || chooseGrade == currentGrade)							cout << studentName << ", your final grade for " << courseName << " is " << chooseGrade << ". Goodbye..." << endl;						else if (currentGrade == "F" && chooseGrade != "F")							cout << "Invalid grade selection. If you received F before, and fail this semester, you get F." << endl;						else							cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;					}				}				else					cout << "Invalid grade selection. Goodbye..." << endl;			}			else				cout << "Invalid grade selection. Goodbye..." << endl;
		}

		else
			cout << "Invalid grade selection. Goodbye..." << endl;
	}

	return 0;
}
