#ifndef BALLS_AND_BINS_H
#define BALLS_AND_BINS_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <random>
#include <numeric>
#include <filesystem>
#include <iterator>  // std::begin, std::end
using namespace std;

#include "settings.h"

typedef uint16_t Bin_t; //Choose appropriate bin type to reduce run time
const long MAX_BIN_VAL = ((Bin_t)-1); // max representatable value for Bin_t.

class BallsNBins {
	unsigned long 		_numBalls; // overall # of balls
	unsigned long 		_ball;	  // # of the current ball
	unsigned  			_numBins;
	unsigned			_chosenBin;
	unsigned  			_numSmpls;
	bool 				_allowRepetitions; // when True, we occasionally may sample the same bin a few time at a single round
	vector <Bin_t> 		_bins;
	ofstream 			_logFile;
	ofstream 			_resFile;
	vector <Verbose_t> 	_verbose; // verbose level, a defined in settings.h, e.g.: LOG, DEBUG.
	uint8_t				_seed = 42;

	void openOutputFiles ();
	string genSettingStr (); // Return a string that details the simulation's parameters.
	bool verboseIncludes (Verbose_t const verbose); // Returns true iff the given verbose is found in the list of verbose to perform (this.verbose).
	template<typename Type> void printVecToLog (vector <Type> const &v);

	public:
	BallsNBins  (
		unsigned long 		numBalls,
		unsigned  			numBins,
		vector <Verbose_t> const verbose // verbose level, a defined in settings.h, e.g.: LOG, DEBUG.
	) :_numBalls(numBalls), _numBins(numBins), _bins(numBins), _verbose (verbose) {}
	~BallsNBins ();

	void printAllBinsToLog ();

	void sim (
		unsigned numExps,
		unsigned numSmpls, //number of samples. When 0 (sample all bins). Otherwise, sample numSmpl bins and use the minimal.
		bool 	 allowRepetitions // when True, we occasionally may sample the same bin a few time at a single round
	);

};

#endif
