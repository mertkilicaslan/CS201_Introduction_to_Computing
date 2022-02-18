// mkilicaslan_the6 - Header File
#ifndef FAVORITESERIES_H
#define FAVORITESERIES_H

#include <vector>
#include "date.h"
using namespace std;

struct episode {
	string episodeName;
	int seriesCode;
	Date date;
	string slot;
};

struct series{
    string seriesName;
    int seriesCode;
    vector<episode> episodes;
	vector<string> actorNames;
};


class FavoriteSeries{
	public:
		FavoriteSeries(string, string);								// Parameter Constructor
    
		string getFullName() const;									// Returns the full name (name&surname) of the user 
		void addSeries(const series &);								// Adds TV series to the favorite list
		bool ifExists(int seriesCode);								// Checks if the serie in the favorite list or not
		bool isListEmpty() const;									// Returns true if the favorite list is empty
		void dropSeriesSorted(int);									// Drops the TV series with the given TV serie code from the vector (favSeries) while keeping the vector sorted
																
		void displayFavoriteList(const vector<episode> &) const;	// Displays the favorite TV series list
		void displayFavoriteActors() const;							// Calculates and displays the sorted favorite actors list
		bool isConflict(const series &) const;						// Returns true if a given TV serie has a time conflict with an another serie from the user's schedule
																
						// Time conflict means same date and same time slot among (morning, afternoon, evening, night)
		
	private:
		string userName;
		string userSurname;
		vector<series> favSeries;
};

#endif