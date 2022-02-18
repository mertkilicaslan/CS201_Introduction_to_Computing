// mkilicaslan_the6 - Implementation File
#include "favoriteseries.h"

FavoriteSeries::FavoriteSeries(string name, string lastname){
	userName = name;
	userSurname = lastname;
}

string FavoriteSeries::getFullName() const{
	return userName + " " + userSurname;
}

void FavoriteSeries::addSeries(const series & theSerie){
	int prevSize = favSeries.size();
	favSeries.push_back(theSerie);
	int loc = prevSize;

	while((loc > 0) && (favSeries[loc-1].episodes[0].date > theSerie.episodes[0].date)){
		favSeries[loc] = favSeries[loc-1];
		loc--;
	}
	
	favSeries[loc] = theSerie;
}

bool FavoriteSeries::ifExists(int code){
	for(unsigned int i = 0; i < favSeries.size(); i++)
		if(favSeries[i].seriesCode == code)
			return true;
	return false;
}

bool FavoriteSeries::isListEmpty() const{
	return favSeries.size() == 0;
}

void FavoriteSeries::dropSeriesSorted(int code){
	int lastIndex = favSeries.size()-1, codePosition = 0;
	for(unsigned int i = 0; i < favSeries.size(); i++)
		if(favSeries[i].seriesCode == code)
			codePosition = i;

	cout << getFullName() << ", " << favSeries[codePosition].seriesName << " has been dropped from your favorite list!" << endl;

	for(int k = codePosition; k < lastIndex; k++)
		favSeries[k] = favSeries[k+1];
	
	favSeries.pop_back();
}

void FavoriteSeries::displayFavoriteList(const vector<episode> & vec) const{
	cout << "CODE,SERIES,EPISODE,DATE,SLOT" << endl;
	for(unsigned k = 0; k < vec.size(); k++)
		for(unsigned int i = 0; i < favSeries.size(); i++)
			if(vec[k].seriesCode == favSeries[i].seriesCode){
				cout << vec[k].seriesCode << ",";
				cout << favSeries[i].seriesName << ",";
				cout << vec[k].episodeName << ",";
				cout << vec[k].date << ",";
				cout << vec[k].slot << endl;
			}
}

bool FavoriteSeries::isConflict(const series & theSerie) const{
	for(unsigned int i = 0; i < favSeries.size(); i++)
		for(unsigned int j = 0; j < favSeries[i].episodes.size(); j++)
			for(unsigned int k = 0; k < theSerie.episodes.size(); k++)
				if(favSeries[i].episodes[j].date == theSerie.episodes[k].date && favSeries[i].episodes[j].slot == theSerie.episodes[k].slot)
					return true;
	return false;
}

int occurences(const vector<string> & vec, const string & str){
	int occurencess = 0;
	for(unsigned int i = 0; i < vec.size(); i++)
		if(vec.at(i) == str)
			occurencess++;
	return occurencess;
}

void removeFromSortedVec(vector<string> & vec, const int numPos){
	int lastIndex = vec.size()-1;
	for(int k = numPos; k < lastIndex; k++)
		vec[k] = vec[k+1];
	vec.pop_back();
}

void removeFromSortedVec(vector<int> & vec, const int numPos){
	int lastIndex = vec.size()-1;
	for(int k = numPos; k < lastIndex; k++)
		vec[k] = vec[k+1];
	vec.pop_back();
}

void FavoriteSeries::displayFavoriteActors() const{
	vector<int> pointActVec;
	vector<string> complexActVec;

	// Adding to complexActVec vector
	for(unsigned int i = 0; i < favSeries.size(); i++)
		for(unsigned int j = 0; j < favSeries[i].actorNames.size(); j++){
			complexActVec.push_back(favSeries[i].actorNames[j]);
			pointActVec.push_back(1);
		}

	// Increasing points 
	for(unsigned int i = 0; i < complexActVec.size(); i++)
		if(occurences(complexActVec,complexActVec[i]) > 1)
			pointActVec[i] = occurences(complexActVec,complexActVec[i]);
			
	// Sorting by point and than by name 
	int temp;
	string temp2;
	for(unsigned int i = 0; i < pointActVec.size(); i++)
		for(unsigned int j = i+1; j < pointActVec.size(); j++)
			if((pointActVec[j] > pointActVec[i]) || (pointActVec[j] == pointActVec[i] && complexActVec[j] < complexActVec[i])){
				temp2 = complexActVec[i];
				temp = pointActVec[i];

				complexActVec[i] = complexActVec[j];
				pointActVec[i] = pointActVec[j];

				complexActVec[j] = temp2;
				pointActVec[j] = temp;
			}

	// Substracting same actors and their points 
	int temp3 = complexActVec.size();
	while(temp3 > 0){
		for(unsigned int i = 0; i < complexActVec.size(); i++)
			if(occurences(complexActVec,complexActVec[i]) != 1){
				removeFromSortedVec(complexActVec, i);
				removeFromSortedVec(pointActVec, i);
			}
		temp3--;
	}

	// Print process 
	for(unsigned int i = 0; i <  pointActVec.size(); i++)
		cout << complexActVec[i]  << ": " << pointActVec[i] <<  endl;

}