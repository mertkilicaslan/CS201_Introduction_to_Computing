// mkilicaslan_the6 - Main Cpp File
#include "favoriteseries.h"
#include <fstream>
#include <sstream>
using namespace std;

void makeStringUpper(string & str){
	for(unsigned int i = 0; i < str.length(); i++)
		if('a' <= str.at(i) && str.at(i) <= 'z')
			str.at(i) -= 'a'-'A';
}

void displayMenu(void){
	cout << "---" << endl;
	cout << "MENU" << endl;
	cout << "1. Print all TV series" << endl;
	cout << "2. Add TV series" << endl;
	cout << "3. Drop TV series" << endl;
	cout << "4. Print your favorite series with schedule" << endl;
	cout << "5. Print all your favorite actors" << endl;
	cout << "6. Exit" << endl;
	cout << "---" << endl;

}

bool doesCodeExistInData(int code, const vector<series> & vec){
	for(unsigned int i = 0; i < vec.size(); i++)
		if(code == vec[i].seriesCode)
			return true;
	return false;
}


int main(){

	cout << "Welcome to my favorite TV series schedule program!" << endl;
	cout << "Please, enter your name and surname: ";

	string nameLastname, seriesTxtLine, episodesTxtLine;
	ifstream inputSeries, inputEpisodes;
	
	getline(cin, nameLastname);
	makeStringUpper(nameLastname);
	string name = nameLastname.substr(0,nameLastname.find(" "));
	string lastname = nameLastname.substr(nameLastname.find(" ")+1);

	string seriestxt = "series.txt";
	inputSeries.open(seriestxt.c_str());
	string episodetxt = "episodes.txt";
	inputEpisodes.open(episodetxt.c_str());


	// Series.txt to vecOfSeries process 
	vector<series> vecOfSeries;
	string actorsAndSerieWord, serie, actor;
	int code;

	while(getline(inputSeries, seriesTxtLine)){
		series tempSerie;
		string actorsAndSerie;

		istringstream lineStream(seriesTxtLine);
		lineStream >> code;
		tempSerie.seriesCode = code;

		while(lineStream >> actorsAndSerieWord)
			 actorsAndSerie += " " + actorsAndSerieWord;

		actorsAndSerie = actorsAndSerie.substr(1);
		makeStringUpper(actorsAndSerie);

		serie = actorsAndSerie.substr(0,actorsAndSerie.find(";"));
		actorsAndSerie = actorsAndSerie.substr((serie.length())+2);
		tempSerie.seriesName = serie;

		// Actor names process 
		int startingIndex = 0, searchPosition = actorsAndSerie.find(", ");
		while(searchPosition != string::npos){
			actor = actorsAndSerie.substr(startingIndex,searchPosition-startingIndex);
			tempSerie.actorNames.push_back(actor);
			startingIndex = searchPosition+2;
			searchPosition = actorsAndSerie.find(", ",startingIndex);
		}

		tempSerie.actorNames.push_back(actorsAndSerie.substr(actorsAndSerie.rfind(", ")+2));
		vecOfSeries.push_back(tempSerie);
	}


	// Episodes.txt to vecOfEpisodes process 
	vector<episode> vecOfEpisodes;
	string time, slot, episodeWord;
	int code2;

	while(getline(inputEpisodes, episodesTxtLine)){
		episode tempEpisode;

		istringstream lineStream2(episodesTxtLine);
		lineStream2 >> code2 >> time >> slot;
		tempEpisode.seriesCode = code2;

		makeStringUpper(slot);
		tempEpisode.slot = slot;

		string strMonth = time.substr(0,time.find("/"));
		string strDay = time.substr(time.find("/")+1,(time.rfind("/")-time.find("/")-1));
		string strYear = time.substr(time.rfind("/")+1);

		int month = stoi(strMonth);
		int day = stoi(strDay);
		int year = stoi(strYear);
		tempEpisode.date = Date(month, day, year);
			
		string theEpisode;
		while(lineStream2 >> episodeWord)
			theEpisode += " " + episodeWord;

		theEpisode = theEpisode.substr(1);
		makeStringUpper(theEpisode);
		tempEpisode.episodeName = theEpisode;

		vecOfEpisodes.push_back(tempEpisode);
	}

	inputSeries.close();
	inputEpisodes.close();


	// Sorting vecOfEpisodes by previous date, then slot and the code 
	episode temp;
	for(unsigned int i = 0; i < vecOfEpisodes.size(); i++)
		for(unsigned int j = i+1; j < vecOfEpisodes.size(); j++)
			if((vecOfEpisodes[i].date > vecOfEpisodes[j].date) || 
				((vecOfEpisodes[i].date == vecOfEpisodes[j].date) && (vecOfEpisodes[i].slot == "NIGHT" && vecOfEpisodes[j].slot != "NIGHT")) ||
				((vecOfEpisodes[i].date == vecOfEpisodes[j].date) && (vecOfEpisodes[i].slot == "EVENING" && (vecOfEpisodes[j].slot == "MORNING" || vecOfEpisodes[j].slot == "AFTERNOON"))) ||
				((vecOfEpisodes[i].date == vecOfEpisodes[j].date) && (vecOfEpisodes[i].slot == "AFTERNOON" && vecOfEpisodes[j].slot == "MORNING"))	||
				((vecOfEpisodes[i].date == vecOfEpisodes[j].date && vecOfEpisodes[i].slot == vecOfEpisodes[j].slot) && (vecOfEpisodes[i].seriesCode > vecOfEpisodes[j].seriesCode))){

				temp = vecOfEpisodes[i];
				vecOfEpisodes[i] = vecOfEpisodes[j];
				vecOfEpisodes[j] = temp;
			}


	// Adding vecOfEpisodes to the vecOfSeries
	for(unsigned int i = 0; i < vecOfSeries.size(); i++)
		for(unsigned k = 0; k < vecOfEpisodes.size(); k++)
			if(vecOfEpisodes[k].seriesCode == vecOfSeries[i].seriesCode)
				vecOfSeries[i].episodes.push_back(vecOfEpisodes[k]);
				

	/* CHOICE AND PRINT PROCESSING */
	FavoriteSeries theObj(name,lastname);
	while(true){
		int choice = 0;
		displayMenu();

		cout << "Please enter your choice: ";
		cin >> choice;

		// CHOICE = INVALID 
		if(!(1 <= choice && choice <= 6)){
			cout << "Invalid option!" << endl;
			cin.clear();
			cin.ignore(1000,'\n');
			continue;
		}

		// CHOICE = 1
		if(choice == 1){
			cout << "CODE,SERIES,EPISODE,DATE,SLOT" << endl;
			for(unsigned int i = 0; i < vecOfEpisodes.size(); i++){
				cout << vecOfEpisodes[i].seriesCode << ",";
				for(unsigned int j = 0; j < vecOfSeries.size(); j++)
					if(vecOfSeries[j].seriesCode == vecOfEpisodes[i].seriesCode)
						cout << vecOfSeries[j].seriesName << ",";

				cout << vecOfEpisodes[i].episodeName << ",";
				cout << vecOfEpisodes[i].date << ",";
				cout << vecOfEpisodes[i].slot << endl;
			}
		}

		// CHOICE = 2
		else if(choice == 2){
			int theCode = 0;
			bool state = false;
			cout << "Enter code for the TV series you want to add: ";
			cin >> theCode;

			// Does not exist in database
			if(!(doesCodeExistInData(theCode, vecOfSeries))){
				cout << theObj.getFullName() << ", there is no such TV series in the database!" << endl;
				continue;
			}

			// Code already exists in fav list
			if(theObj.ifExists(theCode)){
				cout << theObj.getFullName() << ", you can't add this TV series because you already added it!" << endl;
				continue;
			}

			// Time conflict
			for(unsigned int i = 0; i < vecOfSeries.size(); i++)
				if(vecOfSeries[i].seriesCode == theCode)
					if(theObj.isConflict(vecOfSeries[i])){
						cout << theObj.getFullName() << ", you can't add this TV series because of a date and slot conflict!" << endl;
						state = true;
					}
			if(state == true)
				continue;

			// Adding to list process 
			else
				for(unsigned int i = 0; i < vecOfSeries.size(); i++)
					if(theCode == vecOfSeries[i].seriesCode){
						theObj.addSeries(vecOfSeries[i]);
						cout << theObj.getFullName() << ", " << vecOfSeries[i].seriesName << " added to your schedule." << endl;
					}
		}

		// CHOICE = 3
		else if(choice == 3){
			if(theObj.isListEmpty()){
				cout << theObj.getFullName() << ", you did not add any TV series yet!" << endl;
				continue;
			}

			int theCode = 0;
			cout << "Enter code for the TV series you want to drop: ";
			cin >> theCode;

			if(!(theObj.ifExists(theCode)))
				cout << theObj.getFullName() << ", there is no such TV series in your favorite list!" << endl;
			else
				theObj.dropSeriesSorted(theCode);
		}

		// CHOICE = 4
		else if(choice == 4){
			if(theObj.isListEmpty()){
				cout << theObj.getFullName() << ", you did not add any TV series yet!" << endl;
				continue;
			}

			cout << theObj.getFullName() << ", here is your favorite TV series:" << endl;
			theObj.displayFavoriteList(vecOfEpisodes);
		}

		// CHOICE = 5
		else if(choice == 5){
			if(theObj.isListEmpty()){
				cout << theObj.getFullName() << ", you did not add any TV series yet!" << endl;
				continue;
			}

			cout << theObj.getFullName() << ", here is your favorite actors:" << endl;
			theObj.displayFavoriteActors();
			
		}

		// CHOICE = 6
		else if(choice == 6){
			cout << "Goodbye, " << theObj.getFullName() << "!" << endl;
			break;
		}	
	}
	return 0;
}
