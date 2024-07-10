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
	vector<Bin_t> tmp(numBins);
	bins = tmp;
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
			resFile << "// format: ballsX_binsY_dZ : W" << endl << "// Where : " << endl;
			resFile << "// X, Y, Z are the numbers of balls, bins, samples, resp. W is the maximal load." << endl;
		}
	}
}

/*************************************************************************************************************************************************
Print all the bins to a log file
*************************************************************************************************************************************************/
void BallsNBins::printAllBinsToLog ()
{
	logFile << "ball " << ball << ", chosenBin=" << chosenBin << ": bins=[";
	for (const auto bin : bins) {
		logFile << bin << " ";
	}
	logFile << "]" << endl;
}

/*************************************************************************************************************************************************
Return a string that details the simulation's parameters.
*************************************************************************************************************************************************/
string BallsNBins::genSettingStr ()
{
	string settingStr =
			string("balls") + to_string(numBalls) +
			string("bins") + to_string(numBins) +
			string("d") + to_string(numSmpls);
	if (allowRepetitions && numSmpls>1) {
		settingStr += "R";
	}
	return settingStr;
}

/*************************************************************************************************************************************************
Simulate balls and bins
*************************************************************************************************************************************************/
void BallsNBins::sim (
		unsigned numExps,
		unsigned numSmpls, //number of samples. When 0 (sample all bins). Otherwise, sample numSmpl bins and use the minimal.
		bool 	 allowRepetitions // when True, we occasionally may sample the same bin a few time at a single round
		)
{
	this->numSmpls	= numSmpls; //number of samples. When 0 (sample all bins). Otherwise, sample numSmpl bins and use the minimal.
	this->allowRepetitions = allowRepetitions;
	if (numSmpls>2) {
		printErrStrAndExit ("BallsNBins.sim() was called with numSmpls=" + to_string(numSmpls) + "numSmpls should be either 0, 1, or 2.");
	}
	vector <Bin_t> maxLd; // maxLd[exp] will hold the maximal load observed at experiment exp.
	maxLd.reserve (numExps);
	std::random_device rd;
	std::mt19937 rng(rd());
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, numBins - 1);
	openOutputFiles ();

	for (unsigned exp(0); exp<numExps; exp++) {
		srand(seed + exp); // set the seed of random num generation
		fill(bins.begin(), bins.end(), 0); // empty all the bins
		for (ball = 0; ball<numBalls; ball++) {

			switch (numSmpls) {

				case 0:
					chosenBin = distance (bins.begin(), min_element(bins.begin(), bins.end()));
					break;
				case 1:
					chosenBin = dis(gen);
					break;
				default:
					chosenBin = dis(gen);
					unsigned scndBin;
					while (true) {
						scndBin = dis(gen);
						if (allowRepetitions || scndBin!=chosenBin) { // Assure that we don't sample the same bin again
							if (bins[scndBin]<bins[chosenBin]) {
								chosenBin =scndBin;
							}
							break;
						}
					}
					break;
			}
			bins[chosenBin]++;
			if (std::find(verbose.begin(), verbose.end(), DEBUG) != verbose.end() ) {
				if (bins[chosenBin]>=MAX_BIN_VAL) {
					printErrStrAndExit ("In BallsNBins.sim(). bin #" + to_string(chosenBin) + "reached its maximal value. Please use a larger bit width for Bin_t in BallsNBins.h");
				}
			}
			if (exp==0 && std::find(verbose.begin(), verbose.end(), LOG) != verbose.end() ) { //consider logging only in the first experiment
				printAllBinsToLog ();
			}
		} // end of this experiment
		maxLd[exp] = *std::max_element(std::begin(bins), std::end(bins));
	}
	if (std::find(verbose.begin(), verbose.end(), RES) != verbose.end() ) {
		double average = std::accumulate(maxLd.begin(), maxLd.end(), 0.0) / maxLd.size();

		// Calculate the standard deviation
		double stddev = std::sqrt(std::accumulate(maxLd.begin(), maxLd.end(), 0.0,
					   [average](double sum, int val) { return sum + std::pow(val - average, 2); }) / maxLd.size());
		resFile << genSettingStr() << " avg=" << average << " (std/avg)=" << stddev/average << endl;
	}


}

int main() {
	vector <Verbose_t> verbose = {LOG};
	BallsNBins bb = BallsNBins (
		4, 	// numBalls
		3, 	// numBins
		verbose // verbose
	);
	bb.sim (
		1, 	// numExps
		0,	// numSmpls
		false //allowRepetitions
	);
}
