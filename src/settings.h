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

typedef int8_t Verbose_t;
const Verbose_t RES = 0;
const Verbose_t LOG = 1;
const Verbose_t LOG_END_SIM = 2;
const Verbose_t DEBUG = 3;

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
    return  sum / v.size();
}

/*************************************************************************************************************************************************
* Returns the standard deviation of the given vector. If the vector is empty, the average is 0.
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

    return sqrt(accum / (v.size()-1));
}

void printErrStrAndExit (const string &errorMsgStr);

#endif
