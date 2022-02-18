// mkilicaslan_the5
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Function overloading
int findIndexInVector(const vector<string> & vec, const string & str){
	for(unsigned int i = 0; i < vec.size(); i++)
		if(str == vec.at(i))
			return i;
	return -1;
}

// Function overloading
int findIndexInVector(const vector<int> & vec, const int & num){
	for(unsigned int i = 0; i < vec.size(); i++)
		if(num == vec.at(i))
			return i;
	return -1;
}

bool doesExistInString(const vector <string> & vec, const string & str){
	for(unsigned int i = 0; i < vec.size(); i++)
		if(vec.at(i) == str)
			return true;
	return false;
}

void makeStringUpper(string & str){
	for(unsigned int i = 0; i < str.length(); i++)
		if('a' <= str.at(i) && str.at(i) <= 'z')
			str.at(i) -= 'a'-'A';
}

void displayMenu(void){
	cout << "---" << endl;
	cout << "MENU" << endl;
	cout << "1. Print the series" << endl;
	cout << "2. Search the series according to the rating" << endl;
	cout << "3. Add the series to the favorite list" << endl;
	cout << "4. Print the favorite list" << endl;
	cout << "5. Exit" << endl;
	cout << "---" << endl;
}



int main(){
	cout << "Welcome to Netflix TV Series Ratings Calculator!" << endl;

	string actorsSeriesFile, ratingFile, ratingLine, actorsSeriesLine;
	ifstream actorsSeriesInput, ratingInput;

	cout << "Please enter a filename for Series-Actor file: ";
	cin >> actorsSeriesFile;
	actorsSeriesInput.open(actorsSeriesFile.c_str());
	while(actorsSeriesInput.fail()){
		cout << "Can not find the specified file." << endl;
		cout << "Please enter a filename for Series-Actor file: ";
		cin >> actorsSeriesFile;
		actorsSeriesInput.open(actorsSeriesFile.c_str());
	}


	cout << "Please enter a filename for Rating file: ";
	cin >> ratingFile;
	ratingInput.open(ratingFile.c_str());
	while(ratingInput.fail()){
		cout << "Can not find the specified file." << endl;
		cout << "Please enter a filename for Rating file: ";
		cin >> ratingFile;
		ratingInput.open(ratingFile.c_str());
	}



	/* FILE TO VECTOR PROCESSING */
	// Ratings text opening
	double rate; 
	string seriesWord;
	vector<string> seriesVec;
	vector<double> rateVec;
	vector<int> occurences;

	while(getline(ratingInput, ratingLine)){
		string series;
		istringstream lineStream(ratingLine);
		lineStream >> rate;

		while(lineStream >> seriesWord)
			series += " " + seriesWord;

		series = series.substr(1); 
		makeStringUpper(series);

		if(doesExistInString(seriesVec, series) == false){
			seriesVec.push_back(series);
			rateVec.push_back(rate);
			occurences.push_back(1);
		}

		else if(doesExistInString(seriesVec, series) == true){
			occurences.at(findIndexInVector(seriesVec, series)) += 1;
			rateVec.at(findIndexInVector(seriesVec, series)) += rate;
		}
	}


	// Rating text multiple occurence handling
	for(int unsigned i = 0; i < occurences.size(); i++)
		if(occurences.at(i) > 1)
			rateVec.at(i) /= occurences.at(i);

	// Sorting rating text - Handling same rate series alphabetically
	double temp;
	string temp2;
	for(unsigned int i = 0; i < rateVec.size(); i++)
		for(unsigned int j = i+1; j < rateVec.size(); j++)
			if ((rateVec[i] < rateVec[j]) || ((rateVec[i] == rateVec[j]) && (seriesVec[i] > seriesVec[j]))){			
				temp = rateVec[i];
				temp2 = seriesVec[i];

				rateVec[i] = rateVec[j];
				seriesVec[i] = seriesVec[j];

				seriesVec[j] = temp2;
				rateVec[j] = temp;
			}

	// Actors-series text opening
	string actorsAndSeriesWord, actors, seriesInActorsFile;
	vector<string> actorsVec(seriesVec.size(), "");

	while(getline(actorsSeriesInput, actorsSeriesLine)){
		string actorsAndSeries;
		istringstream lineStream2(actorsSeriesLine);

		while(lineStream2 >> actorsAndSeriesWord)
			actorsAndSeries += " " + actorsAndSeriesWord;

		actorsAndSeries = actorsAndSeries.substr(1); 
		makeStringUpper(actorsAndSeries);

		actors = actorsAndSeries.substr(0, actorsAndSeries.find(";"));
		seriesInActorsFile = actorsAndSeries.substr(actors.length()+2);
			
		// Adding actors to vector acording to the order of series
		for(unsigned int i = 0; i < seriesVec.size(); i++)
			if(seriesInActorsFile == seriesVec.at(i))
				actorsVec.at(i) = actors;
	}

	ratingInput.close();
	actorsSeriesInput.close();


	/* CHOICE AND PRINT PROCESSING */
	vector<string> favouriteSeriesVec;
	vector<string> favouriteActorVec;
	vector<double> favouriteRateVec;

	while(true){
		int choice = 0;
		displayMenu();
		cout << "Enter your choice: ";
		cin >> choice;
		cout << "---" << endl;
		

		// CHOICE = Invalid
		if(!(choice == 1 || choice == 2 ||choice == 3 || choice == 4 || choice == 5)){
			cout << "This is not a valid option!" << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
			
		// CHOICE = 1
		else if(choice == 1){
			cout << "RANK,NAME,ACTOR,POINTS" << endl;
			for(unsigned int i = 0; i < seriesVec.size(); i++)
				cout << i+1 << "," << seriesVec.at(i) << "," << actorsVec.at(i) << "," << rateVec.at(i) << endl;
		}

		// CHOICE = 2
		else if(choice == 2){
			double ratingMin = -1;
			cout << "Please enter the minimum rating: ";
			cin >> ratingMin;

			if(!(0 <= ratingMin && ratingMin <= 10)){
				cout << "This is not a valid rating!" << endl;
				cin.clear();
				cin.ignore(1000,'\n');
			}
				
			else{
				cout << "RANK,NAME,ACTOR,POINTS" << endl;
				for(unsigned int i = 0; i < seriesVec.size(); i++)
					if(rateVec.at(i) >= ratingMin)
						cout << i+1 << "," << seriesVec.at(i) << "," << actorsVec.at(i) << "," << rateVec.at(i) << endl;
			}
		}

		// CHOICE = 3
		else if(choice == 3){
			string favouriteSerie;
			cout << "Please enter the name of series: ";
			cin.ignore();
			getline(cin, favouriteSerie);
			makeStringUpper(favouriteSerie);

			if(doesExistInString(seriesVec, favouriteSerie) == false){
				cout << "There is no such TV series!" << endl;
				continue;
			}

			else if(doesExistInString(favouriteSeriesVec, favouriteSerie) == true){
				cout << "Your favorite list already have " << favouriteSerie << endl;
				continue;
			}

			else{
				int tempIndex = findIndexInVector(seriesVec, favouriteSerie);
				favouriteSeriesVec.push_back(seriesVec.at(tempIndex));
				favouriteActorVec.push_back(actorsVec.at(tempIndex));
				favouriteRateVec.push_back(rateVec.at(tempIndex));
				continue;
			}
		}
		
		// CHOICE = 4
		else if(choice == 4){
			if(favouriteSeriesVec.size() == 0){
				cout << "Your favorite list is currently empty!" << endl;
				continue;
			}

			else{
				double temp;
				string temp2,temp3;
				for(unsigned int i = 0; i < favouriteRateVec.size(); i++)
					for(unsigned int j = i+1; j < favouriteRateVec.size(); j++)
						if ((favouriteRateVec[i] < favouriteRateVec[j]) || ((favouriteRateVec[i] == favouriteRateVec[j]) && (favouriteRateVec[i] > favouriteRateVec[j]))){
							temp = favouriteRateVec[i];
							temp2 = favouriteSeriesVec[i];
							temp3 = favouriteActorVec[i];

							favouriteRateVec[i] = favouriteRateVec[j];
							favouriteSeriesVec[i] = favouriteSeriesVec[j];
							favouriteActorVec[i] = favouriteActorVec[j];

							favouriteRateVec[j] = temp;
							favouriteSeriesVec[j] = temp2;
							favouriteActorVec[j] = temp3;
						}

				cout << "RANK,NAME,ACTOR,POINTS" << endl;
				for(unsigned int i = 0; i < favouriteSeriesVec.size(); i++)
					cout << i+1 << "," << favouriteSeriesVec.at(i) << "," << favouriteActorVec.at(i) << "," << favouriteRateVec.at(i) << endl;
			}
		}

		// CHOICE = 5
		else if(choice == 5)
			break;
	}

	return 0;
}