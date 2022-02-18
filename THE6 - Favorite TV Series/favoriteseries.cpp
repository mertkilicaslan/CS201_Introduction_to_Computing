/* mkilicaslan_the6 */
#include "favoriteseries.h"

FavoriteSeries::FavoriteSeries(string name, string lastname){
	userName = name;
	userSurname = lastname;
}

string FavoriteSeries::getFullName() const{
	return userName + " " + userSurname;
}

void FavoriteSeries::addSeries(const series & series_object){
	int before_size = favSeries.size();
	favSeries.push_back(series_object);
	int loc = before_size;

	while((loc > 0) && (favSeries[loc-1].episodes[0].date > series_object.episodes[0].date)){
		favSeries[loc] = favSeries[loc-1];
		loc--;}
	
	favSeries[loc] = series_object;
}

bool FavoriteSeries::ifExists(int code){
	for(unsigned int i = 0; i < favSeries.size(); i++)
		if(favSeries[i].seriesCode == code)
			return true;
	return false;
}

bool FavoriteSeries::isListEmpty() const{
	if(favSeries.size() == 0)
		return true;
	return false;
}

void FavoriteSeries::dropSeriesSorted(int code){
	int lastindex = favSeries.size()-1;
	int code_position = 0;

	for(unsigned int i = 0; i < favSeries.size(); i++)
		if(favSeries[i].seriesCode == code)
			code_position = i;

	cout << getFullName() << ", " << favSeries[code_position].seriesName << " has been dropped from your favorite list!" << endl;

	for(int k = code_position; k < lastindex; k++)
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

bool FavoriteSeries::isConflict(const series & series_object) const{
	for(unsigned int i = 0; i < favSeries.size(); i++)
		for(unsigned int j = 0; j < favSeries[i].episodes.size(); j++)
			for(unsigned int k = 0; k < series_object.episodes.size(); k++)
				if(favSeries[i].episodes[j].date == series_object.episodes[k].date &&
					favSeries[i].episodes[j].slot == series_object.episodes[k].slot)
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

void remove_from_sortedV_index_str(vector<string> & vec, const int num_pos){
	int lastIndex = vec.size()-1;
	for(int k = num_pos; k < lastIndex; k++)
		vec[k] = vec[k+1];
	vec.pop_back();
}

void remove_from_sortedV_index_int(vector<int> & vec, const int num_pos){
	int lastIndex = vec.size()-1;
	for(int k = num_pos; k < lastIndex; k++)
		vec[k] = vec[k+1];
	vec.pop_back();
}

void FavoriteSeries::displayFavoriteActors() const{

	vector<int> point_act_vec;
	vector<string> complex_actor_vec;

	/* Adding to complex_actor_vec vector */
	for(unsigned int i = 0; i < favSeries.size(); i++)
		for(unsigned int j = 0; j < favSeries[i].actorNames.size(); j++){
			complex_actor_vec.push_back(favSeries[i].actorNames[j]);
			point_act_vec.push_back(1);}



	/* Increasing points */
	for(unsigned int i = 0; i < complex_actor_vec.size(); i++)
		if(occurences(complex_actor_vec,complex_actor_vec[i]) > 1)
			point_act_vec[i] = occurences(complex_actor_vec,complex_actor_vec[i]);
			


	/* Sorting by point and than by name */
	int temp;
	string temp2;
	for(unsigned int i = 0; i < point_act_vec.size(); i++)
		for(unsigned int j = i+1; j < point_act_vec.size(); j++)
			if((point_act_vec[j] > point_act_vec[i]) || (point_act_vec[j] == point_act_vec[i] && complex_actor_vec[j] < complex_actor_vec[i])){

				temp2 = complex_actor_vec[i];
				temp = point_act_vec[i];

				complex_actor_vec[i] = complex_actor_vec[j];
				point_act_vec[i] = point_act_vec[j];

				complex_actor_vec[j] = temp2;
				point_act_vec[j] = temp;}



	/* Substracting same actors and their points */
	int temp3 = complex_actor_vec.size();
	while(temp3 > 0){
		for(unsigned int i = 0; i < complex_actor_vec.size(); i++)
			if(occurences(complex_actor_vec,complex_actor_vec[i]) != 1){
				remove_from_sortedV_index_str(complex_actor_vec,i);
				remove_from_sortedV_index_int(point_act_vec,i);}
			temp3--;}



	/* Print process */
	for(unsigned int i = 0; i <  point_act_vec.size(); i++)
		cout << complex_actor_vec[i]  << ": " << point_act_vec[i] <<  endl;
	

}