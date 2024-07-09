//============================================================================
// Author      : Itamar Cohen
// Description : The main balls-and-bins simulation source file.
//============================================================================

#include "settings.h"
#include "BallsNBins.h"


BallsNBins::BallsNBins (long numBalls, uint32_t numBins, uint32_t numSmpls, vector <Verbose_t>& verbose)
{
	this->numBalls	= numBalls;
	this->numBins	= numBins;
	this->numSmpls	= numSmpls; // num of bins to sample before selecting a bin
	this->verbose 	= verbose;  // verbose level, a defined in settings.h, e.gBallsNBins.: LOG, DEBUG.
//	cout << int(this->verbose[0]);
	seed 			= 42;
	openOutputFiles ();
}

BallsNBins::~BallsNBins ()
{
	bins.clear ();
	if (std::find(verbose.begin(), verbose.end(), LOG) != verbose.end() ) {
		logFile.close ();
	}
	if (std::find(verbose.begin(), verbose.end(), RES) != verbose.end() ) {
		resFile.close ();
	}
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
	string logFileName = "log_files/bb_" + genSettingStr() + ".log";
	if (std::find(verbose.begin(), verbose.end(), LOG) != verbose.end() ) {
		if (fileExists (logFileName)) {
			  resFile.open(logFileName, std::ios_base::app);
		}
		else {
			logFile.open(logFileName);
		}
	}
	if (std::find(verbose.begin(), verbose.end(), LOG) != verbose.end() ) {
		string resFileName = "res/bb.res";
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
//	vector <Verbose_t> verbose = {LOG};
//	cout << int(verbose[0]); // <<", " << int(verbose[1]);
//	if (find(verbose.begin(), verbose.end(), RES) != verbose.end() ) {
//		cout << "res";
//	}
//
////	cout << verbose[1];
////	int i = 3;
//	return 0;
	vector <Verbose_t> verbose = {RES, LOG};
	BallsNBins bb = BallsNBins (
			4, 	// numBalls
			3, 	// numBins
			1,	// numSmpl
			verbose // verbose
	);
}
