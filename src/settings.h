#ifndef SETTINGS_H
#define SETTINGS_H

# include <stdio.h>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>

enum Verbose_t {RES, LOG, LOG_END_SIM, DEBUG};
const float CONF_LVL =0.95;

# include "BallsNBins.h"

bool fileExists (const std::string& name); // returns true iff the given fileName already exists

//typedef int Verbose_t;
//void conf_interval (vector <ar>, avg, confLvl=0.95 : st.t.interval (confLvl, len(ar)-1, loc=avg, scale=st.sem(ar)) if np.std(ar)>0 else [avg, avg]

//void func_in_settings (int x);
void func_in_settings (ofstream log_file);
//void func_in_settings (ofstream log_file);

//class settings {
//
//	public:
////	void printToLog (ofstream log_file, vector <Bin_t> vec);
//	static void printToLog (ofstream log_file);
////	static inline bool file_exists (const std::string& name); // returns true iff the given fileName already exists
//};

#endif
