//============================================================================
// Author      : Itamar Cohen
// Description : Header, containing declaration of types and accessory functions
//				 used throughout this project.
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

bool fileExists (const std::string& name); // returns true iff the given fileName already exists
void printErrStrAndExit (const string &errorMsgStr);
//void printVecToLog (ofstream logFile, vector <Bin_t> vec); // Print a vector to a log file

#endif
