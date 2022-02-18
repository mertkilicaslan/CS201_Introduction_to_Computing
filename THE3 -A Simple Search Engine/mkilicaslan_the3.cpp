// mkilicaslan_the3
#include <iostream>
#include <string>
using namespace std;

string getMainSource(string sourceRaw){
	string source;
	bool condition = true;

	while (condition && cin >> sourceRaw){
		if (sourceRaw == "END" || sourceRaw == "end")
			condition = false;
		else if (condition = true)
			source += sourceRaw + " ";
	}

	return source.substr(0, source.length() -1);
}

bool checkSourceInput(const string & sourceRaw){
	bool condition = false;

	for(unsigned int i = 0; i < sourceRaw.length(); ++i)
		if ((sourceRaw.at(i) <= 31) || (33 <= sourceRaw.at(i) && sourceRaw.at(i) <= 47) || (58 <= sourceRaw.at(i) && sourceRaw.at(i) <= 64) ||
			(91 <= sourceRaw.at(i) && sourceRaw.at(i) <= 96) ||(123 <= sourceRaw.at(i) && sourceRaw.at(i) <= 127))
				condition = true;
	
	return condition;
}


int main(){

	// Source string
	string sourceRaw, source, search;

	cout << "Enter source string: ";
	source = getMainSource(sourceRaw);

	while (checkSourceInput(source)){
		cout << "Enter source string: ";
		source = getMainSource(sourceRaw);
	} 
	
	source = " " + source + " "; // Add a space to avoid errors


	// Search string
	cout << "Enter search string: ";
	cin >> search;

	while(search != "quit" && search != "QUIT"){
		string searchLastString = search.substr(search.length()-1);
		
		if((search.length() < 2) || (searchLastString != "+" && searchLastString != "." && searchLastString != "*")){
			cout << "Enter search string: ";
			cin >> search;
			continue;
		}

		// Index checking calculations
		string searchLast2String = search.substr(search.length()-2);
		string searchWithoutSign = search.substr(0,search.length()-1);
		string searchWithoutLast2Signs = search.substr(0,search.length()-2);

		// "+"
		if (searchLastString == "+"){ 
			int searchPosition = source.find(searchWithoutSign);
			
			while(searchPosition != string::npos){
				if(source.at(searchPosition-1) == ' '){
					int postSpaceIndex = source.find(" ",searchPosition);
					cout << "index: " << searchPosition-1 << " word: " << source.substr(searchPosition,(postSpaceIndex-searchPosition)) << endl;
				}
				searchPosition = source.find(searchWithoutSign,searchPosition+1);
			}
		}


		// "." 
		else if (searchLastString == "."){ 
			int searchPosition = source.find(searchWithoutSign);
				
			while(searchPosition != string::npos){
				if(source.at(searchPosition + searchWithoutSign.length()) == ' '){
					int prevSpaceIndex = source.rfind(" ",searchPosition);
					int postSpaceIndex = source.find(" ",searchPosition);
					cout << "index: " << searchPosition-1 << " word: " << source.substr(prevSpaceIndex+1,((postSpaceIndex-1)-prevSpaceIndex)) << endl;
				}
				searchPosition = source.find(searchWithoutSign,searchPosition+1);
			}
		}


		// "*"
		else if (searchLastString == "*" && searchLast2String != "**"){
			int searchPosition = source.find(searchWithoutSign);

			while(searchPosition != string::npos){
				if(source.substr(source.rfind(" ",searchPosition)+1,searchWithoutSign.length()) != searchWithoutSign && 
					source.substr(source.find(" ",searchPosition)-searchWithoutSign.length(),searchWithoutSign.length()) != searchWithoutSign){
					int prevSpaceIndex = source.rfind(" ",searchPosition);
					int postSpaceIndex = source.find(" ",searchPosition);
					cout << "index: " << searchPosition-1 << " word: " << source.substr(prevSpaceIndex+1,((postSpaceIndex-1)-prevSpaceIndex)) << endl;
				}
				searchPosition = source.find(searchWithoutSign,searchPosition+1);
			}
		}


		// "**"
		else if (searchLast2String == "**" && search.length() > 2){
			int searchPosition = source.find(searchWithoutLast2Signs);

			while(searchPosition != string::npos){
				int prevSpaceIndex = source.rfind(" ",searchPosition);
				int postSpaceIndex = source.find(" ",searchPosition);
				cout << "index: " << searchPosition-1 << " word: " << source.substr(prevSpaceIndex+1,((postSpaceIndex-1)-prevSpaceIndex)) << endl;
				searchPosition = source.find(searchWithoutLast2Signs, searchPosition+1);
			}
		}
		

		cout << "Enter search string: ";
		cin >> search;
	}

	return 0;
}