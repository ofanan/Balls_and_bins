#ifndef BALLS_AND_BINS_H
#define BALLS_AND_BINS_H

# include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdint.h>
using namespace std;

#include "settings.h"

typedef uint16_t Bin_t; //Choose appropriate bin type to reduce run time
const long MAX_BIN_VAL = ((uint32_t)-1); // max representatable value for Bin_t.

const int num_of_exps = 1;
//typedef int gamad;

class BallsNBins {
	long 				numBalls;
	uint32_t 			numBins;
	uint32_t 			numSmpls;
	vector <Bin_t> 		bins;
	ofstream 			logFile;
	ofstream 			resFile;
	vector <Verbose_t> 	verbose = {RES}; // verbose level, a defined in settings.h, e.g.: LOG, DEBUG.
	uint8_t				seed = 42;

	void openOutputFiles ();

	void func_in_me ();

	string genSettingStr ();
	public:
	BallsNBins  (
			long 				numBalls,
			uint32_t 			numBins,
			uint32_t 			numSmpls, // num of bins to sample before selecting a bin
			vector <Verbose_t> 	verbose // verbose level, a defined in settings.h, e.g.: LOG, DEBUG.
	);
	~BallsNBins ();


};


#endif
