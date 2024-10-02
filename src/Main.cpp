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
using std::string;
using std::stringstream;

int main() {

	std::vector <YearAvg> avgs;
	string header;
	int size = 0;

	string line;
	ifstream file("yearly.csv");
	if (!file.is_open()) {
		cout << "Error opening file";
		return 1;
	}	
	vector <string>	 toks;
	getline(file, header);
	while (getline(file, line)) {
		cout << line << '\n';
		boost::algorithm::split(toks, line, boost::is_any_of(","));
	// store into array
	avgs.push_back (YearAvg(stof(toks[0]), stoi(toks[1]), stof(toks[2])));
	size++;
	}
	cout << "size of file is " << size << endl;
	file.close();
	
	sort(avgs.begin(), avgs.end(), YearAvg::sortByRain);
	ofstream ofile;
	ofile.open("yearout.csv");
	ofile << header << "\n";
	for (auto const &yearAvg : avgs) {
		ofile << yearAvg.getTemp() << "," << yearAvg.getYear() << ","
		<< yearAvg.getRain() << "\n";
	}
	ofile.close();
	return 0;
}
/*
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
*/
