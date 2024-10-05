#ifndef BALLS_ANDbins__H
#define BALLS_ANDbins__H

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
	unsigned long 		num_balls_; // overall # of balls
	unsigned long 		ball_;	  // # of the current ball
	unsigned  			num_bins_;
	unsigned			chosen_bin_;
	unsigned  			num_smpls_;
	bool 				with_replacements_; // when True, we occasionally may sample the same bin a few time at a single round
	vector <Bin_t> 		bins_;
	ofstream 			log_file_;
	ofstream 			res_file_;
	vector <Verbose_t> 	verbose_; // verbose level, a defined in settings.h, e.g.: LOG, DEBUG.
	uint8_t				seed_ = 42;

	void openOutputFiles ();
	string genSettingStr (); // Return a string that details the simulation's parameters.
	bool verboseIncludes (Verbose_t const verbose); // Returns true iff the given verbose is found in the list of verbose to perform (this.verbose).
	template<typename Type> void printVecToLog (vector <Type> const &v);

	public:
	BallsNBins  (
		unsigned long 		numBalls,
		unsigned  			numBins,
		vector <Verbose_t> const verbose // verbose level, a defined in settings.h, e.g.: LOG, DEBUG.
	) :num_balls_(numBalls), num_bins_(numBins), bins_(numBins), verbose_ (verbose) {}
	~BallsNBins ();

	void printAllBinsToLog ();

	void sim (
		unsigned numExps,
		unsigned numSmpls, //number of samples. When 0 (sample all bins). Otherwise, sample numSmpl bins and use the minimal.
		bool 	 allowRepetitions // when True, we occasionally may sample the same bin a few time at a single round
	);

};

/*************************************************************************************************************************************************
Returns an unordered set of k distinct integers, picked u.a.r without replacements
out of the range 0..N-1.
*************************************************************************************************************************************************/
/*
std::unordered_set<int> gamad //sampleWoReplacements
	(int N,
	 int k,
	 std::mt19937& gen)
{
    std::unordered_set<int> elems;
    for (int r = N - k; r < N; ++r) {
        int v = std::uniform_int_distribution<>(0, r)(gen);
        // there are two cases.
        // v is not in candidates ==> add it
        // v is in candidates ==> well, r is definitely not, because
        // this is the first iteration in the loop that we could've
        // picked something that big.
        if (!elems.insert(v).second) {
            elems.insert(r);
        }
    }
    return elems;
}
std::unordered_set<int> pickSet(int N, int k, std::mt19937& gen)
{
    std::uniform_int_distribution<> dis(1, N);
    std::unordered_set<int> elems;

    while (elems.size() < k) {
        elems.insert(dis(gen));
    }

    return elems;
}
*/
#endif
