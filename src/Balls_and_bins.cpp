//============================================================================
// Name        : Balls_and_bins.cpp
// Author      : Itamar Cohen
// Description :
//============================================================================

#include "settings.h"
#include "Balls_and_bins.h"


/*************************************************************************************************************************************************
Open the output files:.log, .res, based on the chosen verbose option.
*************************************************************************************************************************************************/
void Balls_and_bins::open_output_fiels ()
{
}

/*************************************************************************************************************************************************
Close the open output files, based on the verbose option.
*************************************************************************************************************************************************/
void Balls_and_bins::close_output_fiels ()
{
}

/*************************************************************************************************************************************************
Generate a string that details the simulation's configuration
*************************************************************************************************************************************************/
string Balls_and_bins::gen_setting_str ()
{
}

Balls_and_bins::Balls_and_bins ()
{
}

Balls_and_bins::~Balls_and_bins ()
{
}


//if ( std::find(vec.begin(), vec.end(), item) != vec.end() )

int main() {
//	cout << "Hello World" << endl; // prints Hello World
	vector <Verbose_t> verbose = {DEBUG, DEBUG};
	if ( std::find(verbose.begin(), verbose.end(), DEBUG) != verbose.end() ) {
		cout << "DEBUG";
	}
//	vector <int> nisui = {3,5};
//	cout << nisui;
	return 0;
}
