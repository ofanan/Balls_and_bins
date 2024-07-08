//============================================================================
// Name        : Balls_and_bins.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>

#include "settings.h"
#include "Balls_and_bins.h"

//#include <settings.h>
//using namespace settings;
using namespace std;

//if ( std::find(vec.begin(), vec.end(), item) != vec.end() )

int main() {
//	cout << "Hello World" << endl; // prints Hello World
	vector <Verbose_t> verbose = {DEBUG, DEBUG};
	if ( std::find(verbose.begin(), verbose.end(), DEBUG) != verbose.end() ) {
		cout << "DEBUG";
	}
	return 0;
}
