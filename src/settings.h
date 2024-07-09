#ifndef SETTINGS_H
#define SETTINGS_H

# include <stdio.h>
#include <fstream>

enum Verbose_t {RES, LOG, LOG_END_SIM, DEBUG};
const float CONF_LVL =0.95;

inline bool fileExists (const std::string& name); // returns true iff the given fileName already exists

# include "Balls_and_bins.h"
//typedef int Verbose_t;
//void conf_interval (vector <ar>, avg, confLvl=0.95 : st.t.interval (confLvl, len(ar)-1, loc=avg, scale=st.sem(ar)) if np.std(ar)>0 else [avg, avg]

void printToLog (ofstream log_file, vector <Bin_t> vec);


#endif
