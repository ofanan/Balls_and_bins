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
void Balls_and_bins::open_output_files ()
{

	if (std::find(verbose.begin(), verbose.end(), LOG) != verbose.end() ) {
		log_file.open ("bb.log");
	}
//	if (fileExists (resFileName)) {
//	  resFile.open(resFileName, std::ios_base::app);
//	}
//	else {
//		resFile.open(resFileName);
//		resFile << "// format: t{T}.{Mode}.cpu{C}.stts{s} | cpu_cost=... | link_cost=... | mig_cost=... | cost=... | ratio=[c,l,m] c | resh=lvl, , where" << endl;
//		resFile << "// T is the slot cnt (read from the input file)" << endl;
//		resFile << "// Mode is the algorithm / solver used. Possble modes are:"  << endl;
//	}

	if (std::find(verbose.begin(), verbose.end(), RES) != verbose.end() ) {
		string res_file_name = "bb.res";
//			if (fileExists (res_file_name)) {
//			  resFile.open(res_file_name, std::ios_base::app);
//			}
//			else {
//				resFile.open(res_file_name);
//				resFile << "// format: t{T}.{Mode}.cpu{C}.stts{s} | cpu_cost=... | link_cost=... | mig_cost=... | cost=... | ratio=[c,l,m] c | resh=lvl, , where" << endl;
//				resFile << "// T is the slot cnt (read from the input file)" << endl;
//				resFile << "// Mode is the algorithm / solver used. Possble modes are:"  << endl;
//			}
	}
//	res_file.open ();

}

/*************************************************************************************************************************************************
Generate a string that details the simulation's configuration
*************************************************************************************************************************************************/
string Balls_and_bins::gen_setting_str ()
{
	return "erer";
}

Balls_and_bins::Balls_and_bins ()
{
	bins.reserve (num_bins);
}

Balls_and_bins::~Balls_and_bins ()
{
	bins.clear ();
	log_file.close ();
	res_file.close ();
}


//if ( std::find(vec.begin(), vec.end(), item) != vec.end() )

int main() {
//	cout << "Hello World" << endl; // prints Hello World
//	vector <Verbose_t> verbose = {DEBUG, DEBUG};
//	if ( std::find(verbose.begin(), verbose.end(), DEBUG) != verbose.end() ) {
//		cout << "DEBUG";
//	}
//	vector <int> nisui = {3,5};
//	cout << nisui;
	return 0;
}
