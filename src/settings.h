//============================================================================
// Author      : Itamar Cohen
// Description : Header, containing declaration of types and accessory
//				 generic functions, used throughout this project.
//============================================================================
#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <stdint.h>
#include <unordered_set>

enum class Verbose_t : int8_t {
	RES 		= 0,
	LOG 		= 1,
	LOG_END_SIM = 2,
	DEBUG 		= 3
};
const float CONF_LVL =0.95;

# include "BallsNBins.h"

/*************************************************************************************************************************************************
Format-print a given vector to the requested output file
*************************************************************************************************************************************************/
template<typename Type> void printVecToFile (ofstream &file, vector <Type> const &v)
{
	file << "[";
	for (const auto item : v) {
		file << item << " ";
	}
	file << "]" << endl;
}

/*************************************************************************************************************************************************
Format-print a given vector to cout
*************************************************************************************************************************************************/
template<typename Type> void printVecToScreen (vector <Type> const &v)
{
	cout << "[";
	for (const auto item : v) {
		cout << item << " ";
	}
	cout << "]" << endl;
}

/*************************************************************************************************************************************************
* Returns the average of the given vector. If the vector is empty, the average is 0.
**************************************************************************************************************************************************/
template<typename Type> double mean (vector <Type> const &v)
{
    if(v.empty()){
        return 0;
    }
    double sum = std::reduce(std::begin(v), std::end(v), 0.0);
    return  sum / v.size(); // consider changing here to (v.size()-1) to satisfy Bessel's correction. 
}

/*************************************************************************************************************************************************
* Returns the standard deviation of the given vector. If the vector is empty, the average is 0.
* The stdev is calculated using Bessel's correction:
* https://www.statisticshowto.com/bessels-correction/#:~:text=So%20why%20do%20we%20subtract,sample%20size)%20corrects%20this%20bias.
**************************************************************************************************************************************************/
template<typename Type> double standardDeviation (vector <Type> const &v, double const &mean)
{
    if(v.empty()){
        return 0;
    }
    double accum = 0.0;
    std::for_each (std::begin(v), std::end(v), [&](const auto d) {
        accum += (d - mean) * (d - mean);
    });

    // Use minus 1 below due to Bessel's correction
    // https://www.statisticshowto.com/bessels-correction/#:~:text=So%20why%20do%20we%20subtract,sample%20size)%20corrects%20this%20bias.
    return sqrt(accum / (v.size()-1));
}

void printErrStrAndExit (const string &errorMsgStr);

/*************************************************************************************************************************************************
Returns an unordered set of numSmpls distinct integers, picked u.a.r without replacements
out of the range 0..N-1.
*************************************************************************************************************************************************/
std::unordered_set<unsigned> sampleWoReplacements
	(unsigned N, unsigned numSmpls, std::mt19937& gen);

#endif
