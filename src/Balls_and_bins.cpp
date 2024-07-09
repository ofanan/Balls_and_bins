//============================================================================
// Name        : Balls_and_bins.cpp
// Author      : Itamar Cohen
// Description :
//============================================================================

#include "settings.h"
#include "Balls_and_bins.h"


Balls_and_bins::Balls_and_bins ()
{
	bins.reserve (num_bins);
}

Balls_and_bins::~Balls_and_bins ()
{
	bins.clear ();
//	log_file.close ();
//	res_file.close ();
}


/*************************************************************************************************************************************************
Generate a string that details the simulation's configuration
*************************************************************************************************************************************************/
void printToLog (ofstream log_file, vector <Bin_t> vec)
{
	log_file << "[";
	for (const auto bin : vec) {
		log_file << bin << " ";
	}
	log_file << "]" << endl;
}

/*************************************************************************************************************************************************
Open the output files:.log, .res, based on the chosen verbose option.
*************************************************************************************************************************************************/
void Balls_and_bins::open_output_files ()
{

//	if (std::find(verbose.begin(), verbose.end(), LOG) != verbose.end() ) {
	log_file.open ("bb.log");
//	}
//	bins.push_back (3);
	string res_file_name = "abcd.txt";
//	if (settings::file_exists (res_file_name)) {
	res_file.open(res_file_name, std::ios_base::app);
	ofstream gamad_of;
	gamad_of.open ("rgrg", std::ofstream::app);
//	func_in_settings (gamad_of);
//	}
//	else {
	res_file.open(res_file_name);
	res_file << "// format: t{T}.{Mode}.cpu{C}.stts{s} | cpu_cost=... | link_cost=... | mig_cost=... | cost=... | ratio=[c,l,m] c | resh=lvl, , where" << endl;
	res_file << "// T is the slot cnt (read from the input file)" << endl;
	res_file << "// Mode is the algorithm / solver used. Possble modes are:"  << endl;
//	}

//	if (std::find(verbose.begin(), verbose.end(), RES) != verbose.end() ) {
//		string res_file_name = "bb.res";
//			if (fileExists (res_file_name)) {
//			  res_file.open(res_file_name, std::ios_base::app);
//			}
//			else {
//				res_file.open(res_file_name);
//				res_file << "// format: t{T}.{Mode}.cpu{C}.stts{s} | cpu_cost=... | link_cost=... | mig_cost=... | cost=... | ratio=[c,l,m] c | resh=lvl, , where" << endl;
//				res_file << "// T is the slot cnt (read from the input file)" << endl;
//				res_file << "// Mode is the algorithm / solver used. Possble modes are:"  << endl;
//			}
//	}
//	res_file.open ();

}

/*************************************************************************************************************************************************
Generate a string that details the simulation's configuration
*************************************************************************************************************************************************/
string Balls_and_bins::gen_setting_str ()
{
	return "erer";
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
