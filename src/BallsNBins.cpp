//============================================================================
// Author      : Itamar Cohen
// Description : The main balls-and-bins simulation source file.
//============================================================================
//https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=2b5c5a64a4403f3f22ed7f7170e3a559e0687443
#include "settings.h"
#include "BallsNBins.h"

BallsNBins::BallsNBins (unsigned long numBalls, unsigned numBins, vector <Verbose_t> const &verbose)
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
	if (verboseIncludes(LOG)) {
		logFile.close ();
	}
	if (verboseIncludes(RES)) {
		resFile.close ();
	}
}


/*************************************************************************************************************************************************
Open the output files:.log, .res, based on the chosen verbose option.
*************************************************************************************************************************************************/
void BallsNBins::openOutputFiles ()
{
	if (verboseIncludes(LOG) || verboseIncludes(LOG_END_SIM)) {
		string logFileName = "log_files/bb_" + genSettingStr() + ".log";
		logFile.open(logFileName);
	}
	if (verboseIncludes(RES)) {
		string resFileName = "res/bb.res";
		if (filesystem::exists(resFileName)) {
			  resFile.open(resFileName, std::ios_base::app);
		}
		else {
			resFile.open(resFileName);
			resFile << "// format: ballsX.binsY.dZ.RW : avg=A | std_over_avg=S" << endl << "// Where : " << endl;
			resFile << "// X, Y, Z are the numbers of balls, bins, samples, resp." << endl;
			resFile << "// W==1 if we allow repetitions, else W==0." << endl;
			resFile << "// A is the maximal load, averaged over the experiments done. "<< endl;
			resFile << "// S is the ratio: standard variation of the experiments, over the maximal load." << endl;
		}
	}
}

/*************************************************************************************************************************************************
Print all the bins to a log file
*************************************************************************************************************************************************/
void BallsNBins::printAllBinsToLog ()
{
	logFile << "ball " << ball << ", chosenBin=" << chosenBin << ": bins=";
	printVecToFile (logFile, bins);
}

/*************************************************************************************************************************************************
Print a vector to a log file
*************************************************************************************************************************************************/
//template<typename Type> void BallsNBins::printVecToLog (vector <Type> const &v)
//{
//	logFile << "[";
//	for (const auto item : v) {
//		logFile << item << " ";
//	}
//	logFile << "]" << endl;
//}

/*************************************************************************************************************************************************
Return a string that details the simulation's parameters.
*************************************************************************************************************************************************/
string BallsNBins::genSettingStr ()
{
	string settingStr =
			string("balls") + to_string(numBalls) +
			string(".bins") + to_string(numBins) +
			string(".d") + to_string(numSmpls) +
			string(".R");
			;
	if (allowRepetitions && numSmpls>1) {
		settingStr += "1";
	}
	else {
		settingStr += "0";
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
	vector<Bin_t> tmp(numExps);
	maxLd= tmp;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, numBins - 1);
	openOutputFiles ();
	cout << "Starting sim. NumExps=" << numExps << ", numBalls=" << numBalls << ", numBins=" << numBins << ", numSmpls=" << numSmpls << endl;

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
			if (verboseIncludes(DEBUG)) {
				if (bins[chosenBin]>=MAX_BIN_VAL) {
					printErrStrAndExit ("In BallsNBins.sim(). bin" + to_string(chosenBin) + " reached its maximal value. Please use a larger bit width for Bin_t in BallsNBins.h");
				}
			}
			if (verboseIncludes(LOG) && exp==0) { //consider logging only in the first experiment
				printAllBinsToLog ();
			}
		} // end of this experiment
		maxLd[exp] = *std::max_element(std::begin(bins), std::end(bins));
	}
	if (verboseIncludes(LOG_END_SIM)) { //consider logging only the last experiment
		printAllBinsToLog ();
		logFile << "At the end of simulation:" << endl;
		logFile << "maxLd=";
		printVecToFile (logFile, maxLd);
	}
	if (verboseIncludes(RES)) {
		double avg 	 = mean (maxLd);
		double stdev = standardDeviation (maxLd, avg);
		resFile << genSettingStr() << " | avg=" << avg << " | std_over_avg=" << stdev/avg << endl;
	}
	cout << "Successfully finished sim." << endl;

}

/*************************************************************************************************************************************************
Returns true iff the given verbose is found in the list of verbose to perform (this.verbose).
*************************************************************************************************************************************************/
inline bool BallsNBins::verboseIncludes (Verbose_t const verbose)
{
	return (std::find((this->verbose).begin(), (this->verbose).end(), verbose) != (this->verbose).end());
}


/*************************************************************************************************************************************************
Run a short sim. Used for debugging.
*************************************************************************************************************************************************/
void runShortSim ()
{
	vector <Bin_t> vec= {1, 2, 3, 4};
	printVecToScreen (vec);
	vector <Verbose_t> verbose 	= {RES, LOG};
	BallsNBins bb = BallsNBins (
		4 , // numBalls
		2,  // numBins
		verbose // verbose
	);

	bb.sim (
		2, // numExps
		1, // numSmpls
		false //allowRepetitions
	);
}

/*************************************************************************************************************************************************
Generate a BallsNBins simulator and run it in several configurations.
*************************************************************************************************************************************************/
int main() {
	runShortSim (); //##$$$$
	exit (0); //##$$$$
	vector <Verbose_t> verbose 	= {RES};
	const unsigned numExps		= 100;
	const unsigned numBalls 	= 10000;
	const unsigned numBins[3] 	= {numBalls}; //{16, 32, numBalls};

	for (unsigned idx(0); idx<sizeof(numBins)/sizeof(unsigned); idx++) {
		for (unsigned numSmpls(0); numSmpls<3; numSmpls++) {
			BallsNBins bb = BallsNBins (
				numBalls,
				numBins[idx],
				verbose
			);

			bb.sim (
				numExps,
				numSmpls,
				false //allowRepetitions
			);
		}

		// Additional single run with 2 smpls, allowing repetitions.
		BallsNBins bb = BallsNBins (
			numBalls,
			numBins[idx],
			verbose
		);
		bb.sim (
			numExps,
			2, // numSmpls
			true //allowRepetitions
		);
	}
}
