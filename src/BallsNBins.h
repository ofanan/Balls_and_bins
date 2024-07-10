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
	unsigned long 		numBalls;
	unsigned long 		ballNum;
	unsigned  			numBins;
	unsigned  			numSmpls;
	vector <Bin_t> 		bins;
	ofstream 			logFile;
	ofstream 			resFile;
	vector <Verbose_t> 	verbose; // verbose level, a defined in settings.h, e.g.: LOG, DEBUG.
	uint8_t				seed = 42;


	void openOutputFiles ();

	void func_in_me ();

	string genSettingStr ();
	public:
	BallsNBins  (
		unsigned long 		numBalls,
		unsigned  			numBins,
		vector <Verbose_t>& verbose // verbose level, a defined in settings.h, e.g.: LOG, DEBUG.
	);
	~BallsNBins ();
	void sim (
		unsigned numExps,
		unsigned numSmpls //number of samples. When 0 (sample all bins). Otherwise, sample numSmpl bins and use the minimal.
	);


};


#endif
