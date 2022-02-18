// mkilicaslan_the4
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

void makeStrLower(string & str){
	for(unsigned int i = 0; i < str.length(); i++)
		if('A' <= str.at(i) && str.at(i) <= 'Z')
			str.at(i) += 'a'-'A';
}

int main(){

	string fileName1, fileName2, wordPool, wordMain;
	ifstream inputPool, inputMain;

	// Word pool check
	cout << "Please enter a filename for the word pool: ";
	cin >> fileName1;
	inputPool.open(fileName1.c_str());

	while(inputPool.fail()){
		cout << "Cannot open the word pool file." << endl;
		cout << "Please enter a filename for the word pool: ";
		cin >> fileName1;
		inputPool.open(fileName1.c_str());
	}

	// Main text check
	cout << "Please enter a filename for the main text: ";
	cin >> fileName2;
	inputMain.open(fileName2.c_str());

	while(inputMain.fail()){
		cout << "Cannot open the main text file." << endl;
		cout << "Please enter a filename for the main text: ";
		cin >> fileName2;
		inputMain.open(fileName2.c_str());
	}


	// File to string coversion with lower cases
	cout << "You may find the results below:" << endl << endl;
	string lineMain;

	while(getline(inputMain, lineMain)){
		istringstream lineStream(lineMain);
		string display;

		while(lineStream >> wordMain){
			vector<string> similars;
			vector<int> similarsCount;
			string same;

			while(inputPool >> wordPool){
				makeStrLower(wordMain); 
				makeStrLower(wordPool);
				unsigned int count = 0;

				if(wordMain == wordPool)
					same = wordMain;

				else if((same.length() == 0) && (wordMain.length() == wordPool.length())){
					for(unsigned int i = 0; i < wordMain.length(); i++)
						if(wordMain.at(i) == wordPool.at(i))
							count++;

					if(count >= double(wordMain.length())/2){
						similarsCount.push_back(count);
						similars.push_back(wordPool);
					}
				}
			}


			// Send words to display
			if((similars.size() != 0) && (same.length() == 0)){
				int counter = 0, maxElement = 0, maxElementIndex = 0;

				for(unsigned int i = 0; i < similarsCount.size(); i++)
					if(similarsCount[i] > maxElement){
						maxElement = similarsCount[i];
						maxElementIndex = i;
					}
				
				for(unsigned int i = 0; i < similarsCount.size(); i++)
					if(similarsCount[i] == maxElement)
						counter++;
				
				if(counter == 1)
					display+= similars[maxElementIndex] + " ";

				else if(counter > 1){
					display += "(";
					for(unsigned int i = 0; i < similarsCount.size(); i++)
						if(similarsCount[i] == similarsCount[maxElementIndex])
							display+= similars[i] + ",";
					
					display = display.substr(0, display.rfind(","));
					display += ") ";
				}
			}

			else if((similars.size() == 0) && (same.length()) == 0)
				display += "{" + wordMain + "} ";
			else
				display += same + " ";

			inputPool.clear();
			inputPool.seekg(0);
		}

		cout << display.substr(0, display.rfind(" ")) << endl;
	}


	inputPool.close();
	inputMain.close();

	return 0;
}