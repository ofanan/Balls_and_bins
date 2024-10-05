
//============================================================================
// Name        : CPPArray.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Sorts Weather data and stores the sorted data to a file.
//============================================================================

//#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <algorithm>

#include "YearAvg.h"

using namespace std;
using std::string;
using std::stringstream;

struct sortYearAvg {
	size_t operator() (const YearAvg &lhs, const YearAvg &rhs) const
	{
		return lhs.getYear() > rhs.getYear();
	}
};

//static bool cmp (const YearAvg &lhs, const YearAvg &rhs) {return true; }

int main() {

	std::vector <YearAvg> vags;
	string header;

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
//		boost::algorithm::split(toks, line, boost::is_any_of(","));
		if (toks.size()<3) { // Skip non-formatted lines
			continue;
		}
		vags.push_back (YearAvg(stof(toks[0]), stoi(toks[1]), stof(toks[2]))); // store into a set	
	}
	file.close();
	cout << "size of file is " << vags.size() << endl;
	
	ofstream ofile;
	ofile.open("yearout.csv");
	ofile << "// By vector:" << endl;
	ofile << header << "\n";
	for (auto const &yearAvg : vags) {
		ofile << yearAvg.toCSV() << "\n";
	}
//	std::set <YearAvg, sortYearAvg>	sags (std::make_move_iterator(vags.begin()), std::make_move_iterator(vags.end())); // using the struct's operator
	std::set <YearAvg>	sags (std::make_move_iterator(vags.begin()), std::make_move_iterator(vags.end())); // using the operator < defined in YearAvg.h.
	cout << "Number of unique years in the file is " << sags.size() << endl;
	std::vector<YearAvg>().swap(vags); // clear the vector
	
	ofile << "// By set:" << endl;
	ofile << header << "\n";
	for (auto const &yearAvg : sags) {
		ofile << yearAvg.toCSV() << "\n";
	}
	
	// Copy the set back into the vector vags
	vags.reserve (sags.size());
	vags.assign(sags.begin(), sags.end());
	cout << "size of the sorted vector is " << vags.size() << endl;
	
	sort (vags.begin(), vags.end(), YearAvg::sortByRain);
	ofile << "// By vector, SORTED:" << endl;
	ofile << header << "\n";
	for (auto const &yearAvg : vags) {
		ofile << yearAvg.toCSV() << "\n";
	}

	std::map <int, YearAvg> mags;
	for (auto const &yearAvg : vags) {
		mags.insert (pair<int, YearAvg> (yearAvg.getYear(), yearAvg));
	}
	
	int year;
	cout << endl << "Please insert your chosen year" << endl;
	cin >> year;
	if (auto search = mags.find(year); search!=mags.end()) { // found the requested year in the map
		cout << "the rain at year " << year << " is " << search->second.getRain() << endl;
	}
	else {
		cout << "Found no data about the year " << year << endl;
	}
	
	
	
	ofile.close();
	return 0;
}

