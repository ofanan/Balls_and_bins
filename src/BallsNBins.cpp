//============================================================================
// Name        : BallsNBins.cpp
// Author      : Itamar Cohen
// Description :
//============================================================================

#include "settings.h"
#include "BallsNBins.h"


BallsNBins::BallsNBins ()
{
	bins.reserve (numBins);
}

BallsNBins::~BallsNBins ()
{
	bins.clear ();
//	logFile.close ();
//	resFile.close ();
}


/*************************************************************************************************************************************************
Generate a string that details the simulation's configuration
*************************************************************************************************************************************************/
void printToLog (ofstream logFile, vector <Bin_t> vec)
{
	logFile << "[";
	for (const auto bin : vec) {
		logFile << bin << " ";
	}
	logFile << "]" << endl;
}

/*************************************************************************************************************************************************
Open the output files:.log, .res, based on the chosen verbose option.
*************************************************************************************************************************************************/
void BallsNBins::openOutputFiles ()
{

//	if (std::find(verbose.begin(), verbose.end(), LOG) != verbose.end() ) {
	logFile.open ("bb.log");
//	}
//	bins.push_back (3);
	string resFileName = "bb.res";
//	if (fileExists (resFileName)) {
	struct stat buffer;
	if (stat (resFileName.c_str(), &buffer) == 0) {
		  resFile.open(resFileName, std::ios_base::app);
	}
//	else {
	resFile.open(resFileName);
	resFile << "// format: t{T}.{Mode}.cpu{C}.stts{s} | cpu_cost=... | link_cost=... | mig_cost=... | cost=... | ratio=[c,l,m] c | resh=lvl, , where" << endl;
	resFile << "// T is the slot cnt (read from the input file)" << endl;
	resFile << "// Mode is the algorithm / solver used. Possble modes are:"  << endl;
//	}

//	if (std::find(verbose.begin(), verbose.end(), RES) != verbose.end() ) {
//		string resFile_name = "bb.res";
//			if (fileExists (resFile_name)) {
//			  resFile.open(resFile_name, std::ios_base::app);
//			}
//			else {
//				resFile.open(resFile_name);
//				resFile << "// format: t{T}.{Mode}.cpu{C}.stts{s} | cpu_cost=... | link_cost=... | mig_cost=... | cost=... | ratio=[c,l,m] c | resh=lvl, , where" << endl;
//				resFile << "// T is the slot cnt (read from the input file)" << endl;
//				resFile << "// Mode is the algorithm / solver used. Possble modes are:"  << endl;
//			}
//	}
//	resFile.open ();

}

/*************************************************************************************************************************************************
Generate a string that details the simulation's configuration
*************************************************************************************************************************************************/
string BallsNBins::genSettingStr ()
{
	return "erer";
}


//if ( std::find(vec.begin(), vec.end(), item) != vec.end() )

int main() {
//	vector <int> nisui = {3,5};
//	cout << nisui;
	return 0;
}
