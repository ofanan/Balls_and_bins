//============================================================================
// Author      : Itamar Cohen
// Description : The main balls-and-bins simulation source file.
//============================================================================

#include "settings.h"
#include "BallsNBins.h"


BallsNBins::BallsNBins (unsigned long numBalls, unsigned numBins, vector <Verbose_t>& verbose)
{
	this->numBalls	= numBalls;
	this->numBins	= numBins;
	this->verbose 	= verbose;  // verbose level, a defined in settings.h, e.gBallsNBins.: LOG, DEBUG.
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
	return string("balls") + to_string(numBalls) + string("bins") + to_string(numBalls) + string("d") + to_string(numSmpls);
}

/*************************************************************************************************************************************************
Simulate balls and bins
*************************************************************************************************************************************************/
void BallsNBins::sim (
		unsigned numExps,
		unsigned numSmpls
		)
{
	this->numSmpls	= numSmpls; //number of samples. When 0 (sample all bins). Otherwise, sample numSmpl bins and use the minimal.
	if (numSmpls>2) {
		printErrStrAndExit ("sim() was called with numSmpls=" + to_string(numSmpls) + "numSmpls should be either 0, 1, or 2.");
	}
	vector <unsigned long> maxLd;
	maxLd.reserve (numExps);
	unsigned chosenBin;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, numBins - 1);
	/*
	switch (numSmpls) {

		case 0: {
			void ();
		}
		case 1: {
			std::random_device rd;
			std::mt19937 rng(rd());
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, numBins - 1);
//			int num = dis(gen);
			chosenBin = dis(gen);

		}
		default:
			void ();
//			std::unordered_set<unsigned> samples;
//			std::random_device rd;
//			std::mt19937 gen(rd());
//			std::uniform_int_distribution<> dis(0, numBins - 1);
//			int num = dis(gen);
	*/
	cout << "Starting sim. NumExps=" << numExps << ", numBalls=" << numBalls << ", numBins=" << numBins << endl;

	for (unsigned exp(0); exp<numExps; exp++) {
		srand(seed + exp); // set the seed of random num generation

		fill(bins.begin(), bins.end(), 0); // empty all the bins

		switch (numSmpls) {

			case 0:
				chosenBin = distance(begin(bins), min_element(begin(bins), end(bins)));
			case 1:
				chosenBin = dis(gen);
			default:
				void ();
		}

//		for (ballNum = 0; ballNum<numBalls; ballNum++) {
//			chosenBin = 7;
//		}
	}

}

int main() {
	vector <Verbose_t> verbose = {RES, LOG};
	BallsNBins bb = BallsNBins (
		4, 	// numBalls
		3, 	// numBins
		verbose // verbose
	);
	bb.sim (
		1, 	// numExps
		0	// numSmpls
	);
}
