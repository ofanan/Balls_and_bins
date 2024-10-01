//============================================================================
// Name        : CPPArray.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Sorts Weather data and stores the sorted data to a file.
//============================================================================

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "YearAvg.h"

using namespace std;

int main() {


	const int SZ = 62;
	YearAvg avgs[SZ];
	cout << avgs[0].toCSV();
	string header;
	int size = 0;

	string line;
	ifstream file("yearly.csv");
	if (file.is_open()) {
		getline(file, header);
		while (getline(file, line)) {
			cout << line << '\n';

			std::stringstream sstr(line);
			std::string token;

			string toks[3]; // array of 3 string tokens
			char delim = ',';

			int i = 0;
			std::string my_input("A,B,EE");
			std::vector<std::string> results;

			boost::algorithm::split(results, my_input, boost::is_any_of(","));

			// read
			while (std::getline(sstr, token, delim)) {

				toks[i] = token;
				i++;
			}
			// the C++ 11 way to read from array.
			for (const string &token : toks) {
				cout << "value of token: " << token << endl;
			} // end for
		  // store into array
			avgs[size] = YearAvg(stof(toks[0]), stoi(toks[1]), stof(toks[2]));
			size++;
		}	        // end while getline
		cout << "size of file is " << size << endl;
		file.close();
	}	        // end if

	else {
		cout << "Error opening file";
	}
	sort(avgs, avgs+SZ, YearAvg::sortByRain);
	ofstream ofile;
	ofile.open("yearout.csv");
	ofile << header << "\n";
	for (const YearAvg &yearAvg : avgs) {
		ofile << yearAvg.getTemp() << "," << yearAvg.getYear() << ","
		<< yearAvg.getRain() << "\n";
	}
	ofile.close();

	return 0;
}
