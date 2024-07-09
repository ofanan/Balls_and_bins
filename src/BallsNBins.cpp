//============================================================================
// Author      : Itamar Cohen
// Description : The main balls-and-bins simulation source file.
//============================================================================

#include "settings.h"
#include "BallsNBins.h"


BallsNBins::BallsNBins (long numBalls, uint32_t numBins, uint32_t numSmpls, vector <Verbose_t> verobse)
{
	this->numBalls	= numBalls;
	this->numBins	= numBins;
	this->numSmpls	= numSmpls; // num of bins to sample before selecting a bin
	this->verbose 	= verbose;  // verbose level, a defined in settings.h, e.gBallsNBins.: LOG, DEBUG.
	seed 			= 42;
	bins.reserve 	(numBins);
//	cout << (this->verbose[1]);
	vector <int> verbose_vec; // = {1}; //{RES, LOG};

//	openOutputFiles 	   ();
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
/*
	string logFileName = "bb_" + genSettingStr() + ".log";
	if (std::find(verbose.begin(), verbose.end(), LOG) != verbose.end() ) {
		cout << "1" << endl;
		if (fileExists (logFileName)) {
			  resFile.open(logFileName, std::ios_base::app);
		}
		else {
			logFile.open(logFileName);
		}
	}
	if (std::find(verbose.begin(), verbose.end(), LOG) != verbose.end() ) {
		string resFileName = "../bb.res";
		if (fileExists (resFileName)) {
			  resFile.open(resFileName, std::ios_base::app);
		}
		else {
		resFile.open(resFileName);
			resFile << "// format: t{T}.{Mode}.cpu{C}.stts{s} | cpu_cost=... | link_cost=... | mig_cost=... | cost=... | ratio=[c,l,m] c | resh=lvl, , where" << endl;
			resFile << "// T is the slot cnt (read from the input file)" << endl;
			resFile << "// Mode is the algorithm / solver used. Possble modes are:"  << endl;
		}
	}
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
*/
}

/*************************************************************************************************************************************************
Return a string that details the simulation's parameters.
*************************************************************************************************************************************************/
string BallsNBins::genSettingStr ()
{
	return string("balls") + to_string(numBalls) + string("bins") + to_string(numBalls) + string("d") + to_string(seed);
}


//if ( std::find(vec.begin(), vec.end(), item) != vec.end() )
int main() {
	vector <Verbose_t> verbose = {RES, LOG};
//	cout << verbose[1];
	BallsNBins bb = BallsNBins (
			4, 	// numBalls
			3, 	// numBins
			1,	// numSmpl
			verbose // verbose
	);
//	vector <int8_t> verbose_vec = {RES};
//	cout << verbose_vec[0];
	return 0;
}
