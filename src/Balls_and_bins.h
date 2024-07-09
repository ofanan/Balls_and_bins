#ifndef BALLS_AND_BINS_H
#define BALLS_AND_BINS_H

# include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//# include <string.h>
# include "settings.h"

typedef uint16_t Bin_t; //Choose appropriate bin type to reduce run time
const long MAX_BIN_VAL = std::numeric_limits<Bin_t>::max(); // max representatable value for Bin_t.

const int num_of_exps = 1;

class Balls_and_bins {
	vector <Bin_t> bins;

	void open_output_fiels ();
	void close_output_fiels ();
	string gen_setting_str ();
	public:
	Balls_and_bins  ();
	~Balls_and_bins ();


};


#endif
